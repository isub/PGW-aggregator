/*
 * Generated by asn1c-0.9.27 (http://lionet.info/asn1c)
 * From ASN.1 module "GPRSChargingDataTypes"
 * 	found in "./PGW_CDR_Format.asn"
 */

#ifndef	_DynamicAddressFlag_H_
#define	_DynamicAddressFlag_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BOOLEAN.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DynamicAddressFlag */
typedef BOOLEAN_t	 DynamicAddressFlag_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_DynamicAddressFlag;
asn_struct_free_f DynamicAddressFlag_free;
asn_struct_print_f DynamicAddressFlag_print;
asn_constr_check_f DynamicAddressFlag_constraint;
ber_type_decoder_f DynamicAddressFlag_decode_ber;
der_type_encoder_f DynamicAddressFlag_encode_der;
xer_type_decoder_f DynamicAddressFlag_decode_xer;
xer_type_encoder_f DynamicAddressFlag_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _DynamicAddressFlag_H_ */
#include <asn_internal.h>
