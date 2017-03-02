/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "GPRSChargingDataTypes"
 * 	found in "./PGW_CDR_Format.asn"
 */

#ifndef	_UnauthorizedLCSClient_Diagnostic_H_
#define	_UnauthorizedLCSClient_Diagnostic_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum UnauthorizedLCSClient_Diagnostic {
	UnauthorizedLCSClient_Diagnostic_noAdditionalInformation	= 0,
	UnauthorizedLCSClient_Diagnostic_clientNotInMSPrivacyExceptionList	= 1,
	UnauthorizedLCSClient_Diagnostic_callToClientNotSetup	= 2,
	UnauthorizedLCSClient_Diagnostic_privacyOverrideNotApplicable	= 3,
	UnauthorizedLCSClient_Diagnostic_disallowedByLocalRegulatoryRequirements	= 4,
	/*
	 * Enumeration is extensible
	 */
	UnauthorizedLCSClient_Diagnostic_unauthorizedPrivacyClass	= 5,
	UnauthorizedLCSClient_Diagnostic_unauthorizedCallSessionUnrelatedExternalClient	= 6,
	UnauthorizedLCSClient_Diagnostic_unauthorizedCallSessionRelatedExternalClient	= 7
} e_UnauthorizedLCSClient_Diagnostic;

/* UnauthorizedLCSClient-Diagnostic */
typedef long	 UnauthorizedLCSClient_Diagnostic_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UnauthorizedLCSClient_Diagnostic;
asn_struct_free_f UnauthorizedLCSClient_Diagnostic_free;
asn_struct_print_f UnauthorizedLCSClient_Diagnostic_print;
asn_constr_check_f UnauthorizedLCSClient_Diagnostic_constraint;
ber_type_decoder_f UnauthorizedLCSClient_Diagnostic_decode_ber;
der_type_encoder_f UnauthorizedLCSClient_Diagnostic_encode_der;
xer_type_decoder_f UnauthorizedLCSClient_Diagnostic_decode_xer;
xer_type_encoder_f UnauthorizedLCSClient_Diagnostic_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _UnauthorizedLCSClient_Diagnostic_H_ */
#include <asn_internal.h>
