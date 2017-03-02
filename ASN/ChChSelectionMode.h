/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "GPRSChargingDataTypes"
 * 	found in "./PGW_CDR_Format.asn"
 */

#ifndef	_ChChSelectionMode_H_
#define	_ChChSelectionMode_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ChChSelectionMode {
	ChChSelectionMode_servingNodeSupplied	= 0,
	ChChSelectionMode_subscriptionSpecific	= 1,
	ChChSelectionMode_aPNSpecific	= 2,
	ChChSelectionMode_homeDefault	= 3,
	ChChSelectionMode_roamingDefault	= 4,
	ChChSelectionMode_visitingDefault	= 5
} e_ChChSelectionMode;

/* ChChSelectionMode */
typedef long	 ChChSelectionMode_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ChChSelectionMode;
asn_struct_free_f ChChSelectionMode_free;
asn_struct_print_f ChChSelectionMode_print;
asn_constr_check_f ChChSelectionMode_constraint;
ber_type_decoder_f ChChSelectionMode_decode_ber;
der_type_encoder_f ChChSelectionMode_encode_der;
xer_type_decoder_f ChChSelectionMode_decode_xer;
xer_type_encoder_f ChChSelectionMode_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _ChChSelectionMode_H_ */
#include <asn_internal.h>
