#ifndef SPS_IO_KWR__H
#define SPS_IO_KWR__H

/* static char sps49_io__h_rcsid[] = "$Header: /ceswbl2/src/micro/lib/ntds_sps49/RCS/sps49_io_.h,v 6.34.0.1 2007/10/19 14:26:15 ceswbl2 Exp twhite $"; */

/*
 * Developed by JHU/APL
 *
 *
 *      Project:        CEP WASP IOC
 *
 *      Module Name:    sps49_io_.h  ( SPS49 interface communications package )
 *
 *      Synopsis (Usage and Parameters):
 *              See content.
 *
 *
 *      Description:
 *              This include file contains:
 *                      a) constant definitions for use with the NTDS
 *                         protocol package.
 *
 *      Files:
 *              sps49_io.c
 *
 *
 *      Programmer:     M. H. Gates
 *      Organization:   JHU/APL
 *      Host System:    SunOS Release 4.1.3_U1
 *      Language:       C
 *      Date Created:   9/17/92
 *      Modifications:
 *      	$Log: sps49_io_.h,v $
 *      	Revision 6.34.0.1  2007/10/19 14:26:15  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.34  2007/10/18 18:25:37  ceswbl2
 *      	CESWBL2_6_34_OCT_18_07
 *
 *      	Revision 6.33.0.2  2007/10/12 11:29:20  tallman
 *      	Removed notices.  IAW TR#2677
 *
 *      	Revision 6.33.0.1  2007/04/24 16:28:04  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.33  2007/04/23 17:00:31  ceswbl2
 *      	CESWBL2_6_33_APR_23_07
 *
 *      	Revision 6.32.0.1  2006/10/26 16:03:47  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.32  2006/10/25 17:22:24  ceswbl2
 *      	CESWBL2_6_32_OCT_25_06
 *
 *      	Revision 6.31.0.1  2006/04/14 14:49:23  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.31  2006/04/13 19:13:09  ceswbl2
 *      	CESWBL2_6_31_APR_14_06
 *
 *      	Revision 6.30.0.1  2005/10/12 16:51:49  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.30  2005/10/11 20:15:42  ceswbl2
 *      	CESWBL2_6_30_OCT_12_05
 *
 *      	Revision 6.29.0.2  2005/09/21 11:01:25  dbocek
 *      	Added C++ constructs around a "C" extern function, in support
 *      	of changes made to implement variable PD for E2C Trainer, iaw
 *      	TR #2148.
 *
 *      	Revision 6.29.0.1  2004/12/03 14:32:42  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.29  2004/12/02 19:24:32  ceswbl2
 *      	CESWBL2_6_29_DEC_03_04
 *
 *      	Revision 6.28.0.1  2004/06/11 14:14:59  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.28  2004/06/10 19:12:04  ceswbl2
 *      	CESWBL2_6_28_JUN_11_04
 *
 *      	Revision 6.27.0.1  2003/12/17 17:54:45  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.27  2003/12/16 21:05:02  ceswbl2
 *      	CESWBL2_6_27_DEC_17_03
 *
 *      	Revision 6.26.0.1  2003/08/14 19:02:44  cwbl2tst
 *      	Making_Branches
 *
 *      	Revision 6.26  2003/08/13 20:08:29  ceswbl2
 *      	CESWBL2_6_26_AUG_13_03
 *
 *      	Revision 6.25.0.1  2003/04/04 17:43:43  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.25  2003/04/03 21:38:00  ceswbl2
 *      	CESWBL2_6_25_APR_03_03
 *
 *      	Revision 6.24.0.1  2002/12/18 18:20:39  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.24  2002/12/13 19:18:29  ceswbl2
 *      	CESWBL2_6_24_DEC_13_02
 *
 *      	Revision 6.23.0.1  2002/09/06 15:16:27  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.23  2002/09/05 20:57:15  ceswbl2
 *      	CESWBL2_6_23_SEP_05_02
 *
 *      	Revision 6.22.0.1  2002/02/22 15:41:28  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.22  2002/02/20 22:14:26  ceswbl2
 *      	CESWBL2_6_22_FEB_20_02
 *
 *      	Revision 6.21.0.1  2001/08/03 15:35:02  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.21  2001/08/02 20:31:27  ceswbl2
 *      	CESWBL2_6_21_AUG_02_01
 *
 *      	Revision 6.20.0.1  2001/05/09 19:01:41  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.20  2001/05/08 20:34:30  ceswbl2
 *      	CESWBL2_6_20_MAY_08_01
 *
 *      	Revision 6.19.0.1  2001/02/22 16:12:57  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.19  2001/02/21 22:15:48  ceswbl2
 *      	CESWBL2_6_19_FEB_21_01
 *
 *      	Revision 6.18.0.1  2000/11/10 17:50:22  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.18  2000/11/09 21:40:02  ceswbl2
 *      	CESWBL2_6_18_NOV_09_00
 *
 *      	Revision 6.17.0.1  2000/09/08 15:44:07  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.17  2000/09/07 21:26:10  ceswbl2
 *      	CESWBL2_6_17_SEPT_07_00
 *
 *      	Revision 6.16.0.1  2000/06/16 15:54:21  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.16  2000/06/15 21:38:08  ceswbl2
 *      	CESWBL2_6_16_JUN_15_00
 *
 *      	Revision 6.15.0.1  2000/04/13 14:53:08  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.15  2000/04/12 20:11:59  ceswbl2
 *      	CESWBL2_6_15_APR_12_00
 *
 *      	Revision 6.14.0.1  2000/01/28 16:12:58  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.14  2000/01/27 21:19:31  cwbl2adm
 *      	CESWBL2_6_14_JAN_27_00
 *
 *      	Revision 6.13.0.1  1999/10/21 17:43:58  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.13  1999/10/20 20:28:58  ceswbl2
 *      	CESWBL2_6_13_OCT_20_99
 *
 *      	Revision 6.12.0.1  1999/06/24 13:09:59  ceswbl2
 *      	Making_Branches
 *
 *      	Revision 6.12  1999/06/22 21:12:09  ceswbl2
 *      	CESWBL2_6_12_JUN_22_99
 *
 *      	Revision 6.11.0.2  1999/06/21 15:38:30  dbocek
 *      	Adding capability to control the 'dummy load' flag in the WRAP_RESPONSE_
 *      	TEST_MSGs, iaw TR #622.
 *
 *      	Revision 6.11.0.1  1999/03/30 17:40:10  ceswbl2
 *      	Making_Branches
 *
 * Revision 6.11  1999/03/29  20:38:47  ceswbl2
 * CESWBL2_6_11_MAR_29_99
 *
 * Revision 6.10.0.1  1999/02/09  17:24:27  ceswbl2
 * Making_Branches
 *
 * Revision 6.10  1999/02/08  20:39:18  ceswbl2
 * CESWBL2_6_10_FEB_08_98
 *
 * Revision 6.9.0.1  1998/11/06  14:22:05  ceswbl2
 * Making_Branches
 *
 * Revision 6.9  1998/11/05  20:20:26  ceswbl2
 * CESWBL2_6_9_NOV_05_98
 *
 * Revision 6.8.0.1  1998/09/03  15:59:33  ceswbl2
 * Making_Branches
 *
 * Revision 6.8  1998/09/02  20:38:32  ceswbl2
 * CESWBL2_6_8_SEPT_02_98
 *
 * Revision 6.7.0.3  1998/08/17  20:13:22  mah
 * Changed the getWrapReference function protocol
 * so as to support unsigned time variable IAW TR343.
 *
 * Revision 6.7.0.2  1998/07/28  20:32:13  mah
 * Commented out rcsid string to avoid unused
 * compiler warning IAW TR#315.
 *
 * Revision 6.7.0.1  1998/06/18  16:25:39  ceswbl2
 * Making_Branches
 *
 * Revision 6.7  1998/06/16  21:35:49  ceswbl2
 * CESWBL2_6_7_JUN_16_98
 *
 * Revision 6.6.0.1  1998/05/11  18:59:45  ceswbl2
 * Making_Branches
 *
 * Revision 6.6  1998/05/08  18:41:19  ceswbl2
 * CESWBL2_6_6_MAY_8_98
 *
 * Revision 6.5.0.1  1998/03/18  16:19:36  ceswbl2
 * Making_Branches
 *
 * Revision 6.5  1998/03/17  21:14:38  ceswbl2
 * CESWBL2_6_5_MAR_17_98
 *
 * Revision 6.4.0.1  1998/01/14  14:30:12  ceswbl2
 * Making_Branches
 *
 * Revision 6.4  1998/01/13  21:16:01  ceswbl2
 * CESWBL2_6_4_JAN_13_98
 *
 * Revision 6.3.0.1  1997/11/20  21:47:48  ceswbl2
 * Making_Branches
 *
 * Revision 6.3  1997/11/19  21:23:29  ceswbl2
 * CESWBL2_6_3_NOV_19_97
 *
 * Revision 6.2.0.2  1997/11/14  19:56:18  nancy
 * support counters for ef's and wrap messages; support
 * dx of wrap messages
 *
 * Revision 6.2.0.1  1997/10/08  14:31:18  ceswbl2
 * Making_Branches
 *
 * Revision 6.2  1997/10/07  20:58:51  ceswbl2
 * CESWBL2_6_2_OCT_07_97
 *
 * Revision 6.1.0.1  1997/09/12  17:02:17  ceswbl2
 * Making_Branches
 *
 * Revision 6.1  1997/09/12  14:30:38  ceswbl2
 * CESWBL2_6_1_SEP_12_97
 *
 */

//#include "rtc_.h"  /* needed for CLOCK structure */

/**************************************************************/
/*      Type Definitions for the r49_io Module Body only      */
/**************************************************************/
 
typedef struct
{
        unsigned nw:			8;
        unsigned bufno:			4;
        unsigned efcode:		4;
        unsigned unused:		16;
} EF_TYPE_16;
 
typedef struct
{
        unsigned unused:		16;
        unsigned nw:			8;
        unsigned bufno:			4;
        unsigned efcode:		4;
}EF_TYPE_32;
 
typedef union
{
	EF_TYPE_16		w16;
	EF_TYPE_32		w32;
} SPS49_EF_TYPE;

/* 
 * There is no "standard" header on messages -
 * for messages going from sys2 to cepwasp the bufno field of the EF
 * must be used to identify type of message that is coming.  Each
 * type of message is fixed length.  For outgoing messages application
 * must specify nw and bufno. If protocol can handle wrap-around test
 * message then all buffers coming from application will go to bufno 1.
 */

/* Test Pattern Words */
#define TWA	 070707
#define TWB	0107070

/*
 *  Messages passed between protocl and application will have a
 *  header word added to identify size and message type because
 *  actual messages have no standard header.  Messages sent and
 *  received via antares (sys) will not have this header.
 */
typedef struct
{
	short	nw;	/* 32-bit words */
	short	mt;	/* sps49 message*/
} SPS49_MSG_HDR;

/* Wrap-Around Test Response Message */
typedef	struct
{
	SPS49_MSG_HDR	mhdr;
	unsigned int	ur	:1,
			s8	:1,
			s7	:1,
			s6	:1,
			s5	:1,
			s4	:1,
			s3	:1,
			s2	:1,
			vbn	:4,
			s1	:1,
			spare1	:3,
			spare2	:1,
			ctr	:2,
			tdelta	:13;
	unsigned int	btp1	:16,
			btp2	:16;
	unsigned int	tpr1	:16,
			tpr2	:16;
	unsigned int	spare3	:10,
			fxtcf	:1,
			mtcf	:1,
			duml	:1,
			cs	:1,
			stao	:1,
			he	:1,
			spare4	:16;
} WRAP_AROUND_RESP_MSG;

#define WRAP_AROUND_RESP_MSG_SZ	sizeof(WRAP_AROUND_RESP_MSG)

/* Wrap-Around Test Message */
typedef	struct
{
	SPS49_MSG_HDR	mhdr;
	unsigned int	fwb	:1,
			spare1	:13,
			ctr	:2,
			rtc_hi	:16;
	unsigned int	rtc_lo	:16,
			btp1	:16;
	unsigned int	btp2	:16,
			spare2	:16;
} WRAP_AROUND_TEST_MSG;

#define WRAP_AROUND_TEST_MSG_SZ	sizeof(WRAP_AROUND_TEST_MSG)

#ifdef __cplusplus
	extern "C" {
#endif

/* #########################################################################
*
*      SYNOPSIS:       Initialize_SPS_Interface
*
*      DESCRIPTION:    This function sets up the protocol layer and device
*                      driver for communications.  It should only be called
*                      once with a list of devices that will use the SPS
*                      protocol.
*
*      PARAMETERS:
*
*        INPUT device_node : This parameter is a pointer to the DEVICE_DATA
*                            type that contains the information required to
*                            configure a device or group of devices.
*
*      RETURNS   status
*
* #########################################################################*/
int Initialize_SPS_Interface (DEVICE_DATA *devices_ptr);


/* function definitions */

void  Set_SPS_Type (int port, int intf_type);
int   Init_SPS_Comm (int device);
void  getWrapReference(int port, CLOCK *wrapTime, int *wrapCtr); 
void  clearXferCounts(int port);
int   numRcvdEc(int port);
int   numRcvdClr(int port);
int   numRcvdRd(int port);
int   numRcvdRtr(int port);
int   numRcvdDc(int port);
int   numRcvdWrapTest(int port);
int   numSentEca(int port);
int   numSentRd(int port);
int   numSentRtr(int port);
int   numSentWrapResp(int port);


//STATUS setDumlWrapResp(int val);

/* these functions are within the SPS-49 Simulation */
void SendWrapRespMesg(WRAP_AROUND_RESP_MSG *wrap_resp);
void RecvWrapTestMesg(WRAP_AROUND_TEST_MSG *wrap_test);

#ifdef __cplusplus
}
#endif

int getDumlWrapResp(void);


#endif // #define SPS_IO_KWR__H
