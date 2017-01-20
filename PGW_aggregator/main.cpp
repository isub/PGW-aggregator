#include <iostream>
#include <cassert>
#include "GPRSRecord.h"
#include "OTL_Header.h"
#include "Utils.h"
#include "Session.h"
#include "Common.h"
#include "Aggregator.h"
#include "Parser.h"
#include "ExportRules.h"
#include "LogWriter.h"
#include "Config.h"

Config config;
ExportRules exportRules;
LogWriter logWriter;

void log(short msgType, std::string msgText)
{
    std::cout << msgText << std::endl;
}


void ClearTestExportTable(otl_connect& dbConnect)
{
    otl_stream dbStream;
    dbStream.open(1, "call Billing.Mobile_Data_Charger.ClearMobileSessions()", dbConnect);
    dbStream.close();
}

void CheckExportedData(otl_connect& dbConnect)
{
    otl_stream otlStream;
    otlStream.open(1, "call Billing.Mobile_Data_Charger.CheckTestExport()", dbConnect);
    otlStream.close();
}

void RunStoredLogicTests(otl_connect& dbConnect)
{
    std::cout << "Running stored database logic tests ..." << std::endl;
    otl_stream otlStream;
    otlStream.open(1, "call Billing.Mobile_Data_Charger.RunAllTests()", dbConnect);
    otlStream.close();

}

void RunAllTests(otl_connect& dbConnect)
{
    Utils::RunAllTests();
    RunStoredLogicTests(dbConnect);

    std::string cdrExtension(".dat");
    ClearTestExportTable(dbConnect);
    dbConnect.commit();

    time_t testStart = time(nullptr);
    Parser parser;
    // uncomment if printing file contents neeeded:
        //parser.SetPrintContents(true);
    parser.ProcessDirectory(config.sampleCdrDir, config.cdrExtension, config.archiveDir);
    std::cout << "Export consumed " << difftime(time(nullptr), testStart) << " seconds" << std::endl;
    std::cout << "Checking exported data ..." << std::endl;
    CheckExportedData(dbConnect);
    std::cout << "Total aggregation test PASSED." << std::endl;
}


void printUsage()
{
    std::cerr << "Usage: " << std::endl << "pgw-aggregator <config-file> [-test]" << std::endl;
}

int main(int argc, const char* argv[])
{
    if (argc < 2) {
        printUsage();
        exit(EXIT_FAILURE);
    }
    const char* confFilename = argv[1];
    bool runTests = false;
    if (argc > 2 && !strncasecmp(argv[2], "-test", 5)) {
        runTests = true;
    }
    std::ifstream confFile(confFilename, std::ifstream::in);
    if (!confFile.is_open()) {
        std::cerr << "Unable to open config file " << confFilename << std::endl;
        exit(EXIT_FAILURE);
    }
    try {
        config.ReadConfigFile(confFile);
        config.ValidateParams();
    }
    catch(const std::exception& ex) {
        std::cerr << "Error when parsing config file " << confFilename << " " << std::endl;
        std::cerr << ex.what() <<std::endl;
        exit(EXIT_FAILURE);
    }

    logWriter.Initialize(config.logDir);
    logWriter << "PGW aggregator start";
    logWriter << config.DumpAllSettings();

    const int OTL_MULTITHREADED_MODE = 1;
    otl_connect::otl_initialize(OTL_MULTITHREADED_MODE);
	otl_connect dbConnect;
	try {
        dbConnect.rlogon(config.connectString.c_str());
        exportRules.ReadSettingsFromDatabase(dbConnect);
        if (runTests) {
            RunAllTests(dbConnect);
        }
        else {
            Parser parser;
            parser.ProcessDirectory(config.inputDir, config.cdrExtension, config.archiveDir);
        }
        dbConnect.commit();
		dbConnect.logoff();
	}
	catch(otl_exception& otlEx) {
		dbConnect.rollback();
		// TODO: add correct processing
        std::cerr << "DB error: " << std::endl
             << otlEx.msg << std::endl
             << otlEx.stm_text << std::endl
             << otlEx.var_info << std::endl;
	}
    logWriter << "PGW aggregator shutdown";
    logWriter.Stop();
    return 0;
}
