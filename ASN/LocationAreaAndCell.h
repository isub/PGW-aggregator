/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "GPRSChargingDataTypes"
 * 	found in "./PGW_CDR_Format.asn"
 */

#ifndef	_LocationAreaAndCell_H_
#define	_LocationAreaAndCell_H_


#include <asn_application.h>

/* Including external dependencies */
#include "LocationAreaCode.h"
#include "CellId.h"
#include "MCC-MNC.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* LocationAreaAndCell */
typedef struct LocationAreaAndCell {
	LocationAreaCode_t	 locationAreaCode;
	CellId_t	 cellId;
	MCC_MNC_t	*mCC_MNC	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} LocationAreaAndCell_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_LocationAreaAndCell;

#ifdef __cplusplus
}
#endif

#endif	/* _LocationAreaAndCell_H_ */
#include <asn_internal.h>
