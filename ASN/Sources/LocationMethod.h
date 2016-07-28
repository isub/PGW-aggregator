/*
 * Generated by asn1c-0.9.27 (http://lionet.info/asn1c)
 * From ASN.1 module "GPRSChargingDataTypes"
 * 	found in "./PGW_CDR_Format.asn"
 */

#ifndef	_LocationMethod_H_
#define	_LocationMethod_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum LocationMethod {
	LocationMethod_msBasedEOTD	= 0,
	LocationMethod_msAssistedEOTD	= 1,
	LocationMethod_assistedGPS	= 2,
	/*
	 * Enumeration is extensible
	 */
	LocationMethod_msBasedOTDOA	= 3,
	LocationMethod_assistedGANSS	= 4,
	LocationMethod_assistedGPSandGANSS	= 5
} e_LocationMethod;

/* LocationMethod */
typedef long	 LocationMethod_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_LocationMethod;
asn_struct_free_f LocationMethod_free;
asn_struct_print_f LocationMethod_print;
asn_constr_check_f LocationMethod_constraint;
ber_type_decoder_f LocationMethod_decode_ber;
der_type_encoder_f LocationMethod_encode_der;
xer_type_decoder_f LocationMethod_decode_xer;
xer_type_encoder_f LocationMethod_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _LocationMethod_H_ */
#include <asn_internal.h>
