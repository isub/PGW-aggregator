/*
 * Generated by asn1c-0.9.27 (http://lionet.info/asn1c)
 * From ASN.1 module "GPRSChargingDataTypes"
 * 	found in "./PGW_CDR_Format.asn"
 */

#ifndef	_IPBinV6Address_H_
#define	_IPBinV6Address_H_


#include <asn_application.h>

/* Including external dependencies */
#include <OCTET_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* IPBinV6Address */
typedef OCTET_STRING_t	 IPBinV6Address_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_IPBinV6Address;
asn_struct_free_f IPBinV6Address_free;
asn_struct_print_f IPBinV6Address_print;
asn_constr_check_f IPBinV6Address_constraint;
ber_type_decoder_f IPBinV6Address_decode_ber;
der_type_encoder_f IPBinV6Address_encode_der;
xer_type_decoder_f IPBinV6Address_decode_xer;
xer_type_encoder_f IPBinV6Address_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _IPBinV6Address_H_ */
#include <asn_internal.h>
