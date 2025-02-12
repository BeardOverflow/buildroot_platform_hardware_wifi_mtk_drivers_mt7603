/*
 ***************************************************************************
 * Ralink Tech Inc.
 * 4F, No. 2 Technology	5th Rd.
 * Science-based Industrial Park
 * Hsin-chu, Taiwan, R.O.C.
 *
 * (c) Copyright 2002-2004, Ralink Technology, Inc.
 *
 * All rights reserved.	Ralink's source	code is	an unpublished work and the
 * use of a copyright notice does not imply otherwise. This source code
 * contains confidential trade secret material of Ralink Tech. Any attemp
 * or participation in deciphering, decoding, reverse engineering or in any
 * way altering	the source code	is stricitly prohibited, unless	the prior
 * written consent of Ralink Technology, Inc. is obtained.
 ***************************************************************************

	Module Name:
	mt_mac.h

	Abstract:
	Ralink Wireless Chip MAC related definition & structures

	Revision History:
	Who			When		  What
	--------	----------	  ----------------------------------------------
*/

#ifndef __MT_MAC_H__
#define __MT_MAC_H__

#include "mac/mac_mt/top.h"
#include "mac/mac_mt/gpio.h"
#include "mac/mac_mt/wf_agg.h"
#include "mac/mac_mt/wf_aon.h"
#include "mac/mac_mt/wf_arb.h"
#include "mac/mac_mt/wf_cfgoff.h"
#include "mac/mac_mt/wf_dma.h"
#include "mac/mac_mt/wf_lpon_top.h"
#include "mac/mac_mt/wf_mib.h"
#include "mac/mac_mt/wf_pf.h"
#include "mac/mac_mt/wf_rmac.h"
#include "mac/mac_mt/wf_sec.h"
#include "mac/mac_mt/wf_tmac.h"
#include "mac/mac_mt/wf_trb.h"
#include "mac/mac_mt/wf_wtbloff.h"
#include "mac/mac_mt/wf_wtblon.h"
#include "mac/mac_mt/wf_int_wakeup_top.h"
#include "mac/mac_mt/client.h"
#include "mac/mac_mt/wf_wtbl.h"
#include "mac/mac_mt/wf_phy.h"
#include "mac/mac_mt/pse.h"
#ifdef RTMP_MAC_PCI
#include "mac/mac_mt/mt_mac_pci.h"
#endif /* RTMP_MAC_PCI */

#ifdef RTMP_MAC_USB
#include "mac/mac_mt/mt_mac_usb.h"
#endif /* RTMP_MAC_USB */

#ifdef RTMP_MAC_SDIO
#include "mac/mac_mt/mt_mac_sdio.h"
#endif /* RTMP_MAC_SDIO */


/*
	TX / RX descriptor format

	TX:
		PCI/RBUS_DMA_Descriptor + TXD + 802.11

	Rx:
		PCI/RBUS/USB_DMA_Descripotr + RXD + 802.11 + RX_CSO_INFO
*/

/* the first 24-byte in TXD is called TXINFO and will be DMAed to MAC block through TXFIFO. */
/* MAC block use this TXINFO to control the transmission behavior of this frame. */
#define FIFO_MGMT	0
#define FIFO_HCCA	1
#define FIFO_EDCA	2

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED tmac_txd_0 {
	/*  DWORD 0 */
	UINT32 p_idx:1;             /*  P_IDX_XXX */
	UINT32 q_idx:4;             /*  Q_IDX_XXX */
	UINT32 UTxB:1;
	UINT32 UNxV:1;
	UINT32 ut_sum:1;
	UINT32 ip_sum:1;
	UINT32 eth_type_offset:7;
	UINT32 tx_byte_cnt:16;
} TMAC_TXD_0;
#else
typedef struct GNU_PACKED tmac_txd_0 {
	/* DWORD 0 */
	UINT32 tx_byte_cnt:16; 		/* in unit of bytes */
	UINT32 eth_type_offset:7;		/* in unit of WORD(2 bytes) */
	UINT32 ip_sum:1;
	UINT32 ut_sum:1;
	UINT32 UNxV:1;
	UINT32 UTxB:1;
	UINT32 q_idx:4;				/* Q_IDX_XXX */
	UINT32 p_idx:1;				/* P_IDX_XXX */
} TMAC_TXD_0;
#endif

/* TMAC_TXD_0.p_idx */
#define P_IDX_LMAC	0
#define P_IDX_MCU	1

/* TMAC_TXD_0.q_idx */
#define Q_IDX_AC0	0x00
#define Q_IDX_AC1	0x01
#define Q_IDX_AC2	0x02
#define Q_IDX_AC3	0x03
#define Q_IDX_AC4	0x04
#define Q_IDX_AC5	0x05
#define Q_IDX_AC6	0x06
#define Q_IDX_BCN	0x07
#define Q_IDX_BMC	0x08
#define Q_IDX_AC10	0x09
#define Q_IDX_AC11	0x0a
#define Q_IDX_AC12	0x0b
#define Q_IDX_AC13	0x0c
#define Q_IDX_AC14	0x0d

#define Q_IDX_RQ0	0x00
#define Q_IDX_RQ1	0x01
#define Q_IDX_RQ2	0x02
#define Q_IDX_RQ3	0x03

/* TMAC_TXD_0.p_idx +  TMAC_TXD_0.q_idx */
#define PQ_IDX_LMAC_AC0	(P_IDX_LMAC << 4) | (Q_IDX_AC0)
#define PQ_IDX_LMAC_AC1	(P_IDX_LMAC << 4) | (Q_IDX_AC1)
#define PQ_IDX_LMAC_AC2	(P_IDX_LMAC << 4) | (Q_IDX_AC2)
#define PQ_IDX_LMAC_AC3	(P_IDX_LMAC << 4) | (Q_IDX_AC3)
#define PQ_IDX_LMAC_AC4	(P_IDX_LMAC << 4) | (Q_IDX_AC4)
#define PQ_IDX_LMAC_AC5	(P_IDX_LMAC << 4) | (Q_IDX_AC5)
#define PQ_IDX_LMAC_AC6	(P_IDX_LMAC << 4) | (Q_IDX_AC6)
#define PQ_IDX_LMAC_BCN	(P_IDX_LMAC << 4) | (Q_IDX_BCN)
#define PQ_IDX_LMAC_BMC	(P_IDX_LMAC << 4) | (Q_IDX_BMC)
#define PQ_IDX_LMAC_AC10	(P_IDX_LMAC << 4) | (Q_IDX_AC10)
#define PQ_IDX_LMAC_AC11	(P_IDX_LMAC << 4) | (Q_IDX_AC11)
#define PQ_IDX_LMAC_AC12	(P_IDX_LMAC << 4) | (Q_IDX_AC12)
#define PQ_IDX_LMAC_AC13	(P_IDX_LMAC << 4) | (Q_IDX_AC13)
#define PQ_IDX_LMAC_AC14	(P_IDX_LMAC << 4) | (Q_IDX_AC14)

#define PQ_IDX_MCU_RQ0		(P_IDX_MCU << 4) | (Q_IDX_RQ0)
#define PQ_IDX_MCU_RQ1		(P_IDX_MCU << 4) | (Q_IDX_RQ1)
#define PQ_IDX_MCU_RQ2		(P_IDX_MCU << 4) | (Q_IDX_RQ2)
#define PQ_IDX_MCU_RQ3		(P_IDX_MCU << 4) | (Q_IDX_RQ3)

#ifdef MAC_REPEATER_SUPPORT
#define MAX_EXT_MAC_ADDR_SIZE	16
//TODO: Carter, single driver case?
#ifdef MT7628
#undef MAX_EXT_MAC_ADDR_SIZE
#defined MAX_EXT_MAC_ADDR_SIZE 24
#endif /* MT7628*/
#endif /* MAC_REPEATER_SUPPORT */

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED tmac_txd_1 {
	/* DWORD 1 */
	UINT32 own_mac:6;
	UINT32 rsv_1_24:2;
	UINT32 protect_frm:1;
	UINT32 tid:3;
	UINT32 no_ack:1;
	UINT32 hdr_pad:3;
	UINT32 ft:1;					/* TMI_FT_XXXX */
	UINT32 hdr_format:2;			/* TMI_HDR_FT_XXX */
	UINT32 hdr_info:5;			/* in unit of WORD(2 bytes) */
	UINT32 wlan_idx:8;
} TMAC_TXD_1;
#else
typedef struct GNU_PACKED tmac_txd_1 {
	/* DWORD 1 */
	UINT32 wlan_idx:8;
	UINT32 hdr_info:5;			/* in unit of WORD(2 bytes) */
	UINT32 hdr_format:2;			/* TMI_HDR_FT_XXX */
	UINT32 ft:1;					/* TMI_FT_XXXX */
	UINT32 hdr_pad:3;
	UINT32 no_ack:1;
	UINT32 tid:3;
	UINT32 protect_frm:1;
	UINT32 rsv_1_24:2;
	UINT32 own_mac:6;
} TMAC_TXD_1;
#endif

/* TMAC_TXD_1.hdr_format */
#define TMI_HDR_FT_NON_80211	0x0
#define TMI_HDR_FT_CMD		0x1
#define TMI_HDR_FT_NOR_80211	0x2
#define TMI_HDR_FT_ENH_80211	0x3

/*
	TMAC_TXD_1.hdr_info
*/
/* if TMAC_TXD_1.hdr_format  == HDR_FORMAT_NON_80211 */
#define TMI_HDR_INFO_0_BIT_MRD		0
#define TMI_HDR_INFO_0_BIT_EOSP		1
#define TMI_HDR_INFO_0_BIT_RMVL		2
#define TMI_HDR_INFO_0_BIT_VLAN		3
#define TMI_HDR_INFO_0_BIT_ETYP		4
#define TMI_HDR_INFO_0_VAL(_mrd, _eosp, _rmvl, _vlan, _etyp)	\
			((((_mrd) ? 1 : 0) << TMI_HDR_INFO_0_BIT_MRD) | \
			(((_eosp) ? 1 : 0) << TMI_HDR_INFO_0_BIT_EOSP) |\
			(((_rmvl) ? 1 : 0) << TMI_HDR_INFO_0_BIT_RMVL) |\
			(((_vlan) ? 1 : 0) << TMI_HDR_INFO_0_BIT_VLAN) |\
			(((_etyp) ? 1 : 0) << TMI_HDR_INFO_0_BIT_ETYP))


/* if TMAC_TXD_1.hdr_format  == HDR_FORMAT_CMD */
#define TMI_HDR_INFO_1_MASK_RSV		(0x1f)
#define TMI_HDR_INFO_1_VAL			0

/* if TMAC_TXD_1.hdr_format  == HDR_FORMAT_NOR_80211 */
#define TMI_HDR_INFO_2_MASK_LEN	(0x1f)
#define TMI_HDR_INFO_2_VAL(_len)	(_len >> 1)

/* if TMAC_TXD_1.hdr_format  == HDR_FORMAT_ENH_80211 */
#define TMI_HDR_INFO_3_BIT_EOSP	1
#define TMI_HDR_INFO_3_BIT_AMS	2
#define TMI_HDR_INFO_3_VAL(_eosp, _ams)	\
			((((_eosp) ? 1 : 0) << TMI_HDR_INFO_3_BIT_EOSP) | \
			(((_ams) ? 1 : 0) << TMI_HDR_INFO_3_BIT_AMS))

#define TMI_HDR_INFO_VAL(_fmt, _mrd, _eosp, _rmvl, _vlan, _etype, _len, _ams, _val)	\
		do{\
			switch (_fmt) {\
				case TMI_HDR_FT_NON_80211:\
					(_val) = TMI_HDR_INFO_0_VAL((_mrd), (_eosp), (_rmvl), (_vlan), (_etype));\
					break;\
				case TMI_HDR_FT_CMD:\
					(_val) = TMI_HDR_INFO_1_VAL;\
					break;\
				case TMI_HDR_FT_NOR_80211:\
					ASSERT((((_len) & 1) == 0));\
					(_val) = TMI_HDR_INFO_2_VAL((_len));\
					break;\
				case TMI_HDR_FT_ENH_80211:\
					(_val) = TMI_HDR_INFO_3_VAL((_eosp), (_ams));\
					__attribute__((__fallthrough__));/* FALL THRU */\
				default:\
					(_val) = 0;\
			}\
		}while(0)


/* TMAC_TXD_1.ft */
#define TMI_FT_SHORT	0
#define TMI_FT_LONG		1


/* TMAC_TXD_1.hdr_pad */
#define TMI_HDR_PAD_BIT_MODE		2
#define TMI_HDR_PAD_MODE_TAIL		0
#define TMI_HDR_PAD_MODE_HEAD	1
#define TMI_HDR_PAD_BIT_LEN	0
#define TMI_HDR_PAD_MASK_LEN	0x3

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED tmac_txd_2 {
	/* DWORD 2 */
	UINT32 fix_rate:1;
	UINT32 timing_measure:1;
	UINT32 ba_disable:1;
	UINT32 pwr_offset:5;
	UINT32 max_tx_time:8;
	UINT32 frag:2;
	UINT32 htc_vld:1;
	UINT32 duration:1;
	UINT32 bip:1;
	UINT32 bc_mc_pkt:1;
	UINT32 rts:1;
	UINT32 sounding:1;
	UINT32 ndpa:1;
	UINT32 ndp:1;
	UINT32 frm_type:2;
	UINT32 sub_type:4;
} TMAC_TXD_2;
#else
typedef struct GNU_PACKED tmac_txd_2 {
	/* DWORD 2 */
	UINT32 sub_type:4;
	UINT32 frm_type:2;
	UINT32 ndp:1;
	UINT32 ndpa:1;
	UINT32 sounding:1;
	UINT32 rts:1;
	UINT32 bc_mc_pkt:1;
	UINT32 bip:1;
	UINT32 duration:1;
	UINT32 htc_vld:1;
	UINT32 frag:2;
	UINT32 max_tx_time:8;
	UINT32 pwr_offset:5;
	UINT32 ba_disable:1;
	UINT32 timing_measure:1;
	UINT32 fix_rate:1;
} TMAC_TXD_2;
#endif

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED tmac_txd_3 {
	/* DWORD 3 */
	UINT32 sn_vld:1;
	UINT32 pn_vld:1;
	UINT32 rsv3_28:2;
	UINT32 sn:12;
	UINT32 remain_tx_cnt:5;
	UINT32 tx_cnt:5;
	UINT32 rsv3_0:6;
} TMAC_TXD_3;
#else
typedef struct GNU_PACKED tmac_txd_3 {
	/* DWORD 3 */
	UINT32 rsv3_0:6;
	UINT32 tx_cnt:5;
	UINT32 remain_tx_cnt:5;
	UINT32 sn:12;
	UINT32 rsv3_28:2;
	UINT32 pn_vld:1;
	UINT32 sn_vld:1;
} TMAC_TXD_3;
#endif

typedef struct GNU_PACKED tmac_txd_4 {
	/* DWORD 4 */
	UINT32 pn_low;
} TMAC_TXD_4;


#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED tmac_txd_5 {
	/* DWORD 5 */
	UINT32 pn_high:16;
	UINT32 rsv5_14:2;
	UINT32 pwr_mgmt:1;
	UINT32 bar_sn_ctrl:1;
	UINT32 da_select:1;
	UINT32 tx_status_2_host:1;
	UINT32 tx_status_2_mcu:1;
	UINT32 tx_status_fmt:1;
	UINT32 pid:8;
} TMAC_TXD_5;
#else
typedef struct GNU_PACKED tmac_txd_5 {
	/* DWORD 5 */
	UINT32 pid:8;
	UINT32 tx_status_fmt:1;
	UINT32 tx_status_2_mcu:1;
	UINT32 tx_status_2_host:1;
	UINT32 da_select:1;
	UINT32 bar_sn_ctrl:1;
	UINT32 pwr_mgmt:1;
	UINT32 rsv5_14:2;
	UINT32 pn_high:16;
} TMAC_TXD_5;
#endif

/* TMAC_TXD_5.da_select */
#define TMI_DAS_FROM_MPDU		0
#define TMI_DAS_FROM_WTBL		1

/* TMAC_TXD_5.bar_sn_ctrl */
#define TMI_BSN_CFG_BY_HW	0
#define TMI_BSN_CFG_BY_SW	1

/* TMAC_TXD_5.pwr_mgmt */
#define TMI_PM_BIT_CFG_BY_HW	0
#define TMI_PM_BIT_CFG_BY_SW	1


#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED tmac_txd_6 {
	/* DWORD 6 */
	UINT32 gi:1;
	UINT32 ldpc:1;
	UINT32 tx_rate:12;
	UINT32 ITxBF:1;
	UINT32 ETxBF:1;
	UINT32 dyn_bw:1;
	UINT32 ant_pri:3;
	UINT32 spe_en:1;
	UINT32 bw:3;
	UINT32 ant_id:6;
	UINT32 rsv_6_1:1;
	UINT32 fix_rate_mode:1;
} TMAC_TXD_6;
#else
typedef struct GNU_PACKED tmac_txd_6 {
	/* DWORD 6 */
	UINT32 fix_rate_mode:1;
	UINT32 rsv_6_1:1;
	UINT32 ant_id:6;
	UINT32 bw:3;
	UINT32 spe_en:1;
	UINT32 ant_pri:3;
	UINT32 dyn_bw:1;
	UINT32 ETxBF:1;
	UINT32 ITxBF:1;
	UINT32 tx_rate:12;
	UINT32 ldpc:1;
	UINT32 gi:1;
} TMAC_TXD_6;
#endif

/* TXD_L_STRUC.fix_rate_mode */
#define TMI_FIX_RATE_BY_TXD	0
#define TMI_FIX_RATE_BY_CR		1

#define TMI_TX_RATE_BIT_STBC		11
#define TMI_TX_RATE_BIT_NSS		9
#define TMI_TX_RATE_MASK_NSS		0x3

#define TMI_TX_RATE_BIT_MODE		6
#define TMI_TX_RATE_MASK_MODE	0x7
#define TMI_TX_RATE_MODE_CCK		0
#define TMI_TX_RATE_MODE_OFDM	1
#define TMI_TX_RATE_MODE_HTMIX	2
#define TMI_TX_RATE_MODE_HTGF		3
#define TMI_TX_RATE_MODE_VHT		4

#define SHORT_PREAMBLE 0
#define LONG_PREAMBLE 1

#define TMI_TX_RATE_BIT_MCS		0
#define TMI_TX_RATE_MASK_MCS		0x3f
#define TMI_TX_RATE_CCK_1M_LP		0
#define TMI_TX_RATE_CCK_2M_LP		1
#define TMI_TX_RATE_CCK_5M_LP		2
#define TMI_TX_RATE_CCK_11M_LP	3

#define TMI_TX_RATE_CCK_2M_SP		5
#define TMI_TX_RATE_CCK_5M_SP		6
#define TMI_TX_RATE_CCK_11M_SP	7

#define TMI_TX_RATE_OFDM_6M		11
#define TMI_TX_RATE_OFDM_9M		15
#define TMI_TX_RATE_OFDM_12M		10
#define TMI_TX_RATE_OFDM_18M		14
#define TMI_TX_RATE_OFDM_24M		9
#define TMI_TX_RATE_OFDM_36M		13
#define TMI_TX_RATE_OFDM_48M		8
#define TMI_TX_RATE_OFDM_54M		12

#define TMI_TX_RATE_HT_MCS0		0
#define TMI_TX_RATE_HT_MCS1		1
#define TMI_TX_RATE_HT_MCS2		2
#define TMI_TX_RATE_HT_MCS3		3
#define TMI_TX_RATE_HT_MCS4		4
#define TMI_TX_RATE_HT_MCS5		5
#define TMI_TX_RATE_HT_MCS6		6
#define TMI_TX_RATE_HT_MCS7		7
#define TMI_TX_RATE_HT_MCS8		8
#define TMI_TX_RATE_HT_MCS9		9
#define TMI_TX_RATE_HT_MCS10		10
#define TMI_TX_RATE_HT_MCS11		11
#define TMI_TX_RATE_HT_MCS12		12
#define TMI_TX_RATE_HT_MCS13		13
#define TMI_TX_RATE_HT_MCS14		14
#define TMI_TX_RATE_HT_MCS15		15
#define TMI_TX_RATE_HT_MCS16		16
#define TMI_TX_RATE_HT_MCS17		17
#define TMI_TX_RATE_HT_MCS18		18
#define TMI_TX_RATE_HT_MCS19		19
#define TMI_TX_RATE_HT_MCS20		20
#define TMI_TX_RATE_HT_MCS21		21
#define TMI_TX_RATE_HT_MCS22		22
#define TMI_TX_RATE_HT_MCS23		23

#define TMI_TX_RATE_HT_MCS32		32

#define TMI_TX_RATE_VHT_MCS0		0
#define TMI_TX_RATE_VHT_MCS1		1
#define TMI_TX_RATE_VHT_MCS2		2
#define TMI_TX_RATE_VHT_MCS3		3
#define TMI_TX_RATE_VHT_MCS4		4
#define TMI_TX_RATE_VHT_MCS5		5
#define TMI_TX_RATE_VHT_MCS6		6
#define TMI_TX_RATE_VHT_MCS7		7
#define TMI_TX_RATE_VHT_MCS8		8
#define TMI_TX_RATE_VHT_MCS9		9


#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED tmac_txd_7 {
	/* DWORD 7 */
	UINT32 sw_field:16;
	UINT32 sch_tx_time:16;
} TMAC_TXD_7;
#else
typedef struct GNU_PACKED tmac_txd_7 {
	/* DWORD 7 */
	UINT32 sch_tx_time:16;
	UINT32 sw_field:16;
} TMAC_TXD_7;
#endif

/*
	TX Descriptor in Long Format (TMAC_TXD_1.FT = 1)
*/
typedef struct GNU_PACKED _TMAC_TXD_L {
	TMAC_TXD_0 txd_0;
	TMAC_TXD_1 txd_1;
	TMAC_TXD_2 txd_2;
	TMAC_TXD_3 txd_3;
	TMAC_TXD_4 txd_4;
	TMAC_TXD_5 txd_5;
	TMAC_TXD_6 txd_6;
#if defined(MT7603) || defined(MT7628) || defined(MT7636)
	TMAC_TXD_7 txd_7;
#endif /* MT7603 */
} TMAC_TXD_L;


/*
	TX Descriptor in Short Format (TMAC_TXD_1.FT = 0)
*/
typedef struct GNU_PACKED _TMAC_TXD_S {
	TMAC_TXD_0 txd_0;
	TMAC_TXD_1 txd_1;
#if defined(MT7603) || defined(MT7628) || defined(MT7636)
	TMAC_TXD_7 txd_7;
#endif /* MT7603 */
} TMAC_TXD_S;



#ifdef RELEASE_EXCLUDE
/*
DWORD 0 ==>
	rx_byte_cnt(RX Byte count): in unit of byte
			The length includes RX status, Header padding, header, and payload
	eth_type_offset(Ether-Type Offset): in unit of WORD
			Indicates the offset of Ether-Type field from the first byte of the
				tx data structure.
			This field is meaningful ONLY when ut_sum(UT) or ip_sum(I) field is 1
	ip_sum(I): Request to do IP checksum offload
			When set, this bit indicates the HW IP checksum check is needed and
			the result will pad in the last DW
	ut_sum(UT): Request to do UDP/TCP checksum offload
			When set, this bit indicates the HW UDP/TCP checksum check is needed
			and the result will pad in the last DW
	grp_vld(GROUP_VLD): RFB Group valid indicators
			Bit[0] =>indicate GROUP 1(DW8~DW11)
			Bit[1] =>indicate GROUP 2(DW12~DW13)
			Bit[2] =>indicate GROUP 3(DW14~DW19)
			Bit[3] =>indicate GROUP 4(DW4~DW7)
			1'b0: the related GROUP is not present
			1'b1: the related GROUP is present
	pkt_type(PKT_TYPE):
			This field could be 3'h2(RX) or 3'h3(Duplicate RFB)

DWORD 1 ==>
	htc_vld(HTC): HTC field is valid
	u2m(UC2ME): Unicast to ME frame
	mcast(MC): Multicast frame
	bcast(BC): Broadcast frame
	beacon_mc(Beacon with BC/MC(BBM)):
			Indicate the beacon with BC/MC indication when
				MPTCR.BCN_PARSE_TIM_EN asserted
	beacon_uc(Beacon with Unicast (BU)):
			Indicate the beacon with UC indication when
				MPTCR. BCN_PARSE_TIM_EN asserted
	key_id(Key ID (KID)): Indicates the matched Key ID
	ch_freq(Channel Frequency):
			Indicate the channel frequency for this packet. The coding rule will
			follow RF frequency register definition.
	mac_hdr_len(MAC Header Length): in units of byte
			the header length
	hdr_offset(Header_Offset (HO)):
			This field indicates the padding byte count of header in unit of byte.
				1'b0: no padding
				1'b1: the padding length is 2 bytes
	hdr_trans(H):
			1'b0: original 802.11 header
			1'b1: received frame is performed by HW RX header translation.
				If WF_DMA.DCR0.RX_HDR_TRANS_MODE is 0: Ethernet / 802.3 header.
				If WF_DMA.DCR0.RX_HDR_TRANS_MODE is 1: Enhanced 802.11 header (non-QoS Data)
	payload_format(PF):
			2'b00: the payload is a MSDU
			2'b11: the payload is from the first sub frame of an A-MSDU
			2'b10: the payload is from a sub frame of an A-MSDU and it's neither the first nor the final.
			2'b01: the payload is from the final sub frame of an A-MSDU
	bssid(BSSID): indicate the matched BSSID
			6'h00: BSSID0 / InfraAP BSSID00
			6'h01: BSSID1
			6'h02: BSSID2
			6'h03: BSSID3
			6'h07: Not match any BSSID
			6'h11: InfraAP BSSID01
			...
			6'h1F: InfraAP BSSID0F
			6'h20: The RootAP BSSID of CloneMAC0 (for repeater mode only)
			6'h21: The RootAP BSSID of CloneMAC1 (for repeater mode only)
			...
			6'h2F: The RootAP BSSID of CloneMACF (for repeater mode only)
			Others: Reserved

DWORD 2 ==>
	wlan_idx(WLAN Index):
			If HW needs to search the WTBL,
						report the matched index,
						if no entry was matched, report 255.
			If HW doesn't need to search the WTBL, always report 255.
			The WTBL search rules can refer to WTBL chapter.
	tid(TID):
			RX packet is an QoS Data frame: = TID field in QoS control field.
			RX packet is not an QoS Data frame: = 0
	sec_mode(SEC_mode): Security engine operation mode
			4'h0: None
			4'h1: WEP-40
			4'h2: TKIP w/ MIC
			4'h3: TKIP w/o MIC
			4'h4: CCMP w/ MIC
			4'h5: WEP-104
			4'h6: BIP
			4'h7: WEP-128
			4'h8: WPI
			4'h9: CCMP with CCX
			4'hA: GCMP
	sw_bit(SWBIT): software assigned bit in WTBL
	fcs_err(FCS_Error (FC)): indicates the received frame contains FCS error
	format_err(Format_Error (FM)):
			it indicates the received frame containing frame format error
			 a). Length is too short for decryption or
			 b). cipher suit does not match (pf bit set but cipher suit = none or pf bit not set but cipher suit = cipher)).
			The WLAN Index, SEC_mode, Key ID should contain correct values
	icv_err(ICV_Error (I)):
			Indicates the received frame contains ICV error or CCMP/BIP/WPI MIC error.
			This error might also combine with other error status bit
	mic_err(TKIPMIC_error (T)):
			indicates the received frame containing TKIP MIC error.
			If fragment frame is received, then MT6620will not check the MIC,
				and will not indicate this TKIP MIC error.
			This error might also combine with other error status bit.
	len_mismatch(LM):
			Length mismatch
	de_amsdu_err(DAMSDU Fail (DAF)):
			This bit indicates the DAMSDU is failed.
				Case #1: the sub-frame length is too short.
				Case #2: the sub-frame length is more than the remaining packet length.
			1 => the AMSDU sub-frame is abnormal.
			0 => the AMSDU sub-frame is correct and it can be De-AMSDU.
	exceed_max_rx_len(Exceed MAX. RX length (EL)):
			If the RX packet exceeds the allowed maximum RX length, the packet payload
			will be drop, the packet header (ONLY when the header length is less than max RX length)
			and the RX status will be written to SYSRAM with this bit asserted.
	llc_mis(LLC-MIS):
			Indicate that the RX header translation can't find pre-defined
			LLC-SNAP pattern and the result packet type is 802.3.
			(this field is meaningful only when H field is 1)
				1'b0: the pre-defined LLC-SNAP pattern is matched
				1'b1: the pre-defined LLC-SNAP pattern is un-matched
	UDF_VLT(UDF_VLT): Undefined VLAN tagged Type
			1'b0: VLAN is followed by pre-defined LLC-SNAP
			1'b1: VLAN is followed by un-defined LLC-SNAP
	frag(FRAG): Fragmented frame
	null_frm(NULL): the frame is a NULL frame
	data_frm(DATA): Data frame
	amsdu_sub_frm(A-MPDU Subframe (ASF)):
			0:  This is not an A-MPDU subframe
			1: This is an A-MPDU subframe
			If A-MPDU de-aggregation function was disabled, this field always is 0
	ampdu(AMP): AMPDU
			0: This is an MPDU frame
			1: This is an A-MPDU frame

DWORD 3 ==>
	rx_vector_seq(RX Vector Sequence No):
			The sequence NO. of the corresponding RX vector
			0: RX vector is invalid
			1~255: RX vector sequence number
	tsf_compare_loss(TSF Compare Loss (TCL)):
			In Ad-Hoc mode, indicates that the local TSF timer is less than the timestamp of Beacon or Probe Response.
			The compared TSF timer is selected by CR.
	pattern_drop_bit(DP): Pattern Filter Drop bit
			0: a wanted packet
			1: a drop packet
	cls(CLS): indicate the packet is a coalescing packet
			0: a normal frame
			1: a coalescing frame
	OFLD(OFLD): FW offload packet filter
			2'h0: not match
			2'h1: matched, the RX packet is an EAPOL packet
			2'h2: matched, the RX packet is an ARP or NS packet
			2'h3: matched, the RX packet is an TDLS packet
	magic_pkt(MGC): Wakeup magic packet
			0: not match
			1: matched, the RX packet is a wakeup magic packet
	wol(WOL): Wake-on-WLAN filter matching number
			{4'h0, 1'h0}: Not matched
			{4'h0, 1'h1}: match bitmap 0
			{4'h1, 1'h1}: match bitmap 1
			...
			{4'hF, 1'h1}: match bitmap 15
			Others: Reserved
	cls_bitmap(CLS_BITMAP): coalescing filter matching flag
			Bit[0]: indicate rule 0 matched
			Bit[1]: indicate rule 1 matched
			...
			Bit[9]: indicate rule 9 matched
	pf_mode(PF_MODE): The pattern filter mode
			0: White list
			1: Black list
	pf_sts(PF_STS): This is status report of packet filter
			00: filtering result is OK
				match vec = result (NO-fragment & NO unknown IPv6)
			01: fragment packet is detected
				match vec = result, ONLY when 1st  fragment is matched
							(the remaining fragments will be pasted with the same matched vector)
			10: non-fragment, but unknown IPv6 extenstion header is detected
				match vec = partial matched result, ONLY when header before unknown IPv6 ext.
							header are matched
			11: no filter enable
				match vec = invalid (all match result = non-match), ONLY when PF_EN = 0
*/
#endif /* RELEASE_EXCLUDE */

#define RMAC_RXD_0_PKT_TYPE_MASK		0xe0000000
#define RMAC_RX_PKT_TYPE_RX_TXS			0x00
#define RMAC_RX_PKT_TYPE_RX_TXRXV		0x01
#define RMAC_RX_PKT_TYPE_RX_NORMAL		0x02
#define RMAC_RX_PKT_TYPE_RX_DUP_RFB		0x03
#define RMAC_RX_PKT_TYPE_RX_TMR			0x04
#define RMAC_RX_PKT_TYPE_RETRIEVE		0x05
#define RMAC_RX_PKT_TYPE_RX_EVENT		0x07
#define RMAC_RX_PKT_TYPE(_x)			(((_x) & RMAC_RXD_0_PKT_TYPE_MASK) >> 29)
#define RMAC_RXD_0_PKT_RX_BYTE_COUNT_MASK 0x0000ffff
#define RMAC_RX_PKT_RX_BYTE_COUNT(_x)	(((_x) & RMAC_RXD_0_PKT_RX_BYTE_COUNT_MASK))

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED rmac_rxd_0_txs {
	UINT32 pkt_type:3;
	UINT32 rsv:8;
	UINT32 txs_cnt:5;
	UINT32 rx_byte_cnt:16;
} RMAC_RXD_0_TXS;
#else
typedef struct GNU_PACKED rmac_rxd_0_txs {
	UINT32 rx_byte_cnt:16;
	UINT32 txs_cnt:5;
	UINT32 rsv:8;
	UINT32 pkt_type:3;
} RMAC_RXD_0_TXS;
#endif

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED rmac_rxd_0_txrxv {
	UINT32 pkt_type:3;
	UINT32 rsv:8;
	UINT32 rxv_cnt:5;
	UINT32 rx_byte_cnt:16;
} RMAC_RXD_0_TXRXV;
#else
typedef struct GNU_PACKED rmac_rxd_0_txrxv {
	UINT32 rx_byte_cnt:16;
	UINT32 rxv_cnt:5;
	UINT32 rsv:8;
	UINT32 pkt_type:3;
} RMAC_RXD_0_TXRXV;
#endif


typedef struct _RXV_INFO {
	INT32 Rssi0;
	INT32 Rssi1;
} RXV_INFO;

typedef struct GNU_PACKED _RXV_DWORD0 {
	UINT32 TA_0_31;
} RXV_DWORD0;

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED _RXV_DWORD1 {
	UINT32 Reserved:7;
	UINT32 TR:1;
	UINT32 RxvSn:8;
	UINT32 TA_32_47:16;
} RXV_DWORD1;
#else
typedef struct GNU_PACKED _RXV_DWORD1 {
	UINT32 TA_32_47:16;
	UINT32 RxvSn:8;
	UINT32 TR:1;
	UINT32 Reserved:7;
} RXV_DWORD1;
#endif

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED _RX_VECTOR1_1ST_CYCLE {
	UINT32 VHTA1_B5_B4:2;
	UINT32 VHTA2_B8_B1:8;
	UINT32 HtNoSound:1;
	UINT32 HtSmooth:1;
	UINT32 HtShortGi:1;
	UINT32 HtAggregation:1;
	UINT32 VHTA1_B22:1;
	UINT32 FrMode:2;
	UINT32 TxMode:3;
	UINT32 HtExtltf:2;
	UINT32 HtAdCode:1;
	UINT32 HtStbc:2;
	UINT32 TxRate:7;
} RX_VECTOR1_1ST_CYCLE;
#else
typedef struct GNU_PACKED _RX_VECTOR1_1ST_CYCLE {
	UINT32 TxRate:7;
	UINT32 HtStbc:2;
	UINT32 HtAdCode:1;
	UINT32 HtExtltf:2;
	UINT32 TxMode:3;
	UINT32 FrMode:2;
	UINT32 VHTA1_B22:1;
	UINT32 HtAggregation:1;
	UINT32 HtShortGi:1;
	UINT32 HtSmooth:1;
	UINT32 HtNoSound:1;
	UINT32 VHTA2_B8_B1:8;
	UINT32 VHTA1_B5_B4:2;
} RX_VECTOR1_1ST_CYCLE;
#endif

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED _RX_VECTOR1_2ND_CYCLE {
	UINT32 VHTA1_B16_B6:11;
	UINT32 Length:21;
} RX_VECTOR1_2ND_CYCLE;
#else
typedef struct GNU_PACKED _RX_VECTOR1_2ND_CYCLE {
	UINT32 Length:21;
	UINT32 VHTA1_B16_B6:11;
} RX_VECTOR1_2ND_CYCLE;
#endif

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED _RX_VECTOR1_3TH_CYCLE {
	UINT32 Fagc1CalGain:3;
	UINT32 Fgac1EqCal:1;
	UINT32 Rcpi1:8;
	UINT32 Fagc0CalGain:3;
	UINT32 Fagc0EqCal:1;
	UINT32 Rcpi0:8;
	UINT32 SelAnt:1;
	UINT32 ACI_DETx:1;
	UINT32 OFDMFreqTransDet:1;
	UINT32 VHTA1_B21_B17:5;
} RX_VECTOR1_3TH_CYCLE;
#else
typedef struct GNU_PACKED _RX_VECTOR1_3TH_CYCLE {
	UINT32 VHTA1_B21_B17:5;
	UINT32 OFDMFreqTransDet:1;
	UINT32 ACI_DETx:1;
	UINT32 SelAnt:1;
	UINT32 Rcpi0:8;
	UINT32 Fagc0EqCal:1;
	UINT32 Fgac0CalGain:3;
	UINT32 Rcpi1:8;
	UINT32 Fagc1EqCal:1;
	UINT32 Fgac1CalGain:3;
} RX_VECTOR1_3TH_CYCLE;
#endif

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED _RX_VECTOR1_4TH_CYCLE {
	UINT32 FgacCalGain:3;
	UINT32 Fagc2EqCal:1;
	UINT32 IBRssi1:8;
	UINT32 FagcLpfGainx:4;
	UINT32 WBRssix:8;
	UINT32 IBRssi0:8;
} RX_VECTOR1_4TH_CYCLE;
#else
typedef struct GNU_PACKED _RX_VECTOR1_4TH_CYCLE {
	UINT32 IBRssi0:8;
	UINT32 WBRssix:8;
	UINT32 FagcLpfGainx:4;
	UINT32 IBRssi1:8;
	UINT32 Fagc2EqCal:1;
	UINT32 FgacCalGain:3;
} RX_VECTOR1_4TH_CYCLE;
#endif

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED _RX_VECTOR1_5TH_CYCLE {
	UINT32 LTF_SNR0:6;
	UINT32 LTF_ProcTime:7;
	UINT32 FoE:12; //FreqOffSer from Rx
	UINT32 CagcState:3;
	UINT32 FagcLnaGain1:2;
	UINT32 FagcLnaGain0:2;
} RX_VECTOR1_5TH_CYCLE;
#else
typedef struct GNU_PACKED _RX_VECTOR1_5TH_CYCLE {
	UINT32 FagcLnaGain0:2;
    UINT32 FagcLnaGain1:2;
	UINT32 CagcState:3;
    UINT32 FoE:12; //FreqOffSer from Rx
    UINT32 LTF_ProcTime:7;
    UINT32 LTF_SNR0:6;
} RX_VECTOR1_5TH_CYCLE;
#endif

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED _RX_VECTOR1_6TH_CYCLE {
	UINT32 Reserved:1;
	UINT32 CagcState:3;
	UINT32 NsTsField:3;
	UINT32 RxValidIndicator:1;
	UINT32 Nf2:8;
	UINT32 Nf1:8;
	UINT32 Nf0:8;
} RX_VECTOR1_6TH_CYCLE;
#else
typedef struct GNU_PACKED _RX_VECTOR1_6TH_CYCLE {
	UINT32 Nf0:8;
	UINT32 Nf1:8;
	UINT32 Nf2:8;
	UINT32 RxValidIndicator:1;
	UINT32 NsTsField:3;
	UINT32 CagcState:3;
	UINT32 Reserved:1;
} RX_VECTOR1_6TH_CYCLE;
#endif

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED _RX_VECTOR2_1ST_CYCLE {
	UINT32 Ofdm:28;
	UINT32 Sec40ItfrEnv:1;
	UINT32 SecItfrEnv:1;
	UINT32 PrimItfrEnv:1;
} RX_VECTOR2_1ST_CYCLE;
#else
typedef struct GNU_PACKED _RX_VECTOR2_1ST_CYCLE {
	UINT32 PrimItfrEnv:1;
	UINT32 SecItfrEnv:1;
	UINT32 Sec40ItfrEnv:1;
	UINT32 BtEnv:1;
	UINT32 Ofdm:28;
} RX_VECTOR2_1ST_CYCLE;
#endif

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED _RX_VECTOR2_2ND_CYCLE {
	UINT32 RxScramblingSeed:3;
	//UINT32 DumpSelect:8;
	UINT32 Reserved2:2;
    UINT32 OfdmLtfSNR1:6;
	UINT32 BtdNoTchLoc:7;
	UINT32 Ofdm:14;
} RX_VECTOR2_2ND_CYCLE;
#else
typedef struct GNU_PACKED _RX_VECTOR2_2ND_CYCLE {
	UINT32 Ofdm:14;
	UINT32 BtdNoTchLoc:7;
	//UINT32 DumpSelect:8;
	UINT32 OfdmLtfSNR1:6;
    UINT32 Reserved2:2;
	UINT32 RxScramblingSeed:3;
} RX_VECTOR2_2ND_CYCLE;
#endif

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED _RX_VECTOR2_3TH_CYCLE {
	UINT32 FcsErr:1;
	UINT32 OfdmDewModeDet:1;
	UINT32 OfdmCeLtfComb:1;
	UINT32 OfdmCeGicEnb:1;
	UINT32 OfdmCeRmsdId:3;
	UINT32 Reserved1:1;
	UINT32 BgAgcWbRssix:8;
	UINT32 BfAgcIbRssix:8;
	UINT32 BfAgcLpfGain:4;
	UINT32 Reserved0:1;
	UINT32 BfAgcLnaGainx:2;
	UINT32 HtStfDet:1;
} RX_VECTOR2_3TH_CYCLE;
#else
typedef struct GNU_PACKED _RX_VECTOR2_3TH_CYCLE {
	UINT32 HtStfDet:1;
	UINT32 BfAgcLnaGainx:2;
	UINT32 Reserved0:1;
	UINT32 BfAgcLpfGain:4;
	UINT32 BfAgcIbRssix:8;
	UINT32 BgAgcWbRssix:8;
	UINT32 Reserved1:1;
	UINT32 OfdmCeRmsdId:3;
	UINT32 OfdmCeGicEnb:1;
	UINT32 OfdmCeLtfComb:1;
	UINT32 OfdmDewModeDet:1;
	UINT32 FcsErr:1;
} RX_VECTOR2_3TH_CYCLE;
#endif

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED rmac_rxd_0_normal {
	UINT32 pkt_type:3;
	UINT32 grp_vld:4;
	UINT32 ut_sum:1;
	UINT32 ip_sum:1;
	UINT32 eth_type_offset:7;
	UINT32 rx_byte_cnt:16;
} RMAC_RXD_0_NORMAL;
#else
typedef struct GNU_PACKED rmac_rxd_0_normal {
	UINT32 rx_byte_cnt:16;
	UINT32 eth_type_offset:7;
	UINT32 ip_sum:1;
	UINT32 ut_sum:1;
	UINT32 grp_vld:4;
	UINT32 pkt_type:3;
} RMAC_RXD_0_NORMAL;
#endif

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED rmac_rxd_1_normal {
	UINT32 bssid:6;
	UINT32 payload_format:2;
	UINT32 hdr_trans:1;
	UINT32 hdr_offset:1;
	UINT32 mac_hdr_len:6;
	UINT32 ch_freq:8;
	UINT32 key_id:2;
	UINT32 beacon_uc:1;
	UINT32 beacon_mc:1;
	UINT32 bcast:1;
	UINT32 mcast:1;
	UINT32 u2m:1;
	UINT32 htc_vld:1;
} RMAC_RXD_1_NORMAL;
#else
typedef struct GNU_PACKED rmac_rxd_1_normal {
	UINT32 htc_vld:1;
	UINT32 u2m:1;
	UINT32 mcast:1;
	UINT32 bcast:1;
	UINT32 beacon_mc:1;
	UINT32 beacon_uc:1;
	UINT32 key_id:2;
	UINT32 ch_freq:8;
	UINT32 mac_hdr_len:6;
	UINT32 hdr_offset:1;
	UINT32 hdr_trans:1;
	UINT32 payload_format:2;
	UINT32 bssid:6;
} RMAC_RXD_1_NORMAL;
#endif

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED rmac_rxd_2_normal {
	UINT32 non_ampdu:1;
	UINT32 non_ampdu_sub_frm:1;
	UINT32 ndata:1;
	UINT32 null_frm:1;
	UINT32 frag:1;
	UINT32 UDF_VLT:1;
	UINT32 llc_mis:1;
	UINT32 exceed_max_rx_len:1;
	UINT32 de_amsdu_err:1;
	UINT32 len_mismatch:1;
	UINT32 tkip_mic_err:1;
	UINT32 icv_err:1;
	UINT32 clm:1;
	UINT32 cm:1;
	UINT32 fcs_err:1;
	UINT32 sw_bit:1;
	UINT32 sec_mode:4;
	UINT32 tid:4;
	UINT32 wlan_idx:8;
} RMAC_RXD_2_NORMAL;
#else
typedef struct GNU_PACKED rmac_rxd_2_normal {
	UINT32 wlan_idx:8;
	UINT32 tid:4;
	UINT32 sec_mode:4;
	UINT32 sw_bit:1;
	UINT32 fcs_err:1;
	UINT32 cm:1;
	UINT32 clm:1;
	UINT32 icv_err:1;
	UINT32 tkip_mic_err:1;
	UINT32 len_mismatch:1;
	UINT32 de_amsdu_err:1;
	UINT32 exceed_max_rx_len:1;
	UINT32 llc_mis:1;
	UINT32 UDF_VLT:1;
	UINT32 frag:1;
	UINT32 null_frm:1;
	UINT32 ndata:1;
	UINT32 non_ampdu_sub_frm:1;
	UINT32 non_ampdu:1;
} RMAC_RXD_2_NORMAL;
#endif

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED rmac_rxd_3_normal {
	UINT32 pf_sts:2;
	UINT32 pf_mode:1;
	UINT32 cls_bitmap:10;
	UINT32 wol:5;
	UINT32 magic_pkt:1;
	UINT32 OFLD:2;
	UINT32 cls:1;
	UINT32 pattern_drop_bit:1;
	UINT32 tsf_compare_loss:1;
	UINT32 rx_vector_seq:8;
} RMAC_RXD_3_NORMAL;
#else
typedef struct GNU_PACKED rmac_rxd_3_normal {
	UINT32 rx_vector_seq:8;
	UINT32 tsf_compare_loss:1;
	UINT32 pattern_drop_bit:1;
	UINT32 cls:1;
	UINT32 OFLD:2;
	UINT32 magic_pkt:1;
	UINT32 wol:5;
	UINT32 cls_bitmap:10;
	UINT32 pf_mode:1;
	UINT32 pf_sts:2;
} RMAC_RXD_3_NORMAL;
#endif

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED rmac_rxd_0_tmr {
	UINT32 pkt_type:3;
	UINT32 ir:1;
	UINT32 tod_vld:1;
	UINT32 toa_vld:1;
	UINT32 type:2;
	UINT32 sub_type:4;
	UINT32 tmf:1;
	UINT32 nc:1;
	UINT32 rsv_16:2;
	UINT32 rx_byte_cnt:16;
} RMAC_RXD_0_TMR;
#else
typedef struct GNU_PACKED rmac_rxd_0_tmr {
	UINT32 rx_byte_cnt:16;
	UINT32 rsv_16:2;
	UINT32 nc:1;
	UINT32 tmf:1;
	UINT32 sub_type:4;
	UINT32 type:2;
	UINT32 toa_vld:1;
	UINT32 tod_vld:1;
	UINT32 ir:1;
	UINT32 pkt_type:3;
} RMAC_RXD_0_TMR;
#endif

union GNU_PACKED rmac_rxd_0 {
	struct rmac_rxd_0_txs txs_d0;
	struct rmac_rxd_0_normal rxd_d0;
	struct rmac_rxd_0_txrxv rxv_d0;
	struct rmac_rxd_0_tmr tmr_d0;
	UINT32 word;
};


/*
	Rx Normal Data frame Format
*/
typedef struct GNU_PACKED rxd_base_struc{
	/* DWORD 0 */
	struct rmac_rxd_0_normal rxd_0;
	/* DWORD 1 */
	struct rmac_rxd_1_normal rxd_1;
	/* DWORD 2 */
	struct rmac_rxd_2_normal rxd_2;
	/* DWORD 3 */
	struct rmac_rxd_3_normal rxd_3;
}RXD_BASE_STRUCT;

#define RXS_GROUP1 (1 << 0)
#define RXS_GROUP2 (1 << 1)
#define RXS_GROUP3 (1 << 2)
#define RXS_GROUP4 (1 << 3)

#define RMAC_INFO_BASE_SIZE 	16
#define RMAC_INFO_GRP_1_SIZE    16
#define RMAC_INFO_GRP_2_SIZE    8
#define RMAC_INFO_GRP_3_SIZE    24
#define RMAC_INFO_GRP_4_SIZE    16

#ifdef RELEASE_EXCLUDE
/*
	Present when RXD_BASE_STRUCT.hdr_trans == 1

DWORD 4 ==>
	frm_ctrl(Frame Control Field):
	ta_low(TA[15:0]):

DWORD 5 ==>
	ta_high(TA[47:16]):

DWORD 6 ==>
	frag_num(Fragment Number):
	seq_num(Sequence Number):
	qos_ctrl(QoS Control Field):

DWORD 7 ==>
	htc_ctrl(HT Control Field):
*/
#endif /* RELEASE_EXCLUDE */

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED _RXD_GRP4_STRUCT{
	/* DWORD 4 */
	UINT32 frm_ctrl:16;
	UINT32 ta_low:16;

	/* DWORD 5 */
	UINT32 ta_high;

	/* DWORD 6 */
	UINT32 frag_num:4;
	UINT32 seq_num:12;
	UINT32 qos_ctrl:16;

	/* DWORD 7 */
	UINT32 htc_ctrl;
} RXD_GRP4_STRUCT;
#else
typedef struct GNU_PACKED _RXD_GRP4_STRUCT{
	/* DWORD 4 */
	UINT32 ta_low:16;
	UINT32 frm_ctrl:16;

	/* DWORD 5 */
	UINT32 ta_high;

	/* DWORD 6 */
	UINT32 qos_ctrl:16;
	UINT32 seq_num:12;
	UINT32 frag_num:4;

	/* DWORD 7 */
	UINT32 htc_ctrl;
} RXD_GRP4_STRUCT;
#endif

#ifdef RELEASE_EXCLUDE
/*
	Present when CR setting HIF_CLIENT.RXINF.RXGV[2:0]

DWORD 8 ==>
	sec_pn_32: TKIP_RSC[31:0] / CCMP_PN[31:0] / GCMP_PN[31:0] / WPI_PN[31:0]

DWORD 9 ==>
	sec_pn_48: TKIP_RSC[47:32] / CCMP_PN[47:32] / GCMP_PN[47:32] / WPI_PN[47:32]
	wpi_pn_64: WPI_PN[63:48]

DWORD 10 ==>
	wpi_pn_96: WPI_PN[95:64]

DWORD 11 ==>
	wpi_pn_128: WPI_PN[127:96]
*/
#endif /* RELEASE_EXCLUDE */

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED _RXD_GRP1_STRUCT{
	/* DWORD 8 */
	UINT32 sec_pn_32;

	/* DWORD 9 */
	UINT32 sec_pn_48:16;
	UINT32 wpi_pn_64:16;

	/* DWORD 10 */
	UINT32 wpi_pn_96;

	/* DWORD 11 */
	UINT32 wpi_pn_128;
} RXD_GRP1_STRUCT;
#else
typedef struct GNU_PACKED _RXD_GRP1_STRUCT{
	/* DWORD 8 */
	UINT32 sec_pn_32;

	/* DWORD 9 */
	UINT32 wpi_pn_64:16;
	UINT32 sec_pn_48:16;

	/* DWORD 10 */
	UINT32 wpi_pn_96;

	/* DWORD 11 */
	UINT32 wpi_pn_128;
} RXD_GRP1_STRUCT;
#endif

#ifdef RELEASE_EXCLUDE
/*
	Present when CR setting HIF_CLIENT.RXINF.RXGV[2:0]

DWORD 12 ==>
	timestamp(Timestamp):
			Frame reception timestamp (low 32-bits) that indicates the value of
			the local TSF timer value at the time the first bit of the MAC header
			in the received frame (PPDU unit) arriving at the MAC.

			For A-MPDU within in the same PPDU, the Timestamp will be the
			same for each de-aggregated MPDU

			If RX packet matches Own BSSID, the local TSF is the BSSID related TSF timer.
			If RX packet un-matches Own BSSID, the local TSF is assigned by CR

DWORD 13 ==>
	crc(CRC): CRC32 value of this MPDU
*/
#endif /* RELEASE_EXCLUDE */

typedef struct GNU_PACKED _RXD_GRP2_STRUCT{
	/* DWORD 12 */
	UINT32 timestamp;

	/* DWORD 13 */
	UINT32 crc;
} RXD_GRP2_STRUCT;

#ifdef RELEASE_EXCLUDE
/*
	Present when CR setting HIF_CLIENT.RXINF.RXGV[2:0]

DWORD 14 ==>
	rxv_1: RX Vector Group 1 1st cycle, The value should refer to "MT6620 WiFi BB MAC interface" document.
DWORD 15 ==>
	rxv_2: RX Vector Group 1 2nd cycle
DWORD 16 ==>
	rxv_3: RX Vector Group 1 3rd cycle
DWORD 17 ==>
	rxv_4: RX Vector Group 1 4th cycle
DWORD 18 ==>
	rxv_5: RX Vector Group 1 5th cycle
DWORD 19 ==>
	rxv_6: RX Vector Group 1 6th cycle
*/
#endif /* RELEASE_EXCLUDE */
typedef struct GNU_PACKED _RXD_GRP3_STRUCT{
	/* DWORD 14 */
	UINT32 rxv_1;

	/* DWORD 15 */
	UINT32 rxv_2;

	/* DWORD 16 */
	UINT32 rxv_3;

	/* DWORD 17 */
	UINT32 rxv_4;

	/* DWORD 18 */
	UINT32 rxv_5;

	/* DWORD 18 */
	UINT32 rxv_6;

	/* DWORD 19 */
	UINT32 rxv_7;
}RXD_GRP3_STRUCT;


#ifdef RELEASE_EXCLUDE
/*
	cs_status(Checksum Status (CS_Status)):
		Indicates the checking result of packet checksum.
			Bit3: This bit is used for UDP checksum result indication and it is
				valid only when HWFCR. RX_UDP_CS_OFLD_EN is asserted.
				0: The UDP checksum result is correct or it doesn't need to check.
						If UDP checksum value is 0, then this field will be 0.
				1: The UDP checksum result is incorrect.
			Bit2: This bit is used for TCP checksum result indication and it is
				valid only when HWFCR. RX_TCP_CS_OFLD_EN is asserted.
				0: The TCP checksum is correct or it doesn't need to check.
					If TCP checksum value is 0, then this field will be 0.
				1: The TCP checksum is incorrect.
			Bit1: Reserved.
			Bit0: This bit is used for IP checksum result indication and it is
				valid only when HWFCR. RX_IPV4_CS_OFLD_EN is asserted.
				0: The IP checksum is correct.
				1: The IP checksum is incorrect.

	cs_type(Checksum Type (CS Type)): Indicates the packet type.
			Bit7: this bit indicates this data structure is an UDP packet format
				=>valid only when HWFCR. RX_UDP_CS_OFLD_EN is asserted.
			Bit6: this bit indicates this data structure is a TCP packet format
				=>valid only when HWFCR. RX_TCP_CS_OFLD_EN is asserted.
			Bit5: this bit indicates this data structure is an IPv6 packet format
				=>valid only when HWFCR. RX_IPV6_CS_OFLD_EN is asserted.
			Bit4: this bit indicates this data structure is an IPv4 packet format
				=>valid only when HWFCR. RX_IPV4_CS_OFLD_EN is asserted.

	ip_len_mismatch(IP Datagram Length Mismatch (C)):
			indicates that the received IP length does not match with the received
			frame length. Refer chapter 8.4 "Rule for checksum offload in TX/RX"
			for details.

			=> This field only valid when at least one bit of HWFCR.[7:5] is asserted

	ip_frag(IP Fragmentation Packet (F)):
			it indicates that the received frame is an IP fragmented packet.

			=> This field is only valid when at least one bit of HWFCR.[7:5] is asserted

	un_next_hdr(Unknown Next Header (UN)):
			If the "next header" field of IPV6 header is not equal to
			TCP(NextHeader=6), UDP (NextHeader=17), or NO_NEXT_HEADER (NextHeader=59),
			this bit will be set to 1.

			=> This field is only valid when HWFCR. RX_IPV6_CS_OFLD_EN is asserted.

	rsv_11: Reserved bits
*/
#endif /* RELEASE_EXCLUDE */

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED _RX_CSO_STRUCT {
	UINT32 cs_status:4;
	UINT32 cs_type:4;
	UINT32 ip_len_mismatch:1;
	UINT32 ip_frag:1;
	UINT32 un_next_hdr:1;
	UINT32 rsv_11:21;
} RX_CSO_STRUCT;
#else
typedef struct GNU_PACKED _RX_CSO_STRUCT {
	UINT32 rsv_11:21;
	UINT32 un_next_hdr:1;
	UINT32 ip_frag:1;
	UINT32 ip_len_mismatch:1;
	UINT32 cs_type:4;
	UINT32 cs_status:4;
} RX_CSO_STRUCT;
#endif

/* TX Status Report Format */
#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED txs_d_0 {
	UINT32 ant_id:6;
	UINT32 tid:3;
	UINT32 baf:1;
	UINT32 ps:1;
	UINT32 txop:1;
	UINT32 BE:1;
	UINT32 LE:1;
	UINT32 RE:1;
	UINT32 ME:1;
	UINT32 txs2h:1;
	UINT32 txs2m:1;
	UINT32 txsfm:1;
	UINT32 fr:1;
	UINT32 tx_rate:12;
} TXS_D_0;
#else
typedef struct GNU_PACKED txs_d_0 {
	UINT32 tx_rate:12;
	UINT32 fr:1;
	UINT32 txsfm:1;
	UINT32 txs2m:1;
	UINT32 txs2h:1;
	UINT32 ME:1;
	UINT32 RE:1;
	UINT32 LE:1;
	UINT32 BE:1;
	UINT32 txop:1;
	UINT32 ps:1;
	UINT32 baf:1;
	UINT32 tid:3;
	UINT32 ant_id:6;
} TXS_D_0;
#endif

#ifdef RT_BIG_ENDIAN
typedef union GNU_PACKED txs_d_1 {
	struct {
		UINT32 rsv:8;
		UINT32 noise_2:8;
		UINT32 noise_1:8;
		UINT32 noise_0:8;
	} field_noise;

	UINT32 timestamp;

	UINT32 word;
} TXS_D_1;
#else
typedef union GNU_PACKED txs_d_1 {
	struct {
		UINT32 noise_0:8;
		UINT32 noise_1:8;
		UINT32 noise_2:8;
		UINT32 rsv:8;
	} field_noise;

	UINT32 timestamp;

	UINT32 word;
} TXS_D_1;
#endif

#ifdef RT_BIG_ENDIAN
typedef union GNU_PACKED txs_d_2 {
	struct {
		UINT32 tx_pwr_dBm:7;
		UINT32 front_time:25;
	} field_ft;

	struct {
		UINT32 tx_pwr_dBm:7;
		UINT32 rsv:1;
		UINT32 rcpi_2:8;
		UINT32 rcpi_1:8;
		UINT32 rcpi_0:8;
	} field_rcpi;

	UINT32 word;
} TXS_D_2;
#else
typedef union GNU_PACKED txs_d_2 {
	struct {
		UINT32 front_time:25;
		UINT32 tx_pwr_dBm:7;
	} field_ft;

	struct {
		UINT32 rcpi_0:8;
		UINT32 rcpi_1:8;
		UINT32 rcpi_2:8;
		UINT32 rsv:1;
		UINT32 tx_pwr_dBm:7;
	} field_rcpi;

	UINT32 word;
} TXS_D_2;
#endif

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED txs_d_3 {
	UINT32 wlan_idx:8;
	UINT32 rxv_sn:8;
	UINT32 transmission_delay:16;
} TXS_D_3;
#else
typedef struct GNU_PACKED txs_d_3 {
	UINT32 transmission_delay:16;
	UINT32 rxv_sn:8;
	UINT32 wlan_idx:8;
} TXS_D_3;
#endif

#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED txs_d_4 {
	UINT32 last_tx_rate_idx:3;
	UINT32 mpdu_tx_cnt:5;
	UINT32 am:1;
	UINT32 fm:1;
	UINT32 pid:8;
	UINT32 tbw:2;
	UINT32 sn:12;
} TXS_D_4;
#else
typedef struct GNU_PACKED txs_d_4 {
	UINT32 sn:12;
	UINT32 tbw:2;
	UINT32 pid:8;
	UINT32 fm:1;
	UINT32 am:1;
	UINT32 mpdu_tx_cnt:5;
	UINT32 last_tx_rate_idx:3;
} TXS_D_4;
#endif

typedef struct GNU_PACKED _TXS_STRUC{
	TXS_D_0 txs_d0;
	TXS_D_1 txs_d1;
	TXS_D_2 txs_d2;
	TXS_D_3 txs_d3;
	TXS_D_4 txs_d4;
} TXS_STRUC;


typedef struct GNU_PACKED _TXS_FRM_STRUC{
	struct rmac_rxd_0_txs txs_d0;
	TXS_STRUC txs_info[0];
} TXS_FRM_STRUC;


/* RX/TX-Status Vector Format */
#ifdef RT_BIG_ENDIAN
typedef struct GNU_PACKED _RXV_STRUC{
	UINT32 ta_0;
	UINT32 rsv_1_25:7;
	UINT32 tr:1;
	UINT32 rxv_sn:8;
	UINT32 ta_32:16;
	UINT32 vector1[6];
	UINT32 vector2[3];
} RXV_STRUC;
#else
typedef struct GNU_PACKED _RXV_STRUC{
	UINT32 ta_0;
	UINT32 ta_32:16;
	UINT32 rxv_sn:8;
	UINT32 tr:1;
	UINT32 rsv_1_25:7;
	UINT32 vector1[6];
	UINT32 vector2[3];
} RXV_STRUC;
#endif

typedef struct GNU_PACKED _RXV_FRM_STRUC{
	struct rmac_rxd_0_txrxv rxv_d0;
	RXV_STRUC rxv_info[0];
} RXV_FRM_STRUC;


/*
	Timing Measurement Report Format
*/
#ifdef RT_BIG_ENDIAN
typedef union GNU_PACKED tmr_d_1 {
	struct {
		UINT32 rsv_29:3;
		UINT32 rxv_fr_mode:2;
		UINT32 rxv_tx_mode:3;
		UINT32 rsv_21:3;
		UINT32 txv_fr_mode:2;
		UINT32 txv_tx_mode:3;
		UINT32 rsv_8:8;
		UINT32 pid:8;
	} field_init;

	struct {
		UINT32 rsv_29:3;
		UINT32 rxv_fr_mode:2;
		UINT32 rxv_tx_mode:3;
		UINT32 rsv_21:3;
		UINT32 txv_fr_mode:2;
		UINT32 txv_tx_mode:3;
		UINT32 rsv_8:8;
		UINT32 rxv_sn:8;
	} field_resp;

	UINT32 word;
} TMR_D_1;
#else
typedef union GNU_PACKED tmr_d_1 {
	struct {
		UINT32 pid:8;
		UINT32 rsv_8:8;
		UINT32 txv_tx_mode:3;
		UINT32 txv_fr_mode:2;
		UINT32 rsv_21:3;
		UINT32 rxv_tx_mode:3;
		UINT32 rxv_fr_mode:2;
		UINT32 rsv_29:3;
	} field_init;

	struct {
		UINT32 rxv_sn:8;
		UINT32 rsv_8:8;
		UINT32 txv_tx_mode:3;
		UINT32 txv_fr_mode:2;
		UINT32 rsv_21:3;
		UINT32 rxv_tx_mode:3;
		UINT32 rxv_fr_mode:2;
		UINT32 rsv_29:3;
	} field_resp;

	UINT32 word;
} TMR_D_1;
#endif

#ifdef RT_BIG_ENDIAN
typedef union GNU_PACKED tmr_d_2 {
	struct {
		UINT32 sn:16;
		UINT32 ta_0:16;
	} field;

	UINT32 word;
} TMR_D_2;
#else
typedef union GNU_PACKED tmr_d_2 {
	struct {
		UINT32 ta_0:16;
		UINT32 sn:16;
	} field;

	UINT32 word;
} TMR_D_2;
#endif

#ifdef RT_BIG_ENDIAN
typedef union GNU_PACKED tmr_d_6 {
	struct {
		UINT32 toa_32:16;
		UINT32 tod_32:16;
	} field;

	UINT32 word;
} TMR_D_6;
#else
typedef union GNU_PACKED tmr_d_6 {
	struct {
		UINT32 tod_32:16;
		UINT32 toa_32:16;
	} field;

	UINT32 word;
} TMR_D_6;
#endif

typedef struct GNU_PACKED _TMR_FRM_STRUC{
	struct rmac_rxd_0_tmr tmr_d0;
	TMR_D_1 tmr_d1;
	TMR_D_2 tmr_d2;
	UINT32 ta_16;
	UINT32 tod_0;
	UINT32 toa_0;
	TMR_D_6 tmr_d6;
}TMR_FRM_STRUC;


typedef struct wtbl_entry {
	UINT8 wtbl_idx;

	struct wtbl_1_struc wtbl_1;
	struct wtbl_2_struc wtbl_2;
	union wtbl_3_struc wtbl_3;
	struct wtbl_4_struc wtbl_4;

	UINT32 wtbl_addr[4];
	UINT16 wtbl_fid[4];
	UINT16 wtbl_eid[4];
}WTBL_ENTRY;



#define MT_PSE_WTBL_2_ADDR	0xa5000000  /* get from CR setting of PSE.BUFS_DAA (0x164) */
#define MT_PSE_BASE_ADDR		0xa0000000

#define MT_TOP_REMAP_ADDR		0x80000000 //TOP start address 8002-0000, but only can remap to 8000-0000
#define MT_TOP_REMAP_ADDR_THEMAL	 0xa2000 //Get Thermal sensor adc cal value: 0x80022000 bits(8,14), Offset 0x80000 + 0x22000 = 0xa2000
#define MT_TOP_THEMAL_ADC	0x80022000 //Get Thermal sensor adc cal value: 0x80022000 bits(8,14)

#define MCU_CFG_BASE		0x2000
#define MCU_PCIE_REMAP_1	(MCU_CFG_BASE + 0x500)
#define REMAP_1_OFFSET_MASK (0x3ffff)
#define GET_REMAP_1_OFFSET(p) (((p) & REMAP_1_OFFSET_MASK))
#define REMAP_1_BASE_MASK	(0x3fff << 18)
#define GET_REMAP_1_BASE(p) (((p) & REMAP_1_BASE_MASK) >> 18)
#define MCU_PCIE_REMAP_2	(MCU_CFG_BASE + 0x504)
#define REMAP_2_OFFSET_MASK (0x7ffff)
#define GET_REMAP_2_OFFSET(p) (((p) & REMAP_2_OFFSET_MASK))
#define REMAP_2_BASE_MASK (0x1fff << 19)
#define GET_REMAP_2_BASE(p) (((p) & REMAP_2_BASE_MASK) >> 19)

#define TOP_CFG_BASE        0x0000

#define XTAL_CTL4           (TOP_CFG_BASE + 0x1210)
#define XTAL_CTL13          (TOP_CFG_BASE + 0x1234)
#define XTAL_CTL14          (TOP_CFG_BASE + 0x1238)
#define DA_XO_C2_MASK (0x7f << 8)
#define DA_XO_C2(p) (((p) & 0x7f) << 8)


#if defined(MT7603_FPGA) || defined(MT7628_FPGA) || defined(MT7636_FPGA)
#define MT_PSE_PAGE_SIZE		256
#else
#define MT_PSE_PAGE_SIZE		128
#endif /* MT7603_FPGA */

#define MT_WTBL_SIZE			128

#ifdef MT7628_FPGA
#undef MT_WTBL_SIZE
#define MT_WTBL_SIZE			20
#endif /* MT7628_FPGA */

#ifdef MT7636_FPGA
#undef MT_WTBL_SIZE
#define MT_WTBL_SIZE			20
#endif /* MT7636_FPGA */

#if defined(MT7603) || defined(MT7628) || defined(MT7636)
#define DMA_SCH_LMAC		0
#define DMA_SCH_BYPASS		1
#define DMA_SCH_HYBRID		2
#endif /* defined(MT7603) || defined(MT7628) || defined(MT7636) */

#define MT_PCI_REMAP_ADDR_1		0x40000
#define MT_PCI_REMAP_ADDR_2		0x80000



// TODO: shiang-7603, this is a dummy data structure and need to revise to adapative for MT7603 series

#define WMM_QUE_NUM		4 /* each sta has 4 Queues to mapping to each WMM AC */

/* value domain of pTxD->HostQId (4-bit: 0~15) */
#define QID_AC_BK               1   /* meet ACI definition in 802.11e */
#define QID_AC_BE               0   /* meet ACI definition in 802.11e */
#define QID_AC_VI               2
#define QID_AC_VO               3
#define QID_HCCA                4
#define NUM_OF_TX_RING		4
#ifdef USE_BMC
#undef NUM_OF_TX_RING
#define NUM_OF_TX_RING      5
#endif /*USE_BMC*/
#define NUM_OF_WMM1_TX_RING	1

#define QID_BMC                 8

#define NUM_OF_RX_RING		1
#ifdef CONFIG_ANDES_SUPPORT
#undef NUM_OF_RX_RING
#define NUM_OF_RX_RING		2
#endif /* CONFIG_ANDES_SUPPORT */

#define QID_MGMT                13
#define QID_RX                  14
#define QID_OTHER               15
#ifdef CONFIG_ANDES_SUPPORT
#define QID_CTRL				16
#endif /* CONFIG_ANDES_SUPPORT */

#define QID_BCN				17

#define SHAREDKEYTABLE			0
#define PAIRWISEKEYTABLE		1

/* Per Packet PID */
enum {
	PID_DATA_NORMALUCAST,
	PID_DATA_NOT_NORM_ACK,
	PID_DATA_AMPDU,
	PID_MGMT,
	PID_DATA_NO_ACK,
	PID_CTL_BAR,
	PID_PS_DATA,
	PID_TDLS,
	PID_UAPSD,
	PID_NULL_FRAME_PWR_ACTIVE,
	PID_NULL_FRAME_PWR_SAVE,
	PID_MAX = 0x40,
};

/* Indicate the txs report to Host or MCU */
typedef enum {
	TXS2MCU,
	TXS2HOST,
} TXS_TARGET_PORT;

#define TXS2MCU_AGGNUMS 31
#define TXS2HOST_AGGNUMS 31

enum {
	TXS2M_QID0,
	TXS2M_QID1,
	TXS2M_QID2,
	TXS2M_QID3,
};

enum {
	TXS2H_QID0,
	TXS2H_QID1,
};

enum {
	TXS_FORMAT0,
	TXS_FORMAT1,
};

enum {
	TXS_UNUSED,
	TXS_USED,
};

typedef struct _TXS_STATUS {
	UINT8 TxSPid;
	UINT8 State;
	UINT8 Type;
	UINT8 PktPid;
	UINT8 PktType;
	UINT8 PktSubType;
	UINT16 TxRate;
	UINT32 Priv;
} TXS_STATUS, *PTXS_STATYS;

#define TOTAL_PID_HASH_NUMS	0x10
#define TOTAL_PID_HASH_NUMS_PER_PKT_TYPE 0x8
#define TXS_WLAN_IDX_ALL 128
#define TXS_STATUS_NUM 256
typedef struct _TXS_CTL {
	/* TXS type hash table per pkt */
	DL_LIST TxSTypePerPkt[TOTAL_PID_HASH_NUMS];
	NDIS_SPIN_LOCK TxSTypePerPktLock[TOTAL_PID_HASH_NUMS];
	/* TXS type hash table per pkt type and subtype */
	DL_LIST TxSTypePerPktType[3][TOTAL_PID_HASH_NUMS_PER_PKT_TYPE];
	NDIS_SPIN_LOCK TxSTypePerPktTypeLock[3][TOTAL_PID_HASH_NUMS_PER_PKT_TYPE];
	ULONG TxS2McUStatusPerPkt;
	ULONG TxS2HostStatusPerPkt;
	ULONG TxS2McUStatusPerPktType[3];
	ULONG TxS2HostStatusPerPktType[3];
	ULONG TxSFormatPerPkt;
	ULONG TxSFormatPerPktType[3];
	ULONG TxSStatusPerWlanIdx[2];
	ULONG TxSFailCount;
	UINT8 TxSPid;
	TXS_STATUS TxSStatus[TXS_STATUS_NUM];
	BOOLEAN TxSValid;
} TXS_CTL, *PTXS_CTL;

#define TXS_TYPE0 0 /* Per Pkt */
#define TXS_TYPE1 1 /* Per Pkt Type */
#define TXS_DUMP_REPEAT 0xffffffff
typedef struct _TXS_TYPE {
	DL_LIST List;
	UINT8 Type;
	UINT8 PktPid;
	UINT8 PktType;
	UINT8 PktSubType;
	UINT8 Format;
	INT32 (*TxSHandler)(struct _RTMP_ADAPTER *pAd, CHAR *Data, UINT32 Priv);
	BOOLEAN DumpTxSReport;
	ULONG DumpTxSReportTimes;
} TXS_TYPE, *PTXS_TYPE;

typedef INT32 (*TXS_HANDLER)(struct _RTMP_ADAPTER *pAd, CHAR *Data, UINT32 Priv);

INT32 InitTxSTypeTable(struct _RTMP_ADAPTER *pAd);
INT32 ExitTxSTypeTable(struct _RTMP_ADAPTER *pAd);
INT32 AddTxSTypePerPkt(struct _RTMP_ADAPTER *pAd, UINT8 Pid, UINT8 Format,
						TXS_HANDLER TxSHandler);
INT32 RemoveTxSTypePerPkt(struct _RTMP_ADAPTER *pAd, UINT32 Pid, UINT8 Format);
INT32 TxSTypeCtlPerPkt(struct _RTMP_ADAPTER *pAd, UINT32 Pid, UINT8 Format, 
						BOOLEAN TxS2Mcu, BOOLEAN TxS2Host, 
						BOOLEAN DumpTxSReport, ULONG DumpTxSReportTimes);
INT32 ParseTxSPacket(struct _RTMP_ADAPTER *pAd, UINT32 Pid, UINT8 Format, CHAR *Data);
INT32 BcnTxSHandler(struct _RTMP_ADAPTER *pAd, CHAR *Data, UINT32 Priv);
INT32 NullFramePM1TxSHandler(struct _RTMP_ADAPTER *pAd, CHAR *Data, UINT32 Priv);
INT32 NullFramePM0TxSHandler(struct _RTMP_ADAPTER *pAd, CHAR *Data, UINT32 Priv);
INT32 RTMPWaitNullFrameTxDone(struct _RTMP_ADAPTER *pAd);

#ifdef CFG_TDLS_SUPPORT
INT32 TdlsTxSHandler(struct _RTMP_ADAPTER *pAd, CHAR *Data, UINT32 Priv);
#endif //CFG_TDLS_SUPPORT
#ifdef UAPSD_SUPPORT
INT32 UAPSDTxSHandler(struct _RTMP_ADAPTER *pAd, CHAR *Data, UINT32 Priv);
#endif
INT32 AddTxSTypePerPktType(struct _RTMP_ADAPTER *pAd, UINT8 Type, UINT8 Subtype,
							UINT8 Format, TXS_HANDLER TxSHandler);
INT32 RemoveTxSTypePerPktType(struct _RTMP_ADAPTER *pAd, UINT8 Type, UINT8 Subtype, 
										UINT8 Format);
INT32 TxSTypeCtlPerPktType(struct _RTMP_ADAPTER *pAd, UINT8 Type, UINT8 Subtype, UINT16 WlanIdx, 
							UINT8 Format, BOOLEAN TxS2Mcu, BOOLEAN TxS2Host, 
							BOOLEAN DumpTxSReport, ULONG DumpTxSReportTimes);
UINT8 AddTxSStatus(struct _RTMP_ADAPTER *pAd, UINT8 Type, UINT8 PktPid, UINT8 PktType,
						UINT8 PktSubType, UINT16 TxRate, UINT32 Priv);
INT32 RemoveTxSStatus(struct _RTMP_ADAPTER *pAd, UINT32 TxSPid, UINT8 *Type, UINT8 *PktPid,
								UINT8 *PktType, UINT8 *PktSubType, UINT16 *TxRate, UINT32 *Priv);

#ifdef CONFIG_TSO_SUPPORT
#define TSO_SIZE		4
#else
#define TSO_SIZE		0
#endif /* CONFIG_TSO_SUPPORT */

#define EXP_ACK_TIME	0x1380

typedef	union GNU_PACKED _TXWI_STRUC {
	UINT32 word;
}TXWI_STRUC;


typedef union GNU_PACKED _RXWI_STRUC {
	UINT32 word;
}RXWI_STRUC;

#ifdef RT_BIG_ENDIAN
typedef	union GNU_PACKED _TX_STA_CNT0_STRUC {
	struct {
	    UINT16  TxBeaconCount;
	    UINT16  TxFailCount;
	} field;
	UINT32 word;
} TX_STA_CNT0_STRUC;
#else
typedef	union GNU_PACKED _TX_STA_CNT0_STRUC {
	struct {
	    UINT16  TxFailCount;
	    UINT16  TxBeaconCount;
	} field;
	UINT32 word;
} TX_STA_CNT0_STRUC;
#endif

#ifdef RT_BIG_ENDIAN
typedef	union GNU_PACKED _TX_STA_CNT1_STRUC {
	struct {
	    UINT16  TxRetransmit;
	    UINT16  TxSuccess;
	} field;
	UINT32 word;
} TX_STA_CNT1_STRUC;
#else
typedef	union GNU_PACKED _TX_STA_CNT1_STRUC {
	struct {
	    UINT16  TxSuccess;
	    UINT16  TxRetransmit;
	} field;
	UINT32 word;
} TX_STA_CNT1_STRUC;
#endif

typedef struct __TX_CNT_INFO {
	union WTBL_2_DW5 wtbl_2_d5;
	union WTBL_2_DW6 wtbl_2_d6;
	union WTBL_2_DW7 wtbl_2_d7;
	union WTBL_2_DW8 wtbl_2_d8;
	union WTBL_2_DW9 wtbl_2_d9;
} TX_CNT_INFO;


#define E2PROM_CSR          0x0004
#define GPIO_CTRL_CFG	0x0228

#define LEGACY_BASIC_RATE	0x1408

#define HW_BEACON_OFFSET		0x0200
#define HW_BEACON_MAX_SIZE(__pAd)      ((__pAd)->chipCap.BcnMaxHwSize)

struct _RTMP_ADAPTER;
VOID dump_mt_mac_cr(struct _RTMP_ADAPTER *pAd);

INT mt_mac_init(struct _RTMP_ADAPTER *pAd);
INT mt_hw_tb_init(struct _RTMP_ADAPTER *pAd, BOOLEAN bHardReset);

INT mt_wtbl_get_entry234(struct _RTMP_ADAPTER *pAd, UCHAR idx, struct wtbl_entry *ent);
VOID dump_wtbl_entry(struct _RTMP_ADAPTER *pAd, struct wtbl_entry *ent);
VOID dump_wtbl_info(struct _RTMP_ADAPTER *pAd, UINT wtbl_idx);
VOID dump_wtbl_base_info(struct _RTMP_ADAPTER *pAd);

INT mt_mac_set_ctrlch(struct _RTMP_ADAPTER *pAd, UINT8 extch);

USHORT tx_rate_to_tmi_rate(UCHAR mode, UCHAR mcs, UCHAR nss, BOOLEAN stbc, UCHAR preamble);
UCHAR get_nss_by_mcs(UCHAR phy_mode, UCHAR mcs, BOOLEAN stbc);

#define HIF_PORT 1
#define MCU_PORT 2
#define MT_TX_RETRY_UNLIMIT		0x1f
#define MT_TX_SHORT_RETRY		0x0f
#define MT_TX_LONG_RETRY		0x0f
#define MT_RTS_RETRY			0x0f

#endif /* __MT_MAC_H__ */

