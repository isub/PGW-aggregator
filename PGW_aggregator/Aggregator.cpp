#include <stdio.h>
#include <iostream>
#include "Aggregator.h"
#include "Utils.h"
#include "otl_utils.h"
#include "Common.h"
#include "LogWriterOtl.h"
#include "Config.h"


extern LogWriterOtl logWriter;
extern Config config;
std::mutex mutex;

Aggregator::Aggregator(int index, const std::string& connectString, ExportRules &er) :
    thisIndex(index),
    cdrQueue(cdrQueueSize),
    stopFlag(false),
    connectString(connectString),
    exportRules(er),
    lastIdleSessionsEject(notInitialized),
    lastMapSizeReport(notInitialized)
{
    time(&lastIdleSessionsEject);
    thread = std::thread(&Aggregator::AggregatorThreadFunc, this);
}


void Aggregator::AddCdrToQueue(const CDR& cdr)
{
    bool queueIsFull = false;
    while (!cdrQueue.push(cdr)) {
        if (!queueIsFull) {
            logWriter.Write("AddCdrToQueue: CDR queue max size reached (" + std::to_string(cdrQueueSize) + ")",
                            thisIndex, debug);
            queueIsFull = true;
        }
        std::this_thread::sleep_for(std::chrono::seconds(secondsToSleepWhenNothingToDo));
    }
}


void Aggregator::AggregatorThreadFunc()
{
    try {
        dbConnect.rlogon(connectString.c_str());
    }
    catch(const otl_exception& ex) {
        SetExceptionAndSendAlert(OTL_Utils::OtlExceptionToText(ex));
        logWriter.Write("**** DB ERROR while logging in to DB: **** " +
            crlf + exceptionText, thisIndex);
    }

    while (!(stopFlag && cdrQueue.empty())) {
        ProcessCDRQueue();
    }

    logWriter.Write("Shutdown flag set.", thisIndex);
    ExportAllSessionsToDB();
    logWriter.Write("Thread finish", thisIndex);
    if (dbConnect.connected) {
        dbConnect.commit();
        dbConnect.logoff();
    }
}


void Aggregator::ProcessCDRQueue()
{
    try {
        MapSizeReportIfNeeded();
        CDR cdr;
        if (cdrQueue.pop(cdr)) {
            ProcessCDR(cdr);
            exceptionText.clear();
            ASN_STRUCT_FREE(asn_DEF_GPRSRecord, cdr.gprsRecord);
            delete cdr.filename;
        }
        else {
            if (EjectOneIdleSession()) {
                exceptionText.clear();
            }
            else {
                logWriter.Write("CDR queue processed and nothing to eject. Sessions count: "
                                + std::to_string(sessions.size()), thisIndex, debug);
                std::unique_lock<std::mutex> lock(mutex);
                conditionVar.wait_for(lock, std::chrono::seconds(secondsToSleepWhenNothingToDo));
            }
        }
    }
    catch(const std::exception& ex) {
        // exception is rethrown from the Session class.
        SetExceptionAndSendAlert(ex.what());
        logWriter.Write(exceptionText, thisIndex);
        dbConnect.reconnect();
    }
}


void Aggregator::ProcessCDR(const CDR& cdr)
{
    try {
        DataVolumesMap dataVolumes = Utils::SumDataVolumesByRatingGroup(cdr.gprsRecord->choice.pGWRecord);
        auto eqRange = sessions.equal_range(cdr.gprsRecord->choice.pGWRecord.chargingID); // equal_range is used here because of multimap. In case of map we could use find function here
        if (eqRange.first == eqRange.second) {
            // not found
             CreateSessions(cdr.gprsRecord->choice.pGWRecord, dataVolumes);
        }
        else {
            // one or more sessions having this Charging ID are found, try to find appropriate rating group
            for (auto sessionIter = eqRange.first; sessionIter != eqRange.second; ++sessionIter) {
                auto dataVolumeIter = dataVolumes.find(sessionIter->second.get()->ratingGroup);
                if (dataVolumeIter != dataVolumes.end()) {
                    // session having same rating group found, update values
                    sessionIter->second.get()->UpdateData(dataVolumeIter->second.volumeUplink,
                                                      dataVolumeIter->second.volumeDownlink,
                                                      dataVolumeIter->second.duration,
                                                      dataVolumeIter->second.timeOfFirstUsage);
                    dataVolumes.erase(dataVolumeIter);
                }
            }
            CreateSessions(cdr.gprsRecord->choice.pGWRecord, dataVolumes);
        }
    }
    catch(const std::exception& ex) {
        std::string message = "ProcessCDR exception: " + std::string(ex.what()) + crlf
                + "Filename: " + *cdr.filename + crlf
                + Utils::DumpCDRContents(cdr.gprsRecord->choice.pGWRecord);
        SetExceptionAndSendAlert(message);
        logWriter.Write(message, thisIndex);
    }
}


void Aggregator::CreateSessions(const PGWRecord& pGWRecord, const DataVolumesMap& dataVolumes)
{
    for (auto dataVolumeIter : dataVolumes) {
        CreateSession(pGWRecord,
                      dataVolumeIter.first /* rating group */,
                      dataVolumeIter.second.timeOfFirstUsage,
                      dataVolumeIter.second.duration,
                      dataVolumeIter.second.volumeUplink,
                      dataVolumeIter.second.volumeDownlink);
    }
}


SessionMap::iterator Aggregator::CreateSession(const PGWRecord& pGWRecord, unsigned32 ratingGroup,
      time_t sessionStartTime, unsigned32 duration, unsigned32 volumeUplink, unsigned32 volumeDownlink)
{
    unsigned64 imsi = Utils::TBCDString_to_ULongLong(pGWRecord.servedIMSI);
    return sessions.insert(std::make_pair(pGWRecord.chargingID,
        Session_ptr(new Session(
           pGWRecord.chargingID,
           imsi,
		   Utils::TBCDString_to_ULongLong(pGWRecord.servedMSISDN),
           Utils::TBCDString_to_String(pGWRecord.servedIMEISV),
           (pGWRecord.accessPointNameNI ? reinterpret_cast<const char*>(pGWRecord.accessPointNameNI->buf) : ""),
		   ( NULL != pGWRecord.servedPDPPDNAddress && pGWRecord.servedPDPPDNAddress->present == PDPAddress_PR_iPAddress)
				? Utils::IPAddress_to_ULong( &pGWRecord.servedPDPPDNAddress->choice.iPAddress )
				: static_cast< unsigned32 >(-1),
           duration,
		   Utils::IPAddress_to_ULong(pGWRecord.servingNodeAddress.list.array[0]),
		   Utils::PLMNID_to_ULong(pGWRecord.servingNodePLMNIdentifier),
		   ratingGroup,
		   volumeUplink,
		   volumeDownlink,
           sessionStartTime,
           exportRules,
           dbConnect))));
}


void Aggregator::ExportAllSessionsToDB()
{
    logWriter.Write("Exporting all sessions: " + std::to_string(sessions.size()), thisIndex);
    while(std::any_of(sessions.begin(), sessions.end(),
                     [](std::pair<unsigned32, Session_ptr> s) { return s.second.get()->HaveDataToExport(); } )) {
        for (auto& it : sessions) {
            try {
                it.second->ForceExport();
            }
            catch(const std::runtime_error& ex) {
                SetExceptionAndSendAlert(ex.what());
                logWriter.Write(exceptionText, thisIndex);
                dbConnect.reconnect();
            }
        }
    }
    logWriter.Write("All sessions exported.", thisIndex);
}


bool Aggregator::EjectOneIdleSession()
{
    time_t now;
    time(&now);
    for (auto it = sessions.begin(); it != sessions.end(); it++) {
        if (Utils::DiffMinutes(it->second->lastUpdateTime, now) > config.sessionEjectPeriodMin) {
            it->second->ForceExport();
            sessions.erase(it);
            logWriter.Write("One idle session was ejected. Sessions count: " + std::to_string(sessions.size()),
                            thisIndex, debug);
            return true;
        }
    }
    return false;
}


void Aggregator::MapSizeReportIfNeeded()
{
    time_t now;
    time(&now);
    if (Utils::DiffMinutes(lastMapSizeReport, now) > mapSizeReportPeriodMin) {
        double fillPercent = static_cast<double>(sessions.size()) / sessions.max_size() * 100;
        logWriter.Write("Sessions count: " + std::to_string(sessions.size()) + " (" +
                        std::to_string(fillPercent) + "% from max)", thisIndex);
        lastMapSizeReport = now;
    }
}


void Aggregator::SetExceptionAndSendAlert(const std::string& excText)
{
    exceptionText = excText;
    if (exceptionText != lastExceptionText && dbConnect.connected) {
        otl_stream dbStream;
        try {
            dbStream.open(1, std::string("call BILLING.MOBILE_DATA_CHARGER.SendAlert(:mess/*char[" +
                           std::to_string(maxAlertMessageLen) + "]*/)").c_str(), dbConnect);
            dbStream << exceptionText.substr(0, maxAlertMessageLen-1);
            dbStream.close();
            lastExceptionText = exceptionText;
        }
        catch(const otl_exception& ex) {
            logWriter.LogOtlException("**** DB ERROR while sending alert ****", ex, thisIndex);
        }
    }
}


std::string Aggregator::GetExceptionMessage() const
{
    if (!exceptionText.empty()) {
        return exceptionText;
    }
    if(!dbConnect.connected) {
        return "Not connected to DB";
    }
    return "";
}


void Aggregator::WakeUp()
{
    conditionVar.notify_one();
}


void Aggregator::SetStopFlag()
{
    stopFlag = true;
}

Aggregator::~Aggregator()
{
    stopFlag = true;
    thread.join();
}
