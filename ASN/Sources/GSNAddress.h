/*
 * Generated by asn1c-0.9.27 (http://lionet.info/asn1c)
 * From ASN.1 module "GPRSChargingDataTypes"
 * 	found in "./PGW_CDR_Format.asn"
 */

#ifndef	_GSNAddress_H_
#define	_GSNAddress_H_


#include <asn_application.h>

/* Including external dependencies */
#include "IPAddress.h"

#ifdef __cplusplus
extern "C" {
#endif

/* GSNAddress */
typedef IPAddress_t	 GSNAddress_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_GSNAddress;
asn_struct_free_f GSNAddress_free;
asn_struct_print_f GSNAddress_print;
asn_constr_check_f GSNAddress_constraint;
ber_type_decoder_f GSNAddress_decode_ber;
der_type_encoder_f GSNAddress_encode_der;
xer_type_decoder_f GSNAddress_decode_xer;
xer_type_encoder_f GSNAddress_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _GSNAddress_H_ */
#include <asn_internal.h>
