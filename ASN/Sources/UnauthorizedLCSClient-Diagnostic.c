/*
 * Generated by asn1c-0.9.27 (http://lionet.info/asn1c)
 * From ASN.1 module "GPRSChargingDataTypes"
 * 	found in "./PGW_CDR_Format.asn"
 */

#include "UnauthorizedLCSClient-Diagnostic.h"

int
UnauthorizedLCSClient_Diagnostic_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	/* Replace with underlying type checker */
	td->check_constraints = asn_DEF_NativeEnumerated.check_constraints;
	return td->check_constraints(td, sptr, ctfailcb, app_key);
}

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static void
UnauthorizedLCSClient_Diagnostic_1_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
	td->free_struct    = asn_DEF_NativeEnumerated.free_struct;
	td->print_struct   = asn_DEF_NativeEnumerated.print_struct;
	td->check_constraints = asn_DEF_NativeEnumerated.check_constraints;
	td->ber_decoder    = asn_DEF_NativeEnumerated.ber_decoder;
	td->der_encoder    = asn_DEF_NativeEnumerated.der_encoder;
	td->xer_decoder    = asn_DEF_NativeEnumerated.xer_decoder;
	td->xer_encoder    = asn_DEF_NativeEnumerated.xer_encoder;
	td->uper_decoder   = asn_DEF_NativeEnumerated.uper_decoder;
	td->uper_encoder   = asn_DEF_NativeEnumerated.uper_encoder;
	if(!td->per_constraints)
		td->per_constraints = asn_DEF_NativeEnumerated.per_constraints;
	td->elements       = asn_DEF_NativeEnumerated.elements;
	td->elements_count = asn_DEF_NativeEnumerated.elements_count;
     /* td->specifics      = asn_DEF_NativeEnumerated.specifics;	// Defined explicitly */
}

void
UnauthorizedLCSClient_Diagnostic_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	UnauthorizedLCSClient_Diagnostic_1_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

int
UnauthorizedLCSClient_Diagnostic_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	UnauthorizedLCSClient_Diagnostic_1_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

asn_dec_rval_t
UnauthorizedLCSClient_Diagnostic_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	UnauthorizedLCSClient_Diagnostic_1_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

asn_enc_rval_t
UnauthorizedLCSClient_Diagnostic_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	UnauthorizedLCSClient_Diagnostic_1_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

asn_dec_rval_t
UnauthorizedLCSClient_Diagnostic_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	UnauthorizedLCSClient_Diagnostic_1_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

asn_enc_rval_t
UnauthorizedLCSClient_Diagnostic_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	UnauthorizedLCSClient_Diagnostic_1_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static asn_INTEGER_enum_map_t asn_MAP_UnauthorizedLCSClient_Diagnostic_value2enum_1[] = {
	{ 0,	23,	"noAdditionalInformation" },
	{ 1,	33,	"clientNotInMSPrivacyExceptionList" },
	{ 2,	20,	"callToClientNotSetup" },
	{ 3,	28,	"privacyOverrideNotApplicable" },
	{ 4,	39,	"disallowedByLocalRegulatoryRequirements" },
	{ 5,	24,	"unauthorizedPrivacyClass" },
	{ 6,	46,	"unauthorizedCallSessionUnrelatedExternalClient" },
	{ 7,	44,	"unauthorizedCallSessionRelatedExternalClient" }
	/* This list is extensible */
};
static unsigned int asn_MAP_UnauthorizedLCSClient_Diagnostic_enum2value_1[] = {
	2,	/* callToClientNotSetup(2) */
	1,	/* clientNotInMSPrivacyExceptionList(1) */
	4,	/* disallowedByLocalRegulatoryRequirements(4) */
	0,	/* noAdditionalInformation(0) */
	3,	/* privacyOverrideNotApplicable(3) */
	7,	/* unauthorizedCallSessionRelatedExternalClient(7) */
	6,	/* unauthorizedCallSessionUnrelatedExternalClient(6) */
	5	/* unauthorizedPrivacyClass(5) */
	/* This list is extensible */
};
static asn_INTEGER_specifics_t asn_SPC_UnauthorizedLCSClient_Diagnostic_specs_1 = {
	asn_MAP_UnauthorizedLCSClient_Diagnostic_value2enum_1,	/* "tag" => N; sorted by tag */
	asn_MAP_UnauthorizedLCSClient_Diagnostic_enum2value_1,	/* N => "tag"; sorted by N */
	8,	/* Number of elements in the maps */
	6,	/* Extensions before this member */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static ber_tlv_tag_t asn_DEF_UnauthorizedLCSClient_Diagnostic_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_UnauthorizedLCSClient_Diagnostic = {
	"UnauthorizedLCSClient-Diagnostic",
	"UnauthorizedLCSClient-Diagnostic",
	UnauthorizedLCSClient_Diagnostic_free,
	UnauthorizedLCSClient_Diagnostic_print,
	UnauthorizedLCSClient_Diagnostic_constraint,
	UnauthorizedLCSClient_Diagnostic_decode_ber,
	UnauthorizedLCSClient_Diagnostic_encode_der,
	UnauthorizedLCSClient_Diagnostic_decode_xer,
	UnauthorizedLCSClient_Diagnostic_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_UnauthorizedLCSClient_Diagnostic_tags_1,
	sizeof(asn_DEF_UnauthorizedLCSClient_Diagnostic_tags_1)
		/sizeof(asn_DEF_UnauthorizedLCSClient_Diagnostic_tags_1[0]), /* 1 */
	asn_DEF_UnauthorizedLCSClient_Diagnostic_tags_1,	/* Same as above */
	sizeof(asn_DEF_UnauthorizedLCSClient_Diagnostic_tags_1)
		/sizeof(asn_DEF_UnauthorizedLCSClient_Diagnostic_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	0, 0,	/* Defined elsewhere */
	&asn_SPC_UnauthorizedLCSClient_Diagnostic_specs_1	/* Additional specs */
};

