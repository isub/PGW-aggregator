#include <iostream>
#include <string>
#include "Utils.h"
#include "Common.h"



std::string Utils::TBCDString_to_String(const TBCD_STRING_t* pTBCDString)
{
    //TBCD-STRING ::= OCTET STRING
    //	-- This type (Telephony Binary Coded Decimal String) is used to
    //	-- represent several digits from 0 through 9, *, #, a, b, c, two
    //	-- digits per octet, each digit encoded 0000 to 1001 (0 to 9),
    //	-- 1010 (*), 1011 (#), 1100 (a), 1101 (b) or 1110 (c); 1111 used
    //	-- as filler when there is an odd number of digits.
    //	-- bits 8765 of octet n encoding digit 2n
    //	-- bits 4321 of octet n encoding digit 2(n-1) +1

    std::string result;
    if (!pTBCDString) {
        return result;
    }
    result.reserve(pTBCDString->size * 2);
    for(int i = 0; i < pTBCDString->size; i++) {
        uint8_t next = pTBCDString->buf[i] & 0x0F;
        if (next != 0x0F) {
            result.push_back(DecodeTbcdDigit(next));
        }
        next = (pTBCDString->buf[i] & 0xF0) >> 4;
        if (next != 0x0F) {
            result.push_back(DecodeTbcdDigit(next));
        }
    }
    return result;
}

char Utils::DecodeTbcdDigit(uint8_t digit)
{
    if (digit >= 0 && digit <= 9) {
        return '0' + digit;
    }
    switch(digit) {
    case 0x0A:
        return '*';
    case 0x0B:
        return '#';
    case 0x0C:
        return 'a';
    case 0x0D:
        return 'b';
    case 0x0E:
        return 'c';
    default:
        return ' ';
    }
}


unsigned64 Utils::TBCDString_to_ULongLong(const TBCD_STRING_t* pTBCDString)
{
	if (!pTBCDString)
		return emptyValueULL;
    unsigned64 res = 0;
    for(int i = 0; i < pTBCDString->size; i++) {
		uint8_t next = pTBCDString->buf[i] & 0x0F;
		if (next >= 0 && next <= 9) {
			// ignore non numeric characters
			res *= 10;
			res += next;
		}
		next = (pTBCDString->buf[i] & 0xF0) >> 4;
		if (next >= 0 && next <= 9) {
			// ignore non numeric characters
			res *= 10;
			res += next;
		}
    }
    return res;
}



unsigned32 Utils::IPAddress_to_ULong(const IPAddress* pIPAddress)
{
	if (!pIPAddress)
        throw std::string("Empty IP address given (NULL pointer)");
    unsigned32 ip_addr_ulong = 0;
    std::string textIP;
	size_t prev_pos = 0, next_pos = 0;
	unsigned int next_octet; // not uint8_t cause we will control 8-bit overflow
	uint8_t num_octets;
	switch(pIPAddress->present) {
	case IPAddress_PR_iPBinaryAddress:
		switch (pIPAddress->choice.iPBinaryAddress.present) {
		case IPBinaryAddress_PR_iPBinV4Address:
			if (pIPAddress->choice.iPBinaryAddress.choice.iPBinV4Address.size > 4)
                throw std::string("IPv4 address consists more than of 4 bytes: ") +
					PrintBinaryDump(&pIPAddress->choice.iPBinaryAddress.choice.iPBinV4Address);
			for (int i =0; i < pIPAddress->choice.iPBinaryAddress.choice.iPBinV4Address.size; i++) {
				ip_addr_ulong <<= 8;
				ip_addr_ulong |= pIPAddress->choice.iPBinaryAddress.choice.iPBinV4Address.buf[i];
			}
			break;
		case IPBinaryAddress_PR_iPBinV6Address:
			//if ()
            throw std::string("IPv6 parsing not implemented.");
		case IPBinaryAddress_PR_NOTHING:
			return emptyValueUL;
		}
		break;
	case IPAddress_PR_iPTextRepresentedAddress:
		switch (pIPAddress->choice.iPTextRepresentedAddress.present) {
		case IPTextRepresentedAddress_PR_iPTextV4Address:
			textIP = (const char*) pIPAddress->choice.iPTextRepresentedAddress.choice.iPTextV4Address.buf;
			next_octet = 0;
			num_octets = 0;
			for (char c : textIP) {
				if (c >= '0' && c <= '9') {
					next_octet *= 10;
					next_octet += c - '0';
					if (next_octet > 0xFF)
                        throw std::string("Wrong text represented IP address given: ") + textIP;
				}
				else if (c == '.') {
					ip_addr_ulong <<= 8;
					ip_addr_ulong |= next_octet;
					if(++num_octets > 4)
                        throw std::string("Wrong text represented IP address given: ") + textIP;
					next_octet = 0;
				}
				else
                    throw std::string("Wrong text represented IP address given: ") + textIP;
			}
			ip_addr_ulong <<= 8;
			ip_addr_ulong |= next_octet;
			if(++num_octets != 4)
                throw std::string("Wrong text represented IP address given: ") + textIP;
			break;
		case IPTextRepresentedAddress_PR_iPTextV6Address:
            throw std::string("IPv6 parsing not implemented.");
		}
		break;
	case IPAddress_PR_NOTHING:
        throw std::string("Empty IP address given (pIPAddress->present == IPAddress_PR_NOTHING)");
	}
	return ip_addr_ulong;
}


std::string Utils::BinIPAddress_to_Text(unsigned32 ipAddress)
{
	std::string textIP;
	while(ipAddress > 0) {
		uint8_t next_octet = ipAddress & 0xFF;
		if (!textIP.empty())
			textIP = '.' + textIP;
        textIP = std::to_string(next_octet) + textIP;
		ipAddress >>= 8;
	}
	return textIP;
}


std::string Utils::PrintBinaryDump(const OCTET_STRING* pOctetStr)
{
	const size_t buffer_size = 256;
	char buffer[buffer_size];
	int i = 0;
	for (; i < pOctetStr->size; i++) {
		if (3 * (i + 1) >= buffer_size - 1)
			break;
		sprintf(&buffer[3 * i], "%02X ", pOctetStr->buf[i]);
	}
	buffer[3 * (i + 1)] = '\0';
    return std::string(buffer);

}

unsigned32 Utils::PLMNID_to_ULong(const PLMN_Id_t* pPLMNID)
{
	//PLMN-Id ::= OCTET STRING (SIZE (3))
	//	-- The internal structure is defined as follows:
	//	-- octet 1 bits 4321	Mobile Country Code 1st digit
	//	--         bits 8765	Mobile Country Code 2nd digit
	//	-- octet 2 bits 4321	Mobile Country Code 3rd digit
	//	--         bits 8765	Mobile Network Code 3rd digit
	//	--			or filler (1111) for 2 digit MNCs
	//	-- octet 3 bits 4321	Mobile Network Code 1st digit
	//	--         bits 8765	Mobile Network Code 2nd digit

	if (!pPLMNID) {
        throw std::string("Empty PLMN-ID given (NULL pointer)");
	}
	if (pPLMNID->size != 3) {
        throw std::string("Wrong PLMN-ID given: ") + PrintBinaryDump(pPLMNID);
	}
    unsigned32 plmnID =
		(pPLMNID->buf[0] & 0x0F) * 10000 + ((pPLMNID->buf[0] & 0xF0) >> 4) * 1000 +
		(pPLMNID->buf[1] & 0x0F) * 100// MCC
		+  (pPLMNID->buf[2] & 0x0F) * 10 + ((pPLMNID->buf[2] & 0xF0) >> 4); // MNC

	if ((pPLMNID->buf[1] & 0xF0) != 0xF0) { // if 3rd digit of MNC is present
		plmnID *= 10;
		plmnID += ((pPLMNID->buf[1] & 0xF0) >> 4);
	}
	return plmnID;
}


unsigned32 Utils::BCDString_to_ULong(const uint8_t* pOctetStr, int size)
{
    unsigned32 result = 0;
	for (int i = 0; i < size; i++)	{
		result += (pOctetStr[i] & 0x0F) + ((pOctetStr[i] & 0xF0) >> 4) * 10;
	}
	return result;
}


time_t Utils::Timestamp_to_time_t(const TimeStamp_t* pTimestamp)
{
//TimeStamp ::= OCTET STRING (SIZE(9))
//--
//-- The contents of this field are a compact form of the UTCTime format
//-- containing local time plus an offset to universal time. Binary coded
//-- decimal encoding is employed for the digits to reduce the storage and
//-- transmission overhead
//-- e.g. YYMMDDhhmmssShhmm
//-- where
//-- YY = Year 00 to 99 BCD encoded
//-- MM = Month 01 to 12 BCD encoded
//-- DD = Day 01 to 31 BCD encoded
//-- hh = hour 00 to 23 BCD encoded
//-- mm = minute 00 to 59 BCD encoded
//-- ss = second 00 to 59 BCD encoded
//-- S = Sign 0 = "+", "-" ASCII encoded
//-- hh = hour 00 to 23 BCD encoded
//-- mm = minute 00 to 59 BCD encoded
    if (!pTimestamp) {
        throw std::string("Empty Timestamp given (NULL pointer)");
    }
    if (pTimestamp->size != 9) {
        throw std::string("Wrong format of Timestamp given: ") + PrintBinaryDump(pTimestamp);
    }
	tm result;
	result.tm_year = 100 + BCDString_to_ULong(&pTimestamp->buf[0], 1); // years since 1900
	result.tm_mon = BCDString_to_ULong(&pTimestamp->buf[1], 1) - 1; // months since January (0-11)
	result.tm_mday = BCDString_to_ULong(&pTimestamp->buf[2], 1); // day of the month (1-31)
	result.tm_hour = BCDString_to_ULong(&pTimestamp->buf[3], 1); // hours since midnight (0-23)
    result.tm_min = BCDString_to_ULong(&pTimestamp->buf[4], 1); // minutes after the hour (0-59)
	result.tm_sec = BCDString_to_ULong(&pTimestamp->buf[5], 1); // seconds after minute(0-61)
	result.tm_wday = 0; // not used
	result.tm_yday = 0; // not used
    result.tm_isdst = 0; //Daylight saving Time flag
    return mktime(&result);
}


bool Utils::Timestamp_to_time_t_Test()
{
    const char *dateStr = "160530153819+0300";
    OCTET_STRING_t* octetStr = OCTET_STRING_new_fromBuf(&asn_DEF_TimeStamp,
        dateStr, strlen(dateStr));
}


std::string Utils::Time_t_to_String(time_t timeT)
{
    char buffer[20];
    strftime(buffer, 20, "%Y%m%d%H%M%S", localtime(&timeT));
    return std::string(buffer);
}


otl_datetime Utils::Time_t_to_OTL_datetime(time_t timeT)
{
    otl_datetime otlDt;

    tm tmT ;
    localtime_r(&timeT, &tmT);
    otlDt.year = tmT.tm_year + 1900;
    otlDt.month = tmT.tm_mon + 1;
    otlDt.day = tmT.tm_mday;
    otlDt.hour = tmT.tm_hour;
    otlDt.minute = tmT.tm_min;
    otlDt.second = tmT.tm_sec;
    return otlDt;
}

std::map<unsigned32, DataVolumes> Utils::SumDataVolumesByRatingGroup(const PGWRecord& pGWRecord)
{
    std::map<unsigned32, DataVolumes> dataVolumes;
    for(int i = 0; i < pGWRecord.listOfServiceData->list.count; i++) {
        auto it = dataVolumes.find(pGWRecord.listOfServiceData->list.array[i]->ratingGroup);
        if (it != dataVolumes.end()) {
            if (pGWRecord.listOfServiceData->list.array[i]->datavolumeFBCUplink)
                it->second.volumeUplink += *pGWRecord.listOfServiceData->list.array[i]->datavolumeFBCUplink;
            if (pGWRecord.listOfServiceData->list.array[i]->datavolumeFBCDownlink)
                it->second.volumeDownlink += *pGWRecord.listOfServiceData->list.array[i]->datavolumeFBCDownlink;
        }
        else {
            dataVolumes.insert(std::make_pair(pGWRecord.listOfServiceData->list.array[i]->ratingGroup,
                DataVolumes(
                    (pGWRecord.listOfServiceData->list.array[i]->datavolumeFBCUplink ?
                        *pGWRecord.listOfServiceData->list.array[i]->datavolumeFBCUplink : 0),
                    (pGWRecord.listOfServiceData->list.array[i]->datavolumeFBCDownlink ?
                        *pGWRecord.listOfServiceData->list.array[i]->datavolumeFBCDownlink : 0))
                ));
        }
    }
    return dataVolumes;
}



bool Utils::TBCDString_to_String_Test()
{
    const int test_string_len = 8;
    const char* test_strings[] =
        { "\x52\x00\x70\x72\x86\x45\x38\xf0",
          "\x52\x00\x70\x72\x86\x45\x38\x80",
          "\x52\xa0\x7b\xc2\x8d\xe5\x38\x10",
          "\x00\xab\xcd\x72\xf1\xd3\x38\xf0",
          NULL };
    const std::string correct_results [] =
        { "250007276854830",
          "2500072768548308",
          "250*#72ab85c8301",
          "00#*ba2713b830",
          "" };
    bool success = true;

    int i = 0;
    for (const char* testStr : test_strings) {
        TBCD_STRING_t* pTBCDString = OCTET_STRING_new_fromBuf(&asn_DEF_TBCD_STRING,
            testStr, test_string_len);
        std::string res = TBCDString_to_String(pTBCDString);
        if (res != correct_results[i]) {
            std::cout << "TBCDString_to_String #" << i + 1 << " FAILED. correct result: " << correct_results[i]
               << " but returned " << res << std::endl;
            success = false;
        }
        else {
            std::cout << "TBCDString_to_String #" << i + 1 << " PASSED. " << std::endl;
        }
        ASN_STRUCT_FREE(asn_DEF_TBCD_STRING, pTBCDString);
        i++;
    }
    return success;
}


bool Utils::TBCDString_to_ULongLong_Test()
{
    const int test_string_len = 8;
    const char* test_strings[] =
        { "\x52\x00\x70\x72\x86\x45\x38\xf0",
          "\x52\x00\x70\x72\x86\x45\x38\x80",
          "\x52\xa0\x7b\xc2\x89\x45\x38\x10",
          "\x00\xab\xcd\x72\xf1\xd3\x38\xf0",
          NULL };
    const unsigned64 correct_results [] =
        { 250007276854830ULL,
          2500072768548308ULL,
          2507298548301ULL,
          2713830ULL,
          0ULL };
    bool success = true;

    int i = 0;
    for (const char* testStr : test_strings) {
        TBCD_STRING_t* pTBCDString = OCTET_STRING_new_fromBuf(&asn_DEF_TBCD_STRING,
            testStr, test_string_len);
        unsigned64 res = TBCDString_to_ULongLong(pTBCDString);
        if (res != correct_results[i]) {
            std::cout << "TBCDString_to_LongLong_Test #" << i + 1 << " FAILED. correct result: " << correct_results[i]
               << " but returned " << res << std::endl;
            success = false;
        }
        else {
            std::cout << "TBCDString_to_LongLong_Test #" << i + 1 << " PASSED. " << std::endl;
        }
        ASN_STRUCT_FREE(asn_DEF_TBCD_STRING, pTBCDString);
        i++;
    }
    return success;
}

bool Utils::PLMNID_to_ULong_Test()
{
    //const int test_string_len = 8;
    const unsigned32 exception_flag = 0xFFFFFFFF;
    const char* test_strings[] =
        // NOTE: don't use strings having \x00 byte 'cause strlen is used in code below
        { "\x52\xF0\x72",
          "\x22\xF2\x10",
          "\x52\x53\x72",
          "\x10\xab\xcd\x72\xf1\xd3\x38\xf0",
        "\x86",
          NULL };
    const unsigned64 correct_results [] =
        { 25027UL,
          22201UL,
          253275UL,
          exception_flag,
          exception_flag,
          exception_flag };
    bool success = true;

    int i = 0;
    for (const char* testStr : test_strings) {
        PLMN_Id_t* pPLMNID;
        if (testStr)
            pPLMNID = OCTET_STRING_new_fromBuf(&asn_DEF_PLMN_Id, testStr, strlen(testStr));
        else
            pPLMNID = NULL;
        unsigned32 res;
        try {
            res = PLMNID_to_ULong(pPLMNID);
            if (res == correct_results[i]) {
                std::cout << "PLMNID_to_ULong_Test #" << i + 1 << " PASSED. " << std::endl;
            }
            else {
                std::cout << "PLMNID_to_ULong_Test #" << i + 1 << " FAILED. correct result: " << correct_results[i]
                   << " but returned " << res << std::endl;
                success = false;
            }
        }
        catch(const std::string& exc_text) {
            if (correct_results[i] == exception_flag) {
                std::cout << "PLMNID_to_ULong_Test #" << i + 1 << " PASSED (exception caught: " << exc_text << "). " << std::endl;
            }
            else {
                std::cout << "PLMNID_to_ULong_Test #" << i + 1 << " FAILED (exception caught: " << exc_text << "). " << std::endl;
                success = false;
            }
        }
        ASN_STRUCT_FREE(asn_DEF_PLMN_Id, pPLMNID);
        i++;
    }
    return success;
}


bool Utils::IPAddress_to_ULong_Test()
{
    const IPAddress test_ips[] = {
        {IPAddress_PR_iPBinaryAddress, {IPBinaryAddress_PR_iPBinV4Address,
                                        {*OCTET_STRING_new_fromBuf(&asn_DEF_IPBinV4Address, "\xB9\x06\x50\x0A", 4)}}},
        {IPAddress_PR_iPBinaryAddress, {IPBinaryAddress_PR_iPBinV4Address,
                                        {*OCTET_STRING_new_fromBuf(&asn_DEF_IPBinV4Address, "\xFF\xFF\xFF\xFF", 4)}}},
        {IPAddress_PR_iPBinaryAddress, {IPBinaryAddress_PR_iPBinV4Address,
                                        {*OCTET_STRING_new_fromBuf(&asn_DEF_IPBinV4Address, "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF", 8)}}},
        {IPAddress_PR_iPBinaryAddress, {IPBinaryAddress_PR_iPBinV6Address,
                                        {*OCTET_STRING_new_fromBuf(&asn_DEF_IPBinV4Address, "\xFF\xFF\xFF\xFF", 4)}}},
        {IPAddress_PR_iPBinaryAddress, {IPBinaryAddress_PR_NOTHING,
                                        {*OCTET_STRING_new_fromBuf(&asn_DEF_IPBinV4Address, "", 0)}}},
        {IPAddress_PR_NOTHING, {IPBinaryAddress_PR_iPBinV4Address,
                                        {*OCTET_STRING_new_fromBuf(&asn_DEF_IPBinV4Address, "\xB9\x06\x50\x0A", 4)}}},
        {IPAddress_PR_iPTextRepresentedAddress, { .iPTextRepresentedAddress = {IPTextRepresentedAddress_PR_iPTextV4Address,
                                        {*OCTET_STRING_new_fromBuf(&asn_DEF_IPTextRepresentedAddress, "172.18.1.0", 10)}}}},
        {IPAddress_PR_iPTextRepresentedAddress, { .iPTextRepresentedAddress = {IPTextRepresentedAddress_PR_iPTextV4Address,
                                        {*OCTET_STRING_new_fromBuf(&asn_DEF_IPTextRepresentedAddress, "1.18.99.255", 11)}}}},
        {IPAddress_PR_iPTextRepresentedAddress, { .iPTextRepresentedAddress = {IPTextRepresentedAddress_PR_iPTextV4Address,
                                        {*OCTET_STRING_new_fromBuf(&asn_DEF_IPTextRepresentedAddress, "11899.255", 9)}}}},
        {IPAddress_PR_iPTextRepresentedAddress, { .iPTextRepresentedAddress = {IPTextRepresentedAddress_PR_iPTextV6Address,
                                        {*OCTET_STRING_new_fromBuf(&asn_DEF_IPTextRepresentedAddress, "172.18.1.0", 10)}}}}
    };
    const unsigned64 exception_sign = 0xFFFFFFFFFFFFFFFF;
    const unsigned64 correct_results [] =
        { 0xB906500A, 0xFFFFFFFF, exception_sign, exception_sign, emptyValueUL, exception_sign, 0xAC120100, 0x011263FF, exception_sign, exception_sign };
    bool success = true;

    int i = 0;
    for (/*int i = 0; i < test_num; i++*/const IPAddress& testIPAddr : test_ips) {
        try {
            unsigned32 res = IPAddress_to_ULong(&testIPAddr);
            if (res != correct_results[i]) {
                std::cout << "IPAddress_to_ULong_Test #" << i + 1 << " FAILED. correct result: " << correct_results[i]
                   << " but returned " << res << std::endl;
                success = false;
            }
            else {
                std::cout << "IPAddress_to_ULong_Test #" << i + 1 << " PASSED. " << std::endl;
            }
        }
        catch(const std::string& exc_text) {
            if (correct_results[i] == exception_sign) {
                std::cout << "IPAddress_to_ULong_Test #" << i + 1 << " PASSED (exception caught: "
                          << exc_text << "). " << std::endl;
            }
            else {
                std::cout << "IPAddress_to_ULong_Test #" << i + 1 << " FAILED (exception caught: "
                          << exc_text << ")." << std::endl;
                success = false;
            }
        }
        i++;
    }
    return success;
}


bool Utils::SumDataVolumesByRatingGroup_Test()
{
    bool success = true;
    PGWRecord rec;
    void* ptr = &rec.listOfServiceData;
    ptr = calloc(1, sizeof(PGWRecord::listOfServiceData));
    return success;
}


bool Utils::RunAllTests()
{
	assert(Utils::TBCDString_to_ULongLong_Test());
    assert(Utils::TBCDString_to_String_Test());
	assert(Utils::IPAddress_to_ULong_Test());
	assert(Utils::PLMNID_to_ULong_Test());
}
