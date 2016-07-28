/*
 * Generated by asn1c-0.9.27 (http://lionet.info/asn1c)
 * From ASN.1 module "GPRSChargingDataTypes"
 * 	found in "./PGW_CDR_Format.asn"
 */

#include "SCFAddress.h"

int
SCFAddress_constraint(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const AddressString_t *st = (const AddressString_t *)sptr;
	size_t size;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	size = st->size;
	
	if((size >= 1 && size <= 20)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

/*
 * This type is implemented using AddressString,
 * so here we adjust the DEF accordingly.
 */
static void
SCFAddress_1_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {
	td->free_struct    = asn_DEF_AddressString.free_struct;
	td->print_struct   = asn_DEF_AddressString.print_struct;
	td->check_constraints = asn_DEF_AddressString.check_constraints;
	td->ber_decoder    = asn_DEF_AddressString.ber_decoder;
	td->der_encoder    = asn_DEF_AddressString.der_encoder;
	td->xer_decoder    = asn_DEF_AddressString.xer_decoder;
	td->xer_encoder    = asn_DEF_AddressString.xer_encoder;
	td->uper_decoder   = asn_DEF_AddressString.uper_decoder;
	td->uper_encoder   = asn_DEF_AddressString.uper_encoder;
	if(!td->per_constraints)
		td->per_constraints = asn_DEF_AddressString.per_constraints;
	td->elements       = asn_DEF_AddressString.elements;
	td->elements_count = asn_DEF_AddressString.elements_count;
	td->specifics      = asn_DEF_AddressString.specifics;
}

void
SCFAddress_free(asn_TYPE_descriptor_t *td,
		void *struct_ptr, int contents_only) {
	SCFAddress_1_inherit_TYPE_descriptor(td);
	td->free_struct(td, struct_ptr, contents_only);
}

int
SCFAddress_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,
		int ilevel, asn_app_consume_bytes_f *cb, void *app_key) {
	SCFAddress_1_inherit_TYPE_descriptor(td);
	return td->print_struct(td, struct_ptr, ilevel, cb, app_key);
}

asn_dec_rval_t
SCFAddress_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const void *bufptr, size_t size, int tag_mode) {
	SCFAddress_1_inherit_TYPE_descriptor(td);
	return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);
}

asn_enc_rval_t
SCFAddress_encode_der(asn_TYPE_descriptor_t *td,
		void *structure, int tag_mode, ber_tlv_tag_t tag,
		asn_app_consume_bytes_f *cb, void *app_key) {
	SCFAddress_1_inherit_TYPE_descriptor(td);
	return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);
}

asn_dec_rval_t
SCFAddress_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,
		void **structure, const char *opt_mname, const void *bufptr, size_t size) {
	SCFAddress_1_inherit_TYPE_descriptor(td);
	return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);
}

asn_enc_rval_t
SCFAddress_encode_xer(asn_TYPE_descriptor_t *td, void *structure,
		int ilevel, enum xer_encoder_flags_e flags,
		asn_app_consume_bytes_f *cb, void *app_key) {
	SCFAddress_1_inherit_TYPE_descriptor(td);
	return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);
}

static ber_tlv_tag_t asn_DEF_SCFAddress_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (4 << 2))
};
asn_TYPE_descriptor_t asn_DEF_SCFAddress = {
	"SCFAddress",
	"SCFAddress",
	SCFAddress_free,
	SCFAddress_print,
	SCFAddress_constraint,
	SCFAddress_decode_ber,
	SCFAddress_encode_der,
	SCFAddress_decode_xer,
	SCFAddress_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_SCFAddress_tags_1,
	sizeof(asn_DEF_SCFAddress_tags_1)
		/sizeof(asn_DEF_SCFAddress_tags_1[0]), /* 1 */
	asn_DEF_SCFAddress_tags_1,	/* Same as above */
	sizeof(asn_DEF_SCFAddress_tags_1)
		/sizeof(asn_DEF_SCFAddress_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	0, 0,	/* No members */
	0	/* No specifics */
};

