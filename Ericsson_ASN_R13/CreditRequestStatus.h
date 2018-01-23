/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "GgsnPgwR13Ber"
 * 	found in "./pgw-r13.txt"
 */

#ifndef	_CreditRequestStatus_H_
#define	_CreditRequestStatus_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum CreditRequestStatus {
	CreditRequestStatus_unsent	= 0,
	CreditRequestStatus_noAnswer	= 1,
	CreditRequestStatus_failure	= 2
} e_CreditRequestStatus;

/* CreditRequestStatus */
typedef long	 CreditRequestStatus_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CreditRequestStatus;
asn_struct_free_f CreditRequestStatus_free;
asn_struct_print_f CreditRequestStatus_print;
asn_constr_check_f CreditRequestStatus_constraint;
ber_type_decoder_f CreditRequestStatus_decode_ber;
der_type_encoder_f CreditRequestStatus_encode_der;
xer_type_decoder_f CreditRequestStatus_decode_xer;
xer_type_encoder_f CreditRequestStatus_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _CreditRequestStatus_H_ */
#include <asn_internal.h>