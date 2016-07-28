/*
 * Generated by asn1c-0.9.27 (http://lionet.info/asn1c)
 * From ASN.1 module "GPRSChargingDataTypes"
 * 	found in "./PGW_CDR_Format.asn"
 */

#ifndef	_DefaultGPRS_Handling_H_
#define	_DefaultGPRS_Handling_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum DefaultGPRS_Handling {
	DefaultGPRS_Handling_continueTransaction	= 0,
	DefaultGPRS_Handling_releaseTransaction	= 1
	/*
	 * Enumeration is extensible
	 */
} e_DefaultGPRS_Handling;

/* DefaultGPRS-Handling */
typedef long	 DefaultGPRS_Handling_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_DefaultGPRS_Handling;
asn_struct_free_f DefaultGPRS_Handling_free;
asn_struct_print_f DefaultGPRS_Handling_print;
asn_constr_check_f DefaultGPRS_Handling_constraint;
ber_type_decoder_f DefaultGPRS_Handling_decode_ber;
der_type_encoder_f DefaultGPRS_Handling_encode_der;
xer_type_decoder_f DefaultGPRS_Handling_decode_xer;
xer_type_encoder_f DefaultGPRS_Handling_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _DefaultGPRS_Handling_H_ */
#include <asn_internal.h>
