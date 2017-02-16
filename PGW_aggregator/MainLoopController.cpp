#include "MainLoopController.h"
#include "LogWriter.h"

extern LogWriter logWriter;

MainLoopController::MainLoopController(const std::string &connectString, const std::string &filesDirectory,
                                       const std::string &extension, const std::string &archDirectory, const std::string &badDirectory) :
    parser(connectString, filesDirectory, extension, archDirectory, badDirectory),
    cdrFilesDirectory(filesDirectory),
    cdrExtension(extension),
    stopFlag(false),
    shutdownFilePath(filesDirectory + "/" + shutdownFlagFilename),
    printFileContents(false),
    lastAlertTime(notInitialized)
{
}


void MainLoopController::Run()
{
    filesystem::path cdrPath(cdrFilesDirectory);
    bool allCdrProcessed = false;
    std::string lastPostponeReason;
    try {
        while(!IsShutdownFlagSet()) {
            parser.RefreshExportRulesIfNeeded();
            filesystem::directory_iterator endIterator;
            bool filesFound = false;
            for(filesystem::directory_iterator dirIterator(cdrPath); dirIterator != endIterator; dirIterator++) {
                if (filesystem::is_regular_file(dirIterator->status()) &&
                        dirIterator->path().extension() == cdrExtension) {
                    filesFound = true;
                    allCdrProcessed = false;
                    if (parser.IsReady()) {
                        lastPostponeReason.clear();
                        parser.ProcessFile(dirIterator->path());
                    }
                    else {
                        if (lastPostponeReason != parser.GetPostponeReason()) {
                            lastPostponeReason = parser.GetPostponeReason();
                            logWriter.Write("CDR processing postponed due to: " + lastPostponeReason, mainThreadIndex);
                        }

                        //TODO: check it
                        //parser.AlertAggregatorExceptions();

                        Sleep();
                    }
                    if (IsShutdownFlagSet()) {
                        break;
                    }
                }
            }
            if (!filesFound) {
                if (!allCdrProcessed) {
                    allCdrProcessed = true;
                    logWriter << "All CDR files processed.";
                }
                Sleep();
            }
        }
    }
    catch(const std::exception& ex) {
            logWriter.Write("Parser ERROR: ", mainThreadIndex, error);
            logWriter.Write(ex.what(), mainThreadIndex, error);
            lastExceptionText = ex.what();
    }
    logWriter << "Shutting down ...";
}


void MainLoopController::Sleep()
{
    std::this_thread::sleep_for(std::chrono::seconds(secondsToSleepWhenNothingToDo));
}

bool MainLoopController::IsShutdownFlagSet()
{
    if (filesystem::exists(shutdownFilePath)) {
        return true;
    }
    else {
        return false;
    }
}

void MainLoopController::SetPrintContents(bool printContents)
{
    parser.SetPrintContents(printContents);
}



MainLoopController::~MainLoopController()
{
    parser.SetStopFlag();
    filesystem::remove(shutdownFilePath);
}

