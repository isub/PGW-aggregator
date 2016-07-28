/*
 * Generated by asn1c-0.9.27 (http://lionet.info/asn1c)
 * From ASN.1 module "GPRSChargingDataTypes"
 * 	found in "./PGW_CDR_Format.asn"
 */

#include "CAMELInformationPDP.h"

static asn_TYPE_member_t asn_MBR_CAMELInformationPDP_1[] = {
	{ ATF_POINTER, 9, offsetof(struct CAMELInformationPDP, sCFAddress),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SCFAddress,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"sCFAddress"
		},
	{ ATF_POINTER, 8, offsetof(struct CAMELInformationPDP, serviceKey),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ServiceKey,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"serviceKey"
		},
	{ ATF_POINTER, 7, offsetof(struct CAMELInformationPDP, defaultTransactionHandling),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DefaultGPRS_Handling,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"defaultTransactionHandling"
		},
	{ ATF_POINTER, 6, offsetof(struct CAMELInformationPDP, cAMELAccessPointNameNI),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CAMELAccessPointNameNI,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"cAMELAccessPointNameNI"
		},
	{ ATF_POINTER, 5, offsetof(struct CAMELInformationPDP, cAMELAccessPointNameOI),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CAMELAccessPointNameOI,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"cAMELAccessPointNameOI"
		},
	{ ATF_POINTER, 4, offsetof(struct CAMELInformationPDP, numberOfDPEncountered),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NumberOfDPEncountered,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"numberOfDPEncountered"
		},
	{ ATF_POINTER, 3, offsetof(struct CAMELInformationPDP, levelOfCAMELService),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_LevelOfCAMELService,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"levelOfCAMELService"
		},
	{ ATF_POINTER, 2, offsetof(struct CAMELInformationPDP, freeFormatData),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_FreeFormatData,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"freeFormatData"
		},
	{ ATF_POINTER, 1, offsetof(struct CAMELInformationPDP, fFDAppendIndicator),
		(ASN_TAG_CLASS_CONTEXT | (9 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_FFDAppendIndicator,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"fFDAppendIndicator"
		},
};
static ber_tlv_tag_t asn_DEF_CAMELInformationPDP_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (17 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_CAMELInformationPDP_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 0, 0, 0 }, /* sCFAddress */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 1, 0, 0 }, /* serviceKey */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 2, 0, 0 }, /* defaultTransactionHandling */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 3, 0, 0 }, /* cAMELAccessPointNameNI */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 4, 0, 0 }, /* cAMELAccessPointNameOI */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 5, 0, 0 }, /* numberOfDPEncountered */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 6, 0, 0 }, /* levelOfCAMELService */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 7, 0, 0 }, /* freeFormatData */
    { (ASN_TAG_CLASS_CONTEXT | (9 << 2)), 8, 0, 0 } /* fFDAppendIndicator */
};
static uint8_t asn_MAP_CAMELInformationPDP_mmap_1[(9 + (8 * sizeof(unsigned int)) - 1) / 8] = {
	(0 << 7) | (0 << 6) | (0 << 5) | (0 << 4) | (0 << 3) | (0 << 2) | (0 << 1) | (0 << 0),
	(0 << 7)
};
static asn_SET_specifics_t asn_SPC_CAMELInformationPDP_specs_1 = {
	sizeof(struct CAMELInformationPDP),
	offsetof(struct CAMELInformationPDP, _asn_ctx),
	offsetof(struct CAMELInformationPDP, _presence_map),
	asn_MAP_CAMELInformationPDP_tag2el_1,
	9,	/* Count of tags in the map */
	asn_MAP_CAMELInformationPDP_tag2el_1,	/* Same as above */
	9,	/* Count of tags in the CXER map */
	0,	/* Whether extensible */
	(unsigned int *)asn_MAP_CAMELInformationPDP_mmap_1	/* Mandatory elements map */
};
asn_TYPE_descriptor_t asn_DEF_CAMELInformationPDP = {
	"CAMELInformationPDP",
	"CAMELInformationPDP",
	SET_free,
	SET_print,
	SET_constraint,
	SET_decode_ber,
	SET_encode_der,
	SET_decode_xer,
	SET_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_CAMELInformationPDP_tags_1,
	sizeof(asn_DEF_CAMELInformationPDP_tags_1)
		/sizeof(asn_DEF_CAMELInformationPDP_tags_1[0]), /* 1 */
	asn_DEF_CAMELInformationPDP_tags_1,	/* Same as above */
	sizeof(asn_DEF_CAMELInformationPDP_tags_1)
		/sizeof(asn_DEF_CAMELInformationPDP_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_CAMELInformationPDP_1,
	9,	/* Elements count */
	&asn_SPC_CAMELInformationPDP_specs_1	/* Additional specs */
};

