#include <iostream>
#include <boost/lockfree/queue.hpp>
#include "ConfigContainer.h"
#include "GPRSRecord.h"
#include "CDRRecord.h"
#include "OTL_Header.h"

#define LOG_ERROR 3

using namespace std;

void log(short msgType, string msgText)
{
    cout << msgText << endl;

}

unsigned long long TBCDString_to_LongLong(TBCD_STRING_t* pTBCDString)
{
    unsigned long long res = 0;

}

int main(int argc, const char* argv[])
{
    FILE *fTapFile=fopen(argv[1],"rb");
    if(!fTapFile) {
        log(LOG_ERROR, string ("Unable to open input file ") + argv[1]);
        return -1;
    }

    fseek(fTapFile, 0, SEEK_END);
    unsigned long tapFileLen=ftell(fTapFile); // длина данных файла (без заголовка)

    unsigned char* buffer = new unsigned char [tapFileLen];

    fseek(fTapFile, 0, SEEK_SET);
    size_t bytesRead=fread(buffer, 1, tapFileLen, fTapFile);
    fclose(fTapFile);
    if(bytesRead < tapFileLen) {
        log(LOG_ERROR, string("Error reading file ") + argv[1]);
        delete [] buffer;
        return -1;
    }
    cout << "read " << bytesRead << " bytes" << endl;

    char* printName = new char[ strlen(argv[1])+5 ];
    sprintf(printName, "%s.txt", argv[1]);
    FILE* fFileContents = fopen (printName, "w");

    boost::lockfree::queue<GPRSRecord*> cdrQueue(10);
    asn_dec_rval_t rval;
    unsigned long nextChunk = 0;
    unsigned long recordCount = 0;
    const int maxPGWRecordSize = 2000;
    while(nextChunk < bytesRead) {
        GPRSRecord* pGprsRecord = NULL;
        rval = ber_decode(0, &asn_DEF_GPRSRecord, (void**) &pGprsRecord, buffer + nextChunk, maxPGWRecordSize);
        //cout << "ber_decode res: " << rval.code << endl;
        if(rval.code != RC_OK) {
            log( LOG_ERROR, string("Error while decoding ASN file. Error code ")); // + std::to_string(rval.code));
            break;
        }
        if ( fFileContents ) {
            asn_fprint(fFileContents, &asn_DEF_GPRSRecord, pGprsRecord);

        }
        nextChunk += rval.consumed;
        recordCount++;
        //ASN_STRUCT_FREE(asn_DEF_GPRSRecord, pGprsRecord);
        cdrQueue.push(pGprsRecord);
        //pGprsRecord = NULL;
    }

    cout << recordCount << " records parsed in " << argv[1] << endl;
    //cout << " queue size: " << cdrQueue. << endl;
    fclose(fFileContents);
    delete [] printName;

    otl_connect::otl_initialize();
    otl_connect dbConnect;
    dbConnect.rlogon("aggregator/aggregator@192.168.101.249:1521/welcome");


    dbConnect.logoff();

    return 0;
}

