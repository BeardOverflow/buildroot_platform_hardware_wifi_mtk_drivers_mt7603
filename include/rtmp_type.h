/*
 ***************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology 5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
 *
 * (c) Copyright 2002-2004, Ralink Technology, Inc.
 *
 * All rights reserved. Ralink's source code is an unpublished work and the
 * use of a copyright notice does not imply otherwise. This source code
 * contains confidential trade secret material of Ralink Tech. Any attemp
 * or participation in deciphering, decoding, reverse engineering or in any
 * way altering the source code is stricitly prohibited, unless the prior
 * written consent of Ralink Technology, Inc. is obtained.
 ***************************************************************************

    Module Name:
    rtmp_type.h

    Abstract:

    Revision History:
    Who         When            What
    --------    ----------      ----------------------------------------------
    Name        Date            Modification logs
    Paul Lin    1-2-2004
*/

#ifndef __RTMP_TYPE_H__
#define __RTMP_TYPE_H__

#ifdef VXWORKS
#ifdef VXWORKS_5X
#include <types/vxTypesOld.h>
#endif /* VXWORKS_5X */
#include <sys/types.h>
#endif /* VXWORKS */

#ifdef THREADX
#include "tx_port.h"
#ifdef SIGMATEL_SDK
#include "dc_type.h"		/* All modules that interface with the DigiColor */
#include "dc_return_codes.h"

/* 
	For threadx, the UINT64 has defined as a data structure, so here we use a wrapper 
	data type to redefine it 
*/
/*typedef unsigned long long UINT64; */
typedef unsigned long long RT_UINT64;
#define UINT64			RT_UINT64

typedef long long INT64;
#endif /* SIGMATEL_SDK */

typedef unsigned char UINT8;

typedef unsigned short UINT16;

typedef int INT32;
typedef unsigned int UINT32;
typedef long time_t;
typedef unsigned char u8;
#endif /* THREADX */

#ifndef GNU_PACKED
#define GNU_PACKED  __attribute__ ((packed))
#endif /* GNU_PACKED */

#ifdef __ECOS
#include "os/rt_ecos_type.h"
#else

#ifdef LINUX
/* Put platform dependent declaration here */
/* For example, linux type definition */
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned long long UINT64;
typedef signed short INT16;
typedef signed int INT32;
typedef signed long long INT64;

typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned int UINT;
typedef unsigned long ULONG;
#endif /* LINUX */

typedef unsigned char *PUINT8;
typedef unsigned short *PUINT16;
typedef unsigned int *PUINT32;
typedef unsigned long long *PUINT64;
typedef signed int *PINT32;
typedef signed long long *PINT64;

/* modified for fixing compile warning on Sigma 8634 platform */
//typedef char STRING;
typedef char RTMP_STRING;

#ifndef THREADX
typedef signed char CHAR;
#endif /* THREADX */

typedef signed short SHORT;
typedef signed int INT;
typedef signed long LONG;
typedef signed long long LONGLONG;

typedef unsigned long long ULONGLONG;

typedef unsigned char BOOLEAN;

#ifdef LINUX
typedef void VOID;
#endif /* LINUX */

//typedef char *PSTRING;
typedef VOID *PVOID;
typedef CHAR *PCHAR;
typedef UCHAR *PUCHAR;
typedef USHORT *PUSHORT;
typedef LONG *PLONG;
typedef ULONG *PULONG;
typedef UINT *PUINT;
#endif /* __ECOS */

typedef unsigned int NDIS_MEDIA_STATE;

typedef union _LARGE_INTEGER {
	struct {
#ifdef RT_BIG_ENDIAN
		INT32 HighPart;
		UINT LowPart;
#else
		UINT LowPart;
		INT32 HighPart;
#endif
	} u;
	INT64 QuadPart;
} LARGE_INTEGER;


/* Register set pair for initialzation register set definition */
typedef struct _RTMP_REG_PAIR {
	UINT32 Register;
	UINT32 Value;
} RTMP_REG_PAIR, *PRTMP_REG_PAIR;

typedef struct _MT_RF_REG_PAIR {
	UINT8 WiFiStream;
	UINT32 Register;
	UINT32 Value;
} MT_RF_REG_PAIR;

typedef struct _REG_PAIR {
	UCHAR Register;
	UCHAR Value;
} REG_PAIR, *PREG_PAIR;

typedef struct _REG_PAIR_CHANNEL {
	UCHAR Register;
	UCHAR FirstChannel;
	UCHAR LastChannel;
	UCHAR Value;
} REG_PAIR_CHANNEL, *PREG_PAIR_CHANNEL;

typedef struct _REG_PAIR_BW {
	UCHAR Register;
	UCHAR BW;
	UCHAR Value;
} REG_PAIR_BW, *PREG_PAIR_BW;


typedef struct _REG_PAIR_PHY{
	UCHAR reg;
	UCHAR s_ch;
	UCHAR e_ch;
	UCHAR phy;	/* RF_MODE_XXX */
	UCHAR bw;	/* RF_BW_XX */
	UCHAR val;
}REG_PAIR_PHY;


/* Register set pair for initialzation register set definition */
typedef struct _RTMP_RF_REGS {
	UCHAR Channel;
	UINT32 R1;
	UINT32 R2;
	UINT32 R3;
	UINT32 R4;
} RTMP_RF_REGS, *PRTMP_RF_REGS;

typedef struct _FREQUENCY_ITEM {
	UCHAR Channel;
	UCHAR N;
	UCHAR R;
	UCHAR K;
} FREQUENCY_ITEM, *PFREQUENCY_ITEM;

typedef int NTSTATUS;

#define STATUS_SUCCESS			0x00
#define STATUS_UNSUCCESSFUL 	0x01

typedef struct _QUEUE_ENTRY {
	struct _QUEUE_ENTRY *Next;
} QUEUE_ENTRY, *PQUEUE_ENTRY;

/* Queue structure */
typedef struct _QUEUE_HEADER {
	PQUEUE_ENTRY Head;
	PQUEUE_ENTRY Tail;
	UINT Number;
} QUEUE_HEADER, *PQUEUE_HEADER;

typedef struct _CR_REG {
	UINT32 flags;
	UINT32 offset;	
	UINT32 value;
} CR_REG, *PCR_REG;

typedef struct _BANK_RF_CR_REG {
	UINT32 flags;
	UCHAR bank;
	UCHAR offset;
	UCHAR value;
} BANK_RF_CR_REG, *PBANK_RF_CR_REG;


typedef struct _BANK_RF_REG_PAIR {
	UCHAR Bank;
	UCHAR Register;
	UCHAR Value;
} BANK_RF_REG_PAIR, *PBANK_RF_REG_PAIR;

typedef struct _R_M_W_REG{
	UINT32 Register;
	UINT32 ClearBitMask;
	UINT32 Value;
} R_M_W_REG, *PR_M_W_REG;

typedef struct _RF_R_M_W_REG{
	UCHAR Bank;
	UCHAR Register;
	UCHAR ClearBitMask;
	UCHAR Value;
} RF_R_M_W_REG, *PRF_R_M_W_REG;

struct mt_dev_priv{
	void *sys_handle;
	void *wifi_dev;
	unsigned long priv_flags;
	UCHAR sniffer_mode;
};

#endif /* __RTMP_TYPE_H__ */

