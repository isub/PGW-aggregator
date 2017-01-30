#include "OTL_Header.h"
#include "Utils.h"
#include "Session.h"


Session::Session(unsigned32 chargingID,
    unsigned64 iMSI,
    unsigned64 mSISDN,
    std::string iMEI,
	std::string accessPointName,
    unsigned32 duration,
    unsigned32 servingNodeIP,
    unsigned32 servingNodePLMNID,
    unsigned32 ratingGroup,
    unsigned32 dataVolumeUplink,
    unsigned32 dataVolumeDownlink,
    time_t cdrTime	) :
        chargingID(chargingID),
        iMSI(iMSI),
        mSISDN(mSISDN),
        iMEI(iMEI),
        accessPointName(accessPointName),
        servingNodeIP(servingNodeIP),
        servingNodePLMNID(servingNodePLMNID),
        ratingGroup(ratingGroup),
        volumeUplinkAggregated(dataVolumeUplink),
        volumeDownlinkAggregated(dataVolumeDownlink),
        volumeUplinkExported(0),
        volumeDownlinkExported(0),
        startTime(cdrTime),
        endTime(cdrTime + duration),
        lastUpdateTime(time(nullptr)),
        lastExportTime(notInitialized)
{}


void Session::UpdateData(unsigned32 volumeUplinkIncrease, unsigned32 volumeDownlinkIncrease,
                         unsigned32 durationIncrease, time_t newCdrTime)
{
    volumeUplinkAggregated += volumeUplinkIncrease;
    volumeDownlinkAggregated += volumeDownlinkIncrease;
    if (startTime == notInitialized || newCdrTime < startTime) {
        startTime = newCdrTime;
    }
    if (newCdrTime + durationIncrease > endTime) {
        endTime = newCdrTime + durationIncrease;
    }
    lastUpdateTime = time(nullptr);
}


void Session::ExportToDB(otl_connect& dbConnect)
{
    if (HaveDataToExport()) {
        otl_stream dbStream;
        dbStream.open(1,
                "call BILLING.MOBILE_DATA_CHARGER.ExportSession(:charging_id /*bigint*/, :imsi /*bigint*/, :msisdn /*bigint*/, "
                ":imei /*char[20]*/, :access_point_name /*char[64]*/, :start_time<timestamp>, :end_time<timestamp>,"
                ":serving_node_ip /*long*/, :plmn_id /*long*/, "
                ":rating_group /*long*/, :data_volume_uplink /*bigint*/, :data_volume_downlink /*bigint*/)",
                dbConnect);
            // WARNING: OTL library does not support unsigned long and unsigned long long datatypes
            // for Oracle versions lower than ORA_R11_G2, so we cast to signed64 type.
            // Long long (64-bit) type has range from -9 223 372 036 854 775 808 to 9 223 372 036 854 775 807,
            // (19 digits) so this should be enough to store IMSI and MSISDN.
            dbStream
                    << static_cast<signed64>(chargingID)
                    << static_cast<signed64>(iMSI)
                    << static_cast<signed64>(mSISDN)
                    << iMEI
                    << accessPointName
                    << Utils::Time_t_to_OTL_datetime(startTime)
                    << Utils::Time_t_to_OTL_datetime(endTime)
                    << static_cast<long>(servingNodeIP)
                    << static_cast<long>(servingNodePLMNID)
                    << static_cast<long>(ratingGroup)
                    << static_cast<signed64>(volumeUplinkAggregated)
                    << static_cast<signed64>(volumeDownlinkAggregated);

        dbStream.close();

        volumeUplinkExported += volumeUplinkAggregated;
        volumeUplinkAggregated = 0;
        volumeDownlinkExported += volumeDownlinkAggregated;
        volumeDownlinkAggregated = 0;
        startTime = endTime = notInitialized;
        lastExportTime = time(nullptr);
    }
}


void Session::PrintSessionData(std::ostream& outStream)
{
    outStream << "------------------------" << std::endl;
    outStream << "chargingID: " << chargingID << std::endl;
    outStream << "IMSI: " << iMSI << std::endl;
    outStream << "MSISDN: " << mSISDN << std::endl;
    outStream << "IMEI: " << iMEI << std::endl;
    outStream << "APN: " << accessPointName << std::endl;
    outStream << "startTime: " << ctime(&startTime) << std::endl;
    outStream << "endTime: " << ctime(&endTime) << std::endl;
    outStream << "servingNodeAddress: " << servingNodeIP << std::endl;
    outStream << "PLMN-ID: " << servingNodePLMNID << std::endl;
    outStream << "rating group: " << ratingGroup << std::endl;
    outStream << "volume uplink: " << volumeUplinkAggregated << std::endl;
    outStream << "volume downlink: " << volumeDownlinkAggregated << std::endl;
}





