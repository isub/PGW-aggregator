/*
 * Generated by asn1c-0.9.27 (http://lionet.info/asn1c)
 * From ASN.1 module "GPRSChargingDataTypes"
 * 	found in "./PGW_CDR_Format.asn"
 */

#include "IPBinV6AddressWithOrWithoutPrefixLength.h"

static asn_TYPE_member_t asn_MBR_IPBinV6AddressWithOrWithoutPrefixLength_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct IPBinV6AddressWithOrWithoutPrefixLength, choice.iPBinV6Address),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_IPBinV6Address,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"iPBinV6Address"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IPBinV6AddressWithOrWithoutPrefixLength, choice.iPBinV6AddressWithPrefix),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_IPBinV6AddressWithPrefixLength,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"iPBinV6AddressWithPrefix"
		},
};
static asn_TYPE_tag2member_t asn_MAP_IPBinV6AddressWithOrWithoutPrefixLength_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 0, 0, 0 }, /* iPBinV6Address */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 1, 0, 0 } /* iPBinV6AddressWithPrefix */
};
static asn_CHOICE_specifics_t asn_SPC_IPBinV6AddressWithOrWithoutPrefixLength_specs_1 = {
	sizeof(struct IPBinV6AddressWithOrWithoutPrefixLength),
	offsetof(struct IPBinV6AddressWithOrWithoutPrefixLength, _asn_ctx),
	offsetof(struct IPBinV6AddressWithOrWithoutPrefixLength, present),
	sizeof(((struct IPBinV6AddressWithOrWithoutPrefixLength *)0)->present),
	asn_MAP_IPBinV6AddressWithOrWithoutPrefixLength_tag2el_1,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_IPBinV6AddressWithOrWithoutPrefixLength = {
	"IPBinV6AddressWithOrWithoutPrefixLength",
	"IPBinV6AddressWithOrWithoutPrefixLength",
	CHOICE_free,
	CHOICE_print,
	CHOICE_constraint,
	CHOICE_decode_ber,
	CHOICE_encode_der,
	CHOICE_decode_xer,
	CHOICE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	CHOICE_outmost_tag,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	0,	/* No PER visible constraints */
	asn_MBR_IPBinV6AddressWithOrWithoutPrefixLength_1,
	2,	/* Elements count */
	&asn_SPC_IPBinV6AddressWithOrWithoutPrefixLength_specs_1	/* Additional specs */
};

