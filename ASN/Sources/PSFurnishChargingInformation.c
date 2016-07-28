/*
 * Generated by asn1c-0.9.27 (http://lionet.info/asn1c)
 * From ASN.1 module "GPRSChargingDataTypes"
 * 	found in "./PGW_CDR_Format.asn"
 */

#include "PSFurnishChargingInformation.h"

static asn_TYPE_member_t asn_MBR_PSFurnishChargingInformation_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct PSFurnishChargingInformation, pSFreeFormatData),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_FreeFormatData,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"pSFreeFormatData"
		},
	{ ATF_POINTER, 1, offsetof(struct PSFurnishChargingInformation, pSFFDAppendIndicator),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_FFDAppendIndicator,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"pSFFDAppendIndicator"
		},
};
static ber_tlv_tag_t asn_DEF_PSFurnishChargingInformation_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_PSFurnishChargingInformation_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 0, 0, 0 }, /* pSFreeFormatData */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 1, 0, 0 } /* pSFFDAppendIndicator */
};
static asn_SEQUENCE_specifics_t asn_SPC_PSFurnishChargingInformation_specs_1 = {
	sizeof(struct PSFurnishChargingInformation),
	offsetof(struct PSFurnishChargingInformation, _asn_ctx),
	asn_MAP_PSFurnishChargingInformation_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_PSFurnishChargingInformation = {
	"PSFurnishChargingInformation",
	"PSFurnishChargingInformation",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_PSFurnishChargingInformation_tags_1,
	sizeof(asn_DEF_PSFurnishChargingInformation_tags_1)
		/sizeof(asn_DEF_PSFurnishChargingInformation_tags_1[0]), /* 1 */
	asn_DEF_PSFurnishChargingInformation_tags_1,	/* Same as above */
	sizeof(asn_DEF_PSFurnishChargingInformation_tags_1)
		/sizeof(asn_DEF_PSFurnishChargingInformation_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_PSFurnishChargingInformation_1,
	2,	/* Elements count */
	&asn_SPC_PSFurnishChargingInformation_specs_1	/* Additional specs */
};

