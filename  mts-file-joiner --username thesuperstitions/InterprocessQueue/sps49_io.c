
/******************************************
 *   System-wide includes 	          *
 ******************************************/

/* ################### */
/* # Module INCLUDES # */
/* ################### */
#include "vxWorks.h"
//#include "ctype.h"
//#include "inetLib.h"
//#include "ioLib.h"
//#include "iv.h"
//#include "strLib.h"
//#include "sysLib.h"
//#include "sysSymTbl.h"
//#include "taskLib.h"
//#include "msgQLib.h"
//#include "semLib.h"
//#include "memLib.h"
//#include "vme.h"
#include "stdio.h"
//#include "errnoLib.h"
//#include "logLib.h"

//#include "nio.h"
#include "ntds_comm_.h" 
//#include "ntds_devices.h"
//#include "ntds_drivers.h"
#include "ntds_sys_.h"
#include "ntds_config.h" 
//#ifndef	SOLARIS_WASP
//#include "nio_trace_.h"
//#endif
//#include "wrap_io_.h"
//#include "crt_ctrl_.h"

//#include "ceswbl2.h"
//#include "ceswbl2_msg.h"
//#include "rtc_.h"

#include "sps49_io_.h" 

//#ifdef SOLARIS_WASP
    /* WASP and CEP have different interfaces but identical names
    *  for the functions below. This causes a namespace clash in the
    *  workstation environment which uses the CEP's version of
    *  ntds_common. Resolve by changing WASP's function names with
    *  the #defines below, and supplying a copy of the WASP
    *  version of the functions in ntds_wasp.cpp in the
    *  workstation adaptation software.
    */

//#include "ntds_wasp.h" /* prototypes for WASP versions of functions */

//#define printf printf_WASP
//#define Get_NTDS_Partition Get_NTDS_Partition_WASP
//#endif /* SOLARIS_WASP */

/**********************************************************************
 * Constant Definitions for the sps_io Package Body only              *
 **********************************************************************/

/* #define LEVEL2	 Include LEVEL2 testing capability. */

#define NTDS_ERROR_PRIORITY  30
#define CHAN_STAT_PRIORITY   32
#define RECV_TST_PRIORITY    34
#define NTDS_IN_PRIORITY     36
#define NTDS_OUT_PRIORITY    38

/* define MAX buffer sizes (bytes) */
#define MAX_SPS_WRDS	     256
#define SPS_RCV_SIZE         ( MAX_SPS_WRDS * 4 )
#define SPS_SND_SIZE         ( MAX_SPS_WRDS * 4 )
#define MAX_RETRY            1
#define MAX_NUM_MESGS        3
#define MAX_EIS              6 
#define INPUT_Q              0
#define OUTPUT_Q             1
#define ERROR_Q              2
#define CHANNEL_Q            3
#define RETRY_COUNT			 0

/******************************************************************
 * Static Data Definitions Needed by this module                  *
 ******************************************************************/
static int REC_Count[NUM_OF_NTDS_PORTS];
static int RDC_Count[NUM_OF_NTDS_PORTS];
static int SECA_Count[NUM_OF_NTDS_PORTS];
static int SRD_Count[NUM_OF_NTDS_PORTS];
static int RRD_Count[NUM_OF_NTDS_PORTS];
static int SRTR_Count[NUM_OF_NTDS_PORTS];
static int RRTR_Count[NUM_OF_NTDS_PORTS];
static int RCLR_Count[NUM_OF_NTDS_PORTS];
static int STest_Count[NUM_OF_NTDS_PORTS];
static int RTest_Count[NUM_OF_NTDS_PORTS];
static int SMesg_Count[NUM_OF_NTDS_PORTS];
static int RMesg_Count[NUM_OF_NTDS_PORTS];
static int DqMesg_Count[NUM_OF_NTDS_PORTS];
static int OB_TO_Count[NUM_OF_NTDS_PORTS];
static int IB_TO_Count[NUM_OF_NTDS_PORTS];

//static NTDS_QUE_ID TM_Que_Index[NUM_OF_NTDS_PORTS];
//static MSG_Q_ID Que_List[NUM_OF_NTDS_PORTS][MAX_EIS];
static int Max_Snd_Size[NUM_OF_NTDS_PORTS];
static int Max_Rcv_Size[NUM_OF_NTDS_PORTS];
//static SEM_ID Recovery_Sem[NUM_OF_NTDS_PORTS];
//static SEM_ID Sps_Wrap_Sem[NUM_OF_NTDS_PORTS];
//static CLOCK WrapRdTime[NUM_OF_NTDS_PORTS];
//static CLOCK WrapLastTime[NUM_OF_NTDS_PORTS];
//static int WrapLastCtr[NUM_OF_NTDS_PORTS];
//static int ChanClear[NUM_OF_NTDS_PORTS];

/* Allows the protocol to determine what type of EF/EI packing to implement */
static unsigned int	Word_Width[NUM_OF_NTDS_PORTS];

static int IntfType[NUM_OF_NTDS_PORTS];  /* 0 => (V)5, 1 => MPU */
static NIO_MESG comm_ef_packet;

/* The zeroth index is used to keep track of the number of ports configured */
static int	Configured[NUM_OF_NTDS_PORTS+1] = {0};

/*  Determines if the application has disabled the interface */
static int	Local_Disable[NUM_OF_NTDS_PORTS];

/*************************************************************
 * Global Function Declarations Needed by THIS module ONLY   *
 * (ie "internal routines).  They should be declared as      *
 * 'static'.                                                 *
 *************************************************************/

//static int sps_status_task (int device, int port);
//static int sps_input_task (int device, int port);
//static int sps_output_task (int device, int port);
//static int sps_error_task (int device, int port);
//static int sps_recv_test_task (int device, int port);
//static int sps_output_ei_proc(int device, int port, NTDS_OUTPUT_MSGS *out_buff,
//                              int *retry, int test_msg);
//static void sps_display ();
//static void setWrapReference(int port, CLOCK wrapTime, int wrapCtr);
static void parse_sps_input (int port, int data_src, NIO_MESG *in_packet);
//static int sps_failed_comm_proc (int device, int port, int err);


/* SPS49/CEP EXTERNAL FUNCTION AND EXTERNAL INTERRUPT CODES */
 
#define RD      0x01    /* Receive Data CEPW <--> SYS-2 */
#define RTR     0x02    /* Ready to Receive CEPW <--> SYS-2 */
#define EC      0x03    /* Enable Communications SYS-2 -> CEPW */
#define DC      0x04    /* Disable Communications SYS-2 --> CEPW */
#define ECA     0x05    /* Enable Communications Acknowledge CEPW -> SYS-2 */
#define MPU_ECA 0x06    /* MPU Enable Communications Acknowledge CEPW -> SYS-2 */
#define CLR     0x07    /* Negative Acknowledge CEPW <--> SYS-2 */
  
/* Error codes in unsolicited Wrap_Response */
#define BUFLEN  0x02    /* Buffer count mismatch  CEPW <--> CSS */
#define EFSEQ   0x03    /* EF Out of Sequence  CEPW <--> CSS    */
#define BADEI   0x04    /* Invalid EI received CEPW <--> CSS    */
#define IBTO    0x05    /* Input Buffer Timeout CEPW <--> CSS   */
#define OBTO    0x06    /* Output Buffer Timeout CEPW <--> CSS  */
	 
/* Messages (Buffer nos.) from SYS2 to SPS49 */
#define GEN_DATA_BUF1   0;
#define WRAP_TEST_BUF   1
#define RPC_GATE_BUF    2
#define EM_GATE_BUF     3
#define SMC_GATE_BUF    4
#define TGT_GATE_BUF    5
#define TEST_TGT_BUF    6

/* Messages (Buffer nos.) from SPS49 to SYS2 */
#define GEN_DATA_BUF2   0;
#define WRAP_RESP_BUF   1

/******************  Receive EI Masks   *****************/
#define SPS49_EI_MASK  0x0000000F  /* Mask to use for detecting EI types*/

/* #define IO_TIMEOUT  3   Timeout value for low level I/O requests  */
/* #define IN_TIMEOUT  5   Timeout value for low level I/O requests  */

#define IO_TIMEOUT  (sysClkRateGet()/8 + 1)  /* Timeout value of 125ms for I/O requests. */
#define IN_TIMEOUT  (sysClkRateGet()/8 + 1)  /* Timeout value of 125ms for inbound transfers. */

/* ############################################ */
/* Module EXTERNAL needed FROM other modules  # */
/* ############################################ */

/* #########################################################################
 *
 *      SYNOPSIS:       Initialize_SPS_Interface
 *
 *      DESCRIPTION:    This function sets up the protocol layer and device
 *                      driver for communications.
 *
 *      PARAMETERS:
 *              INPUT   device:   int
 *		        type:     int
 *
 *      RETURNS   status
 *
 * #########################################################################*/

static	int	SPS_Cmds_Logged = 1;

int Initialize_SPS_Interface (DEVICE_DATA *sps_device)
{
	DEVICE_DATA	*device_node_ptr;
	int	status;
	//int	proc_id;
	char	*chan_proc;
	char	*tst_proc;
	char	*in_proc;
	char	*out_proc;
	char	*err_proc;

	device_node_ptr = sps_device;
  sprintf(device_node_ptr->name_string, "R49"); // KWR Framework

/*	Save the run time word width so we do the right interfacing */
	Word_Width[device_node_ptr->port] = device_node_ptr->board.word_size;

	//printf("SPS device_id = 0x%x\n", device_node_ptr->device_id);
	//printf("SPS port = 0x%x\n", device_node_ptr->port);

	//printf("SPS raw_input_que_type = 0x%x\n", device_node_ptr->raw_input_que_type);
	//printf("SPS packed_output_queue = 0x%x\n", device_node_ptr->packed_output_queue);
	//printf("SPS in_signal_queue = 0x%x\n", device_node_ptr->in_signal_queue);
	//printf("SPS out_signal_queue = 0x%x\n", device_node_ptr->out_signal_queue);
	//printf("SPS name_string = 0x%x\n", (int)device_node_ptr->name_string);
	//
	//printf("SPS user1 = 0x%x\n", device_node_ptr->user1); /* used as interface type indicator */
	//printf("SPS user2 = 0x%x\n", device_node_ptr->user2);
	//printf("SPS user3 = 0x%x\n", device_node_ptr->user3);
	//printf("SPS user4 = 0x%x\n", device_node_ptr->user4);
	//printf("SPS user5 = 0x%x\n", device_node_ptr->user5);

	//printf("SPS primary_ntds_port_address = 0x%x\n", device_node_ptr->board.primary_ntds_port_address);
	//printf("SPS secondary_ntds_port_address = 0x%x\n", device_node_ptr->board.secondary_ntds_port_address);
	//printf("SPS address_modifier = 0x%x\n", device_node_ptr->board.address_modifier);
	//printf("SPS enet_address = 0x%x\n", (int)device_node_ptr->board.enet_address);
	//printf("SPS enet_port = 0x%x\n", device_node_ptr->board.enet_port);

	//printf("SPS io_mode = 0x%x\n", device_node_ptr->board.io_mode);
	//printf("SPS interrupt_level = 0x%x\n", device_node_ptr->board.interrupt_level);
	//printf("SPS manual_ei_mode = 0x%x\n", device_node_ptr->board.manual_ei_mode);
	//printf("SPS word_size = 0x%x\n", device_node_ptr->board.word_size);
	//printf("SPS io_type = 0x%x\n", device_node_ptr->board.io_type);
	//printf("SPS int_enable = 0x%x\n", device_node_ptr->board.int_enable);
	//printf("SPS passive_mode = 0x%x\n", device_node_ptr->board.passive_mode);
	//printf("SPS server_enable = 0x%x\n", device_node_ptr->board.server_enable);
	//printf("SPS driver_type = 0x%x\n", device_node_ptr->board.driver_type);
	//printf("SPS secondary_driver_type = 0x%x\n", device_node_ptr->board.secondary_driver_type);
	//printf("SPS init_mode = 0x%x\n", device_node_ptr->board.init_mode);

	//printf("SPS next = 0x%x\n", (int)device_node_ptr->next);

	Configured[0]++; /* Update configured count */
	Configured[device_node_ptr->port+1] = TRUE;
	Local_Disable[device_node_ptr->port] = TRUE;

	/* identify functions for NTDS_Control */
	device_node_ptr->function.init_comm = NULL;
	device_node_ptr->function.enable_comm =  NULL;
	device_node_ptr->function.disable_comm =  NULL;
	device_node_ptr->function.reset_comm =  NULL;
	device_node_ptr->function.restart_comm =  NULL;
	device_node_ptr->function.test_comm =  NULL;
	device_node_ptr->function.output_comm =  NULL;
	device_node_ptr->function.input_comm =  NULL;
	device_node_ptr->function.spcl_comm =  NULL;
	device_node_ptr->function.suspend_comm =  NULL;
	device_node_ptr->function.resume_comm =  NULL;

	///* Create the semaphore for recovering from failed communications*/
	//if((STATUS)(Recovery_Sem[device_node_ptr->port] =
	//	semMCreate(SEM_INVERSION_SAFE|SEM_Q_PRIORITY)) == NULL)
	//{
	//	printf( 
	//		"SPS:Can't create recovery semaphore, device %x\n",
	//			device_node_ptr->device_id);
	//	return (ERROR);
	//}

	///* create the semaphore used to protect WrapTime and Ctr */
	///* Sps_Wrap_Sem[device_node_ptr->port] = semBCreate(SEM_Q_FIFO, SEM_FULL);*/
	//Sps_Wrap_Sem[device_node_ptr->port] = semMCreate(SEM_INVERSION_SAFE|SEM_Q_PRIORITY);
	//if (Sps_Wrap_Sem[device_node_ptr->port] == NULL)
	//{
	//	printf ( "SPS:can't create Wrap sem\n");
	//	return(ERROR);
	//}

	/* Initialize the NTDS Interface */
	status = Configure_NTDS_Device(sps_device);
	if (status != OK)
	{
		Log_NTDS_Mesg (device_node_ptr->device_id, NTDS_ERROR_CAT, 
                    "RDR49:Init-%d Configure NTDS Failure 0x%x\n", 
                    device_node_ptr->port, status);
		return(status);
	}

	/* Clear all Initialization flags for initialization start */
	//clearXferCounts(device_node_ptr->port);

	/* initialize channel status */
	Report_Port_Status(device_node_ptr->port, CHANNEL_RESET);

	/* establish interface type */
/*	IntfType[port] = intf_type; */
	IntfType[device_node_ptr->port] = device_node_ptr->user1; /* Interface type indicator */

	chan_proc = "SPS_STATUS";
	tst_proc  = "SPS_RCV_TST";
	in_proc   = "SPS_INPUT";
	out_proc  = "SPS_OUTPUT";
	err_proc  = "SPS_ERR";
	Max_Snd_Size[device_node_ptr->port] = SPS_SND_SIZE;
	Max_Rcv_Size[device_node_ptr->port] = SPS_RCV_SIZE;

	/* Spawn and activate the input process */
	//if((proc_id =
	//    taskSpawn(in_proc, NTDS_IN_PRIORITY,VX_FP_TASK|VX_STDIO,
	//	    8192, sps_input_task, device_node_ptr->device_id, device_node_ptr->port, 0, 0, 0, 0, 0, 0, 0, 0)) == ERROR)
	//{
	//	printf( 
	//		"SPS:Error Spawning Protocol Input Task");
	//	return(errnoGet());
	//}

	/* Spawn and activate the output process */
	//if((proc_id =
	//    taskSpawn(out_proc, NTDS_OUT_PRIORITY,VX_FP_TASK|VX_STDIO,
	//	    8192, sps_output_task, device_node_ptr->device_id, device_node_ptr->port, 0, 0, 0, 0, 0, 0, 0, 0)) == ERROR)
	//{
	//	printf( 
	//		"SPS:Error Spawning Protocol Output Task");
	//	return(errnoGet());
	//}

	/* Spawn and activate the error process */
	//if((proc_id =
	//    taskSpawn(err_proc, NTDS_ERROR_PRIORITY,VX_FP_TASK|VX_STDIO,
	//	    8192, sps_error_task, device_node_ptr->device_id, device_node_ptr->port, 0, 0, 0, 0, 0, 0, 0, 0)) == ERROR)
	//{
	//	printf( 
	//		"SPS:Error Spawning Protocol Error Task");
	//	return(errnoGet());
	//}

	/* Spawn and activate the channel_status process */
	//if((proc_id =
	//	taskSpawn(chan_proc, CHAN_STAT_PRIORITY,VX_FP_TASK|VX_STDIO,
	//		8192, sps_status_task, device_node_ptr->device_id, device_node_ptr->port, 0, 0, 0, 0, 0, 0, 0, 0)) == ERROR)
	//{
	//	printf( 
	//		"SPS:Error Spawning Protocol Channel Status Task");
	//	return(errnoGet());
	//}

	/* Spawn and activate the recv_test process */
	//if((proc_id =
	//        taskSpawn(tst_proc, RECV_TST_PRIORITY,VX_FP_TASK|VX_STDIO,
	//		8192, sps_recv_test_task, device_node_ptr->device_id, device_node_ptr->port, 0, 0, 0, 0, 0, 0, 0, 0)) == ERROR)
	//{
	//	printf( 
	//		"SPS:Error Spawning Protocol Recv Test Msg Task");
	//	    return(errnoGet());
	//}

	Log_NTDS_Mesg (device_node_ptr->device_id, NTDS_ERROR_CAT,"SPS:NTDS CHANNEL PORT IS CONFIGURED");

	//if ( SPS_Cmds_Logged )
	//{
	//	Log_NTDS_Cmnd("spsio", "SPS49 Proto Status and Counts", FALSE,
	//		sps_display, 1);

	//}
	SPS_Cmds_Logged = 0;

	return (OK);
}

/* #########################################################################
 *
 *      SYNOPSIS:       Set_SPS_Type
 *
 *      DESCRIPTION:    This function records the interface type as V5 or 
 *                      MPU and sets up the Enb Comm Ack EF code
 *
 *      PARAMETERS:
 *              INPUT   port:       int
 *                      intf_type:  int
 *
 *      RETURNS   no value returned
 *
 * #########################################################################*/

//void Set_SPS_Type (int port, int intf_type)
//{
//	SPS49_EF_TYPE	*sending_ef;
//
//	IntfType[port] = intf_type;
///*	*comm_ef_packet.address = (IntfType[port]) ? MPU_ECA : ECA; */
//
//	sending_ef = (SPS49_EF_TYPE *)comm_ef_packet.address;
//	if (Word_Width[port] == WORD_16)
//		sending_ef->w16.efcode = (IntfType[port]) ? MPU_ECA : ECA;
//	else
//		sending_ef->w32.efcode = (IntfType[port]) ? MPU_ECA : ECA;
//
//	printf("TYPE %d  ECA %d\n", IntfType[port], *comm_ef_packet.address);
//
//}

/* #########################################################################
 *
 *      SYNOPSIS:       sps_output_task
 *
 *      DESCRIPTION:    This is the output task used for the NTDS interface.
 *                      It monitors the output message queue for messages to
 *                      send.  Messages are routed to the appropriate device
 *                      using the interface protocol.
 *
 *      PARAMETERS:
 *              INPUT   device:   int
 *                      port:     int
 *
 *      RETURNS   NOTHING
 *
 *      COMMENTS:  This is a non-terminating task.
 *
 *
 * #########################################################################*/

//static int sps_output_task (int device, int port)
//{
//	SPS49_MSG_HDR	*header;
//	SPS49_EF_TYPE	*ef_word;
//	NTDS_OUTPUT_MSGS  buff;
//	NTDS_OUTPUT_MSGS  nbuf;
//	NIO_MESG	ef_packet;
//	PART_ID		part_id;
//	int status;
//	int timeout_count;
//	int ob_retry;
//	int retry;
//	int test_msg;
//	int consecutive_fails = 0;
//
//	/* this is needed to catch out-of-order EFs */
//	unsigned int	*output_ei_lock_address[3];
//	static unsigned int	output_ei_list[] =
//	{
//		RTR,
//		EI_LIST_END
//	};
//
//	/* Initialize ei_lock_addresses */
//	output_ei_lock_address[0] = NULL;
//	output_ei_lock_address[1] = NULL;
//	output_ei_lock_address[2] = NULL;
//
//	/* Initialize EF function packets */
//	ef_packet.req_size = 1;
//	ef_packet.delay_time = 0;
//	ef_packet.time_out = IO_TIMEOUT;
//	ef_packet.retry_count = RETRY_COUNT;
//	ef_packet.address =
//		(unsigned int *) Get_NTDS_Buffer( WORD_32, &part_id );
//	ef_word = (SPS49_EF_TYPE *) ef_packet.address;
//
//	/* Register for output task EI's */
//	status = Create_EI_Q (port, SPS49_EI_MASK, output_ei_list,
//			&Que_List[port][OUTPUT_Q]);
//	if (status != OK)
//	{
//		logMsg("CREATE EI Q FAILURE. 0x%x\n", status);
//		return( ERROR );
//	}
//
//	/* lock output_ei_list so if any come in they are sent elsewhere */
//	Change_EI_Lock(port, &output_ei_list[0], &output_ei_lock_address[0],
//			LOCK);
//
//	ob_retry = 0;
//	while (TRUE)
//	{
//		/* Wait for a message to be queued for NTDS output */
//		status = Deque_Output_Mesg (port, &buff,
//				(unsigned int)WAIT_FOREVER);
//		if (status != OK)
//			logMsg("Deque MsgQueue Error 0x%x\n", status);
//		else
//		{
//			/* increment msg status count, get header for size */
//			DqMesg_Count[port]++;
//			header = (SPS49_MSG_HDR *) buff.io_pkt.address;
//
//			/* Test message size for tolerance */
//			if (header->nw > Max_Snd_Size[port])
//			{
//				logMsg("TYPE %o MESSAGE SIZE FAULT %x\n",
//					header->mt, header->nw);
///*				status = Free_NTDS_Msg_Buffer(buff.partition_id,
//					(char *)buff.io_pkt.address);
//*/
//			}
//			else
//			{
//				/* copy buff to nbuf and modify */
//				nbuf = buff;
//				nbuf.io_pkt.address = buff.io_pkt.address + 1;
//				nbuf.io_pkt.req_size = buff.io_pkt.req_size - 1;
//
//
//				/* Format RD EF for current message */
//				if (Word_Width[port] == WORD_16)
//				{
//					ef_word->w16.efcode = RD;
//					ef_word->w16.nw = buff.io_pkt.req_size - 1;
//					ef_word->w16.unused = 0;
//				}
//				else /* 32 bit case */
//				{
//					ef_word->w32.efcode = RD;
//					ef_word->w32.nw = buff.io_pkt.req_size - 1;
//					ef_word->w32.unused = 0;
//				}
//
//				/* check if this is a test message */
//				if (Word_Width[port] == WORD_16)
//				{
//					if (header->mt == WRAP_RESP_BUF)
//					{
//						test_msg = TRUE;
//						ef_word->w16.bufno = 1;
//					}
//					else
//					{
//						test_msg = FALSE;
//						ef_word->w16.bufno = 0;
//					}
//				}
//				else /* 32 bit case */
//				{
//					if (header->mt == WRAP_RESP_BUF)
//					{
//						test_msg = TRUE;
//						ef_word->w32.bufno = 1;
//					}
//					else
//					{
//						test_msg = FALSE;
//						ef_word->w32.bufno = 0;
//					}
//				}
//
//				/* Check if NTDS channel is ready */
//				if (!((Get_Port_Status(port) == CHANNEL_READY)||
//				    ((Get_Port_Status(port) == CHANNEL_ENABLED) &&
//				     test_msg)))
//
//				{
//					logMsg("INTERFACE NOT ENABLED\n", port);
///*					status = Free_NTDS_Msg_Buffer(
//						buff.partition_id,
//						(char *)buff.io_pkt.address);
//*/
//				}
//				else /* Prepare and send the message */
//				{
//					ob_retry = 0;
//
//					/* unlock output_ei_list */
//					Change_EI_Lock(port, &output_ei_list[0],
//							&output_ei_lock_address[0], UNLOCK);
//
//
//
//					do  /* Retry Output Message failure Loop for TIMEOUTerror */
//					{
//						timeout_count = 0;
//
//						/* Resync output EI when RD received */
//						status = Flush_EI_Que(port, Que_List[port][OUTPUT_Q]);
//						if(status != OK)
//							logMsg("Flush Output EI ERR %x\n",
//								status);
//
//						do  /* Retry Send RD EF Loop, if no response, restart */
//						{
//							status = Send_EF (port, &ef_packet, NORMAL_EF);
//							if (status == NIO_TIMEOUT)
//							{
//								/*OB_TO_Count[port]++;*/
//								consecutive_fails++;
//								timeout_count++;
//							}
//						} while ((status == NIO_TIMEOUT) && (timeout_count < MAX_RETRY));
//						if (status != OK)
//						{
//							logMsg("SEND RD ERR:0x%x\n", status);
//							ob_retry = MAX_RETRY; /* force restart */
//							break;
//						}
//						else
//						{  /* RD sent, wait for RTR or NRTR EI */
//
//
//
//							retry = FALSE;
//							SRD_Count[port]++;
//
//							status = sps_output_ei_proc(device, port,
//									&nbuf,&retry, test_msg);
//							if (retry == FALSE)
//							{
//								if (status != OK)
//								{
//									/* code folded from here */
//									logMsg("OUTPUT ERROR - %x\n", status);
//									consecutive_fails++;
//									ob_retry = MAX_RETRY; /* force channel reinit */
//									/* unfolding */
//								}
//								/* otherwise either the message was sent */
//								/*  or the channel is down               */
//
//								break;
//							}
//							else if (retry == TRUE)
//								ob_retry ++;
//
//						} /* end else, send RD processing */
//
//					} while (( ob_retry < MAX_RETRY) && ( retry == TRUE) &&
//					    (Get_Port_Status(port) == CHANNEL_READY));
//
//					/* lock output_ei_list */
//					Change_EI_Lock(port, &output_ei_list[0],
//							&output_ei_lock_address[0], LOCK);
//
///*					status = Free_NTDS_Msg_Buffer(buff.partition_id,
//								(char *)buff.io_pkt.address);
//*/
//
//					/* if 5 consecutive tries fail - declare down */
//					if (ob_retry >= MAX_RETRY && consecutive_fails == 5)
//					{
//							ob_retry = 0;
//							consecutive_fails = 0;
//
//							logMsg("Declaring Interface DOWN\n");
//							Report_Port_Status(port, CHANNEL_DISABLED);
//					}
//					/* Restart channel, if Send message retry limit reached */
//					else if (ob_retry >= MAX_RETRY)
//					{
//						ob_retry = 0;
//						OB_TO_Count[port]++;
//						status = sps_failed_comm_proc(device, port, OBTO);
//						if (status != OK)
//						{
//							logMsg("UNABLE TO REINIT COMM\n");
//							Report_Port_Status(port, CHANNEL_DISABLED);
//						}
//					}
//					/* message transferred okay */
//					else
//					{
//							ob_retry = 0;
//							consecutive_fails = 0;
//					}
//
//				} /* end else, channel not enabled */
//			} /* end else, send message size error */
//		} /* end else, deque send message error */
//
//		if( buff.free_buffer == FREE_MESG_BUFFER )
//		{
//			status = Free_NTDS_Msg_Buffer(buff.partition_id,
//				(char *)buff.io_pkt.address);
//		}
//
//	} /* end while true */
//
//} /* end output process */

/* #########################################################################
 *
 *      SYNOPSIS:       sps_output_ei_proc
 *
 *      DESCRIPTION:    This function  deques and processes external
 *                      interrupts used by the output message transfer
 *                      process within sps protocol.
 *
 *      PARAMETERS:
 *              INPUT   device: int
 *                      port:   int
 *                      out_buff * unsigned
 *
 *              OUTPUT  retry   int
 *
 *      RETURNS  status of external interrupt transfers. 
 *
 *      COMMENTS
 *
 *
 * #########################################################################*/
//static int sps_output_ei_proc(int device, int port, NTDS_OUTPUT_MSGS *out_buff,
//                              int *retry, int test_msg)
//{
//	SPS49_EF_TYPE *ei_word;
//	NIO_MESG ei_packet;
//	PART_ID part_id;
//	int status;
//	int rtr_code;
//
//
//	ei_packet.req_size = 1;
//	ei_packet.delay_time = 0;
//	ei_packet.time_out = IO_TIMEOUT;
//	ei_packet.retry_count = RETRY_COUNT;
//	ei_packet.address = (unsigned int *) Get_NTDS_Buffer( WORD_32, &part_id );
//
//	*retry = FALSE;
//	status = Deque_EI(port, &ei_packet, Que_List[port][OUTPUT_Q]);
//	if (status != OK)
//	{
//		if (status == S_objLib_OBJ_TIMEOUT) /* was NIO_TIMEOUT */
//		{
//			if ((Get_Port_Status (port) == CHANNEL_READY) ||
//			    ((Get_Port_Status (port) == CHANNEL_ENABLED) &&
//			      test_msg))
//			{
//				*retry = FALSE;
//				status = OK;
//				logMsg("RTR(nw=%d) not received - sending NAK\n",
//					out_buff->io_pkt.req_size);
//				sps_failed_comm_proc(device, port, OBTO);
//			}
//			else /* channel is down, throw away the message */
//			{
//				status = OK;
//				*retry = FALSE;
//			}
//		}
//		if (Free_NTDS_Msg_Buffer(part_id, (char *)ei_packet.address ) != NULL)
//		{
//			logMsg("Error returning buffer to pool 0x%x\n",
//				errnoGet());
//		}
//		return (status);
//	}
//
//	/* should REALLY LOCK ei's here but for now done after return */
//	*retry = FALSE;
//
//	/* make sure number words matches request */
//	ei_word = (SPS49_EF_TYPE *)ei_packet.address;
//
//	if (Word_Width[port] == WORD_16)
//	{
//		if (ei_word->w16.nw != (out_buff->io_pkt.req_size))
//		{
//			status = sps_failed_comm_proc(device, port, BUFLEN);
//			logMsg("RTR NW %d != RD NW %d\n", ei_word->w16.nw,
//				out_buff->io_pkt.req_size);
//			return(ERROR);
//		}
//	}
//	else /* 32 bit case */
//	{
//		if (ei_word->w32.nw != (out_buff->io_pkt.req_size))
//		{
//			status = sps_failed_comm_proc(device, port, BUFLEN);
//			logMsg("RTR NW %d != RD NW %d\n", ei_word->w32.nw,
//				out_buff->io_pkt.req_size);
//			return(ERROR);
//		}
//	}
//
//	/* If RTR received, send output message */
//
//	if (Word_Width[port] == WORD_16)
//		rtr_code = ei_word->w16.efcode; 
//	else /* 32 bit case */
//		rtr_code = ei_word->w32.efcode; 
//
//	switch (rtr_code)
//	{
//	case RTR:
//		RRTR_Count[port]++;
//
//		if (Word_Width[port] == WORD_16)
//			out_buff->io_pkt.req_size *= WORD_16;
//
//
//		/* Send Dequed message data buffer */
//		status = Send_OB(port, &out_buff->io_pkt, NULL, NULL);
//		if (status != OK)
//		{
//			/* process send ob data buffer status errors */
//			if (status != NIO_TIMEOUT)
//			{
//				logMsg("SEND OB FAULT %x\n", status);
//				break;
//			}
//			else /* send ob status == TIMEOUT */
//			{
//				if ((Get_Port_Status (port) == CHANNEL_READY) ||
//				   ((Get_Port_Status (port) == CHANNEL_ENABLED) &&
//				     test_msg))
//				{
//					logMsg("SEND OB T/O %x\n", status);
//					*retry = TRUE;
//				}
//				else /* channel is down, throw away the mesage */
//				{
//					status = OK;
//					*retry = FALSE;
//				}
//				break;
//			}
//		}
//		else /* Send DATA OB status OK */
//		{
//			/* Output message sent */
//			SMesg_Count[port]++;
//		} /* end else */
//		break;
//	} /* end rtr/nrtr switch */
//
//	if (Free_NTDS_Msg_Buffer( part_id, (char *)ei_packet.address ) != NULL)
//	{
//		logMsg("Error returning buffer to pool 0x%x\n",
//			errnoGet());
//	}
//	return(status);
//} /* end sps_output_ei_proc */

/* #########################################################################
 *
 *      SYNOPSIS:       sps_recv_test_task
 *
 *      DESCRIPTION:    This is the input Test message process for the SPS
 *                      interface. Test messages are 
 *                      received and validated in this process. 
 *                      Test massage protocol requirements are maintained
 *                      here. 
 *						Test messages are expected periodically after 
 *						interface is enabled.  Periodic used is 4 seconds
 *						this could change.
 *
 *      PARAMETERS:
 *              INPUT   device:   int
 *
 *
 *
 * #########################################################################*/

//#define	EIGHT_SECONDS	(sysClkRateGet() * 8)
//
//static int Dummy_Load = 0;

//static int sps_recv_test_task (int device, int port)
//{
//	NTDS_INPUT_MSGS in_block;
//	NTDS_OUTPUT_MSGS out_block;
//	WRAP_AROUND_RESP_MSG *msg_format;
//	WRAP_AROUND_TEST_MSG *header;
//	PART_ID buffer_id;
//	unsigned int msg_size;
//	int status;
//	CLOCK lastTime;
//
//	/* define messages to be received here */
//	static unsigned int mt_list[] =
//	{ 
//		WRAP_TEST_BUF,
//		0
//	};
//
//	in_block.partition_id = NULL;
//	in_block.free_buffer = KEEP_MESG_BUFFER;
//
//	/* Create input queue that uses memory partitions */
///*	status = Create_NTDS_Input_Q(device, 5, MAX_NUM_MESGS,   */
//	status = Create_NTDS_Input_Q(device, 20, MAX_NUM_MESGS,  
//	    mt_list, &TM_Que_Index[port]);
//
//	/* create memory partition big enough for 4 output messages */
//	if((buffer_id = Get_NTDS_Partition( WRAP_AROUND_RESP_MSG_SZ, 4)) == NULL)
//	{
//		logMsg("Get_NTDS_Partition error\n");
//		return( ERROR );
//	}
//
//	out_block.partition_id = buffer_id;
//	out_block.status = (unsigned int *)NULL;
//	out_block.io_pkt.time_out = IO_TIMEOUT;
//	out_block.confirm = NO_CONFIRM_OUTPUT;
//	out_block.free_buffer = FREE_MESG_BUFFER;
//	msg_size = WRAP_AROUND_RESP_MSG_SZ;
//	out_block.io_pkt.req_size = msg_size/4; /* 32bit words */
//	out_block.io_pkt.retry_count = RETRY_COUNT;
//	out_block.io_pkt.delay_time = 0;
//
//	while (TRUE)
//	{
//		/* Wait up to 8 secs for an test message */
//		status = Recv_NTDS_Mesg(device, TM_Que_Index[port], &in_block, 
//								EIGHT_SECONDS);
//
///* logMsg("Just received NTDS message from CEP:0x%x.\n", status); */
//
//		/* if channel is disabled - just free the buffer */
//		if ( Get_Port_Status (port) < CHANNEL_ENABLED )
//		{
//			if ( status == OK )
//			{
///* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
//				/* free the buffer just received */
//				if (in_block.free_buffer != FREE_MESG_BUFFER)
//					Free_NTDS_Msg_Buffer(in_block.partition_id,
//						(char *)in_block.io_pkt.address);
//			}
//			else
//			{
//				/* reset so Recv_NTDS won't free buffer */
//				in_block.partition_id = NULL;
//				in_block.free_buffer = KEEP_MESG_BUFFER;
//			}
//
//			/* taskDelay(1); 12/17/92 */
//			continue;
//		}
//
//		/* if interface enabled or up process message */
//		if (status == OK)
//		{
//			RTest_Count[port]++;
//			header = (WRAP_AROUND_TEST_MSG *)in_block.io_pkt.address;
//			RecvWrapTestMesg(header);
//
//			/* validate test message */
//			if ( (header->btp1 != TWA) || (header->btp2 != TWB) )
//			{
//				status = sps_failed_comm_proc(device, port, 0);
//
//				printf( 
//					"SPS: bad testword received a:0x%x b:0x%x",
//						header->btp1, header->btp2);
//
//				/* free the buffer just received */
//				if (in_block.free_buffer != FREE_MESG_BUFFER)
//					Free_NTDS_Msg_Buffer(in_block.partition_id,
//						(char *)in_block.io_pkt.address);
//
//				continue;
//			}
//
//			/* allocate buffer for test response message */
//			if((msg_format =
//			    (WRAP_AROUND_RESP_MSG *)
//				memPartAlloc(buffer_id, msg_size)) == NULL)
//			{
//				logMsg("memPartAlloc error\n");
//				continue;
//			}
//
//			/* first fill-in test response structure */
//			msg_format->mhdr.nw = 4;
//			msg_format->mhdr.mt = WRAP_RESP_BUF;
//			msg_format->ur = 0;
//			if ( ChanClear[port] )
//			{
//				msg_format->s8 = 1;
//				msg_format->s7 = 1;
//				ChanClear[port] = 0;
//			}
//			else
//			{
//				msg_format->s8 = 0;
//				msg_format->s7 = 0;
//			}
//			msg_format->s6 = 0;
//			msg_format->s5 = 0;
//			msg_format->s4 = 0;
//			msg_format->s3 = 0;
//			msg_format->s2 = 0;
//			msg_format->vbn = WRAP_TEST_BUF;
//			msg_format->s1 = 0;
//			msg_format->spare1 = 0;
//			msg_format->spare2 = 0;
//			msg_format->ctr = header->ctr;
//			lastTime = WrapRdTime[port];
//			msg_format->tdelta = Rtc_GetWaspSimTime() - lastTime;
//			msg_format->btp1 = TWA;
//			msg_format->btp2 = TWB;
//			msg_format->tpr1 = header->btp1;
//			msg_format->tpr2 = header->btp2;
//			msg_format->spare3 = 0;
//			msg_format->fxtcf = 0;
//			msg_format->mtcf = 0;
//			msg_format->duml = Dummy_Load;
//			msg_format->cs = 0;
//			msg_format->stao = 0;
//			msg_format->he = 0;
//			msg_format->spare4 = 0;
//
//			/* save time and ctr for unsolicited test responses */
//			setWrapReference(port, lastTime, header->ctr);
//
///*logMsg("send test delta=%d ms ctr %d\n",
//	msg_format->tdelta, msg_format->ctr);*/
//
//			out_block.io_pkt.address = (unsigned int *)msg_format;
//
//			/* free the buffer just received */
//			if (in_block.free_buffer != FREE_MESG_BUFFER)
//				Free_NTDS_Msg_Buffer(in_block.partition_id,
//					(char *)in_block.io_pkt.address);
//
//
//
///* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
///* logMsg("Just prior to sending NTDS message to CEP.\n"); */
//
//			status = Send_NTDS_Mesg(device, &out_block, MSG_PRI_NORMAL);
//
//			if (status != OK)
//			{
//				logMsg("Send_NTDS_Mesg error %x\n", status);
//				continue;
//			}
//			else
//			{
//				STest_Count[port]++;
//				SendWrapRespMesg(msg_format);
//				if (Get_Port_Status(port) != CHANNEL_READY)
//					Report_Port_Status(port, CHANNEL_READY);
//			}
//		}
//		else
//		{
//			/* Don't return last buffer on input transfer error */
//			if ( (status == S_objLib_OBJ_TIMEOUT ) &&
//				(Get_Port_Status(port) > CHANNEL_DISABLED))
//			{
//				status = sps_failed_comm_proc(device, port, 0);
//				if (status != OK)
//					logMsg("sps_failed_comm_proc TMTO\n");
//				Report_Port_Status(port, CHANNEL_DISABLED);
//			}
//		} /* end else */
//	} /* end while */
//}

/* #########################################################################
 *
 *      SYNOPSIS:       sps_input_task
 *
 *      DESCRIPTION:    This is the input process for the NTDS interface that
 *                      routes all input messages to the proper user.  Waits
 *						for RD EF sends RTR puts buffer on queue for
 *						retrieval by application.
 *
 *      PARAMETERS:
 *              INPUT   device: int
 *                      port:   int
 *
 *
 *
 * #########################################################################*/

//static int sps_input_task (int device, int port)
//{
//
//	SPS49_EF_TYPE	*ei_word;
//	SPS49_EF_TYPE	*ef_word;
//	SPS49_MSG_HDR	*shdr;
//	unsigned int	*segment;
//	unsigned int	seg_size;
//	int status;
//	NIO_MESG in_packet;
//	NIO_MESG ei_packet;
//	NIO_MESG ef_packet;
//	NIO_MESG rcv_block;
//	PART_ID part_id;

	/* this is needed to catch out-of-order EFs */
	//unsigned int	*input_ei_lock_address[3];
	//static unsigned int input_ei_list[] =
	//{
	//	RD,
	//	EI_LIST_END
	//};

	///* Initialize ei_lock_addresses */
	//input_ei_lock_address[0] = NULL;
	//input_ei_lock_address[1] = NULL;
	//input_ei_lock_address[2] = NULL;

	/* Register for input task EI's */
	//status = Create_EI_Q (port, SPS49_EI_MASK, input_ei_list,
	//		&Que_List[port][INPUT_Q]);

	//if (status != OK)
	//{
	//	logMsg("CREATE EI Q FAILURE. 0x%x\n", status);
	//	return( ERROR );
	//}

	//seg_size = (Max_Rcv_Size[port]+20)*4;

	//if((segment = (unsigned int *) Get_NTDS_Buffer(seg_size, &part_id)) == NULL)
	//{
	//	logMsg("ALLOC SEG ERR %x\n", errnoGet());
	//	return( ERROR );
	//}

	//ei_packet.address = (unsigned int *) Get_NTDS_Buffer( WORD_32, &part_id );
	//ei_packet.req_size = 1;
	//ei_packet.delay_time = 0;
	//ei_packet.time_out = WAIT_FOREVER;
	//ei_packet.retry_count = RETRY_COUNT;

	//ef_packet.address = (unsigned int *) Get_NTDS_Buffer( WORD_32, &part_id );
	//ef_packet.req_size = 1;
	//ef_packet.delay_time = 0;
	//ef_packet.time_out = IO_TIMEOUT;
	//ef_packet.retry_count = RETRY_COUNT;

	/* in_packet.req_size = Max_Rcv_Size[port] + 20; */
	//in_packet.delay_time = 0;
	//in_packet.time_out = IN_TIMEOUT;
	//in_packet.retry_count = RETRY_COUNT;

	//rcv_block.delay_time = 0;
	//rcv_block.time_out = IN_TIMEOUT;
	//rcv_block.retry_count = RETRY_COUNT;

	/* initialize input ei lock */
	//Change_EI_Lock(port, &input_ei_list[0], &input_ei_lock_address[0], LOCK);
	//Change_EI_Lock(port, &input_ei_list[0], &input_ei_lock_address[0], UNLOCK);

	//while (TRUE)
	//{
		//status = Deque_EI(port, &ei_packet, Que_List[port][INPUT_Q]);
		//if (status != OK)
		//{
		//	logMsg("DEQUE RD EI ERR %x\n", status);
		//	continue;
		//}

		///* lock input_ei_list so if any come in they are sent elsewhere */
		//Change_EI_Lock(port, &input_ei_list[0], &input_ei_lock_address[0],
		//	LOCK);

		//ei_word = (SPS49_EF_TYPE *) ei_packet.address;

		//RRD_Count[port] += 1;

		///* if RD for WRAP TEST save time */
		//if (Word_Width[port] == WORD_16)
		//{
		//	if ( ei_word->w16.bufno == WRAP_TEST_BUF)
		//		WrapRdTime[port] = Rtc_GetWaspSimTime();
		//}
		//else /* 32 bit case */
		//{
		//	if ( ei_word->w32.bufno == WRAP_TEST_BUF)
		//		WrapRdTime[port] = Rtc_GetWaspSimTime();
		//}

		//status = Flush_EI_Que(port, Que_List[port][INPUT_Q]);
		//if (status != OK)
		//{
		//	logMsg("Flush EI Que ERROR %x\n", status);
		///*	break; */
		//}
		//ef_word = (SPS49_EF_TYPE *) ef_packet.address;
		//*ef_word = *ei_word;

		//if (Word_Width[port] == WORD_16)
		//	ef_word->w16.efcode = RTR;
		//else
		//	ef_word->w32.efcode = RTR;

		///* check that specified NW is valid */

		//if (Word_Width[port] == WORD_16)
		//{
		//	if ( (ef_word->w16.nw < 1) || ( ef_word->w16.nw > MAX_SPS_WRDS) )
		//	{
		//		sps_failed_comm_proc(device, port, BADEI);
		//		logMsg("RD EF bad NW %d\n", ef_word->w16.nw);

		//		/* unlock input_ei_list */
		//		Change_EI_Lock(port, &input_ei_list[0],
		//			&input_ei_lock_address[0],
		//				UNLOCK);

		//		continue;
		//	}
		//}
		//else /* 32 bit case */
		//{
		//	if ( (ef_word->w32.nw < 1) || ( ef_word->w32.nw > MAX_SPS_WRDS) )
		//	{
		//		sps_failed_comm_proc(device, port, BADEI);
		//		logMsg("RD EF bad NW %d\n", ef_word->w32.nw);

		//		/* unlock input_ei_list */
		//		Change_EI_Lock(port, &input_ei_list[0],
		//			&input_ei_lock_address[0],
		//				UNLOCK);

		//		continue;
		//	}
		//}


		//status = Send_EF (port, &ef_packet, NORMAL_EF);


		///* unlock input_ei_list (RD EFs) */
		//Change_EI_Lock(port, &input_ei_list[0], &input_ei_lock_address[0],
		//	UNLOCK);

		//if (status == OK)
		//{
		//	SRTR_Count[port]++;
			//in_packet.address = (unsigned int *)segment + 1;

			//if (Word_Width[port] == WORD_16)
			//{
			//	in_packet.req_size = ef_word->w16.nw;
			//	/* If we are using a 16 bit interface double
			//	the request size so the NIO board will
			//	transfer everything. */

			//	in_packet.req_size *= WORD_16;
			//}
			//else
			//	in_packet.req_size = ef_word->w32.nw;


			///* Get IB status - test for NIO_TERM */
			//status = Get_IB(port, &in_packet, NULL, NULL);
			//if ( status == OK )
			//{
			//	/* fill-in dummy header */
			//	shdr = (SPS49_MSG_HDR *)segment;

			//	if (Word_Width[port] == WORD_16)
			//	{
			//		shdr->nw = in_packet.tfr_size/WORD_16; /* Represent # of 32 bit words */
			//		if ( ef_word->w16.bufno == 0 )
			//			shdr->mt = 10;
			//		else
			//			shdr->mt = ef_word->w16.bufno;
			//	}
			//	else /* 32 bit case */
			//	{
			//		shdr->nw = in_packet.tfr_size;
			//		if ( ef_word->w32.bufno == 0 )
			//			shdr->mt = 10;
			//		else
			//			shdr->mt = ef_word->w32.bufno;
			//	}

			//	/* got message - dispatch it */
			//	rcv_block.address = (unsigned int *)segment;

			//	if (Word_Width[port] == WORD_16)
			//		rcv_block.tfr_size = in_packet.tfr_size+2;
			//	else
			//		rcv_block.tfr_size = in_packet.tfr_size+1;

			//	rcv_block.req_size = in_packet.tfr_size+1;
			//	rcv_block.buf_time = in_packet.buf_time;
			//	RMesg_Count[port] += 1;

			//	status = Queue_Input_Mesg(port, &rcv_block,
			//		shdr->mt, FREE_MESG_BUFFER);

			///*	parse_sps_input (int port, LOCAL_INPUT, *rcv_packet); */
			//}
		//	else
		//	{
		//		if( status == NIO_TIMEOUT )
		//		{
		//			/* SLAVE - Request Interface Test */
		//			sps_failed_comm_proc(device, port, IBTO);
		//			IB_TO_Count[port]++;
		//		}
		//	}
		//}
		//else


		//	logMsg("SEND EF RTR ERR %x\n", status);




//	} /* end while TRUE */
//} /* end of sps_input task */

/* #########################################################################
 *
 *      SYNOPSIS:       sps_error_task
 *
 *      DESCRIPTION:    This task processes any illegal/unexpected EIs
 *                      received on the NTDS channel.  All legitimate
 *						messages should be handled by other routines.
 *
 *      PARAMETERS:
 *              INPUT   device:   int
 *                      port: int
 *
 *
 * #########################################################################*/
//static int sps_error_task (int device, int port)
//{
//	int status;
//	SPS49_EF_TYPE *ei_word;
//	NIO_MESG ei_packet;
//	PART_ID part_id;
//	static unsigned int ei_list[] = {
//		-1,
//		EI_LIST_END	};
//
//	/* Register for error task EI's */
//	status = Create_EI_Q (port, SPS49_EI_MASK, ei_list,
//			&Que_List[port][ERROR_Q]);
//	if (status != OK)
//	{
//		logMsg("CREATE EI Q FAILURE. 0x%x\n", status);
//		return( ERROR );
//	}
//
//	ei_packet.address = (unsigned int *)Get_NTDS_Buffer( WORD_32, &part_id );
//	ei_packet.req_size = 1;
//	ei_packet.delay_time = 0;
//	ei_packet.time_out = WAIT_FOREVER;
//	ei_packet.retry_count = RETRY_COUNT;
//	while (TRUE)
//	{
//		status = Deque_EI(port, &ei_packet, Que_List[port][ERROR_Q]);
//		if (status != OK)
//			logMsg("Deque EI ERROR %x\n", status);
//		else
//		{
//			ei_word =  (SPS49_EF_TYPE *) ei_packet.address;
//
//			if (Word_Width[port] == WORD_16)
//			{
//				if ( (ei_word->w16.efcode == RD) || (ei_word->w16.efcode == RTR) )
//				{
//					logMsg("UNEXPECTED EI RVCD %d (bn=%d, nw=%d)\n",
//							ei_word->w16.efcode, ei_word->w16.bufno, ei_word->w16.nw);
//					status = sps_failed_comm_proc(device, port, EFSEQ);
//				}
//				else
//				{
//					logMsg("INVALID EI RVCD %d\n", ei_word->w16.efcode);
//					status = sps_failed_comm_proc(device, port, BADEI);
//				}
//			}
//			else /* 32 bit case */
//			{
//				if ( (ei_word->w32.efcode == RD) || (ei_word->w32.efcode == RTR) )
//				{
//					logMsg("UNEXPECTED EI RVCD %d (bn=%d, nw=%d)\n",
//							ei_word->w32.efcode, ei_word->w32.bufno, ei_word->w32.nw);
//					status = sps_failed_comm_proc(device, port, EFSEQ);
//				}
//				else
//				{
//					logMsg("INVALID EI RVCD %d\n", ei_word->w32.efcode);
//					status = sps_failed_comm_proc(device, port, BADEI);
//				}
//			}
//		}
//	}
//}

/* #########################################################################
*
*      SYNOPSIS:       parse_sps_input
*
*      DESCRIPTION:    This function parses an input buffer and distributes
*                      the messages to the application as per requested MTs.
*
*      PARAMETERS:
*               INPUT   port:   The I/O port that read the data.
*
*                    data_src : The source of the data buffer.  This can be
*                               either LOCAL_INPUT or REMOTE_INPUT.  If it is
*                               local data, the buffer was provided by the
*                               input task in this file.  If it is remote
*                               data, it is provided by an external input
*                               typically the ethernet package.
*
*                   data_block : A pointer to the NIO_MESG data descriptor
*                                that contains among other things the buffer
*                                address and length
*
*               OUTPUT :   Messages are routed to the application.
*
*		RETURNS :  Nothing
*
* #########################################################################*/

//static void parse_sps_input (int port, int data_src, NIO_MESG *in_packet)
//{
//	NIO_MESG	save_packet;
//	SPS49_MSG_HDR 	*shdr;
//	int		status;
//
//	save_packet = *in_packet;
//
//	/* fill-in dummy header */
//	shdr = (SPS49_MSG_HDR *)in_packet->address;
//	shdr->nw = in_packet->tfr_size;
//
///*	if ( ef_word->w32.bufno == 0 )
//		shdr->mt = 10;
//	else
//		shdr->mt = ef_word->w32.bufno; */
//
//	/* --------------------------------------------- */
//	/* Find out who is registered for this Mesg Type */
//	/* --------------------------------------------- */
//
//	status = Queue_Input_Mesg (port, &save_packet, shdr->mt, FREE_MESG_BUFFER);
//	if (status != OK)
//	{
//		/* ----------------------------------- */
//		/* Message registration error send     */
//		/* ERR_STAT and release message buffer */
//		/* ----------------------------------- */
//
//		if (status == COULD_NOT_QUE_MESG)
//		{
//			/* Index to the next buffer */
//			printf ( 
//				"SPS:parse_sps_input-%d Message Queue Full 0x%x 0x%x\n", 
//				port, shdr->mt, status);
//		}
//		else
//		{
//			printf ( 
//				"SPS:parse_sps_input-%d Bad mesg type 0x%x 0x%x\n",
//				port, shdr->mt, status);
//		}
//	} /* end if */
//} /* end of static void parse_sps_input */
//
/* #########################################################################
 *
 *      SYNOPSIS:       Init_SPS_Comm
 *
 *      DESCRIPTION:    This function performs module initialization and
 *                      creates queues and tasks requied for protocol
 *                      processing.
 *
 *      PARAMETERS:
 *              INPUT:  device:   int
 *
 *      RETURNS:        status
 *
 * #########################################################################*/
//int Init_SPS_Comm (int device)
//{
//	//int i;
//	int status = OK;
//	int port;
//	NTDS_CONFIG  dev_config;
//
//	status = Get_Device_Configuration(device, &dev_config);
//	if (status != OK)
//		return(status);
//	port = dev_config.port;
//
//	///* Drain any stale EI words still hanging out */
//	//for (i = 0; i >= MAX_EIS; i++)
//	//{
//	//	status = Flush_EI_Que(port, Que_List[port][i]);
//	//	if (status != OK)
//	//		return(status);
//	//}
//	//status = Enable_EI_Process(port);
//	//if (status != OK)
//	//	return(status);
//
//	Report_Port_Status(port, CHANNEL_DISABLED);
//
//	return (status);
//}

/* #########################################################################
 *
 *      SYNOPSIS:       sps_failed_comm_proc
 *
 *      DESCRIPTION:    This function should be called when communications
 *                      fail or when Channel Clear EF received.
 *
 *      PARAMETERS:
 *              INPUT:  device:   int
 *
 *      RETURNS:        status
 *
 * #########################################################################*/

//static	PART_ID UTbuffer_id;
//static	BOOL firstUT = 1;
//
//static int sps_failed_comm_proc (int device, int port, int err)
//{
//	NTDS_OUTPUT_MSGS out_block;
//	WRAP_AROUND_RESP_MSG *msg_format;
//	unsigned int msg_size;
//	int status = OK;
//	int i;
//	int lastCtr;
//	CLOCK lastTime;
//
//	/* Check to see if we are already trying to restore communications */
//	/* tell them everything is OK if someone else is handling it */
//	if(semTake(Recovery_Sem[port], NO_WAIT) != OK)
//		return( OK );
//
//	/* Drain any stale EI words still hanging out */
//	for (i = 0; i >= MAX_EIS; i++)
//	{
//		status = Flush_EI_Que(port, Que_List[port][i]);
//		if (status != OK)
//			return(status);
//	}
//	/* Terminate and restart all the Chains */
//	NTDS_Debug( port, err, 0, 0x100 );
//	status = Terminate_Chain(port, TIB);
//	if (status != OK)
//		return (status);
//	status = Terminate_Chain(port, TFB);
//	if (status != OK)
//		return (status);
//	status = Terminate_Chain(port, TOB);
//	if (status != OK)
//		return (status);
//
//	/* send unsolicited wrap_test_response message */
//	/* create memory partition big enough for 4 output messages */
//	if ( firstUT )
//	{
//		if((UTbuffer_id =
//			Get_NTDS_Partition( WRAP_AROUND_RESP_MSG_SZ, 4)) == NULL)
//		{
//			logMsg("Get_NTDS_Partition error\n");
//			return( ERROR );
//		}
//		firstUT = 0;
//	}
//
//	/* only send test resp for "known" error */
//	if ( err == 0 )
//	{
//		if(semGive(Recovery_Sem[port]) != OK)
//			logMsg("Recovery semGive err\n");
//		return( OK );
//	}
//
//	out_block.partition_id = UTbuffer_id;
//	out_block.status = (unsigned int *)NULL;
//	out_block.io_pkt.time_out = IO_TIMEOUT;
//	out_block.confirm = NO_CONFIRM_OUTPUT;
//	out_block.free_buffer = FREE_MESG_BUFFER;
//	msg_size = WRAP_AROUND_RESP_MSG_SZ;
//	out_block.io_pkt.req_size = msg_size/4; /* 32bit words */
//	out_block.io_pkt.retry_count = RETRY_COUNT;
//	out_block.io_pkt.delay_time = 0;
//
//	/* allocate buffer for test response message */
//	if((msg_format = (WRAP_AROUND_RESP_MSG *)
//		memPartAlloc(UTbuffer_id, msg_size)) == NULL)
//	{
//		logMsg("memPartAlloc error\n");
//	}
//	else
//	{
//		/* first fill-in test response structure */
//		msg_format->mhdr.nw = 4;
//		msg_format->mhdr.mt = WRAP_RESP_BUF;
//		msg_format->ur = 1;
//		/* set appropriate error code(s) */
//		if ( err == OBTO )
//			msg_format->s8 = 1;
//		else
//			msg_format->s8 = 0;
//		if ( err == IBTO )
//			msg_format->s7 = 1;
//		else
//			msg_format->s7 = 0;
//		msg_format->s6 = 0;
//		msg_format->s5 = 0;
//		if ( err == BUFLEN )
//			msg_format->s4 = 1;
//		else
//			msg_format->s4 = 0;
//		if ( err == EFSEQ )
//			msg_format->s3 = 1;
//		else
//			msg_format->s3 = 0;
//		if ( err == BADEI )
//			msg_format->s2 = 1;
//		else
//			msg_format->s2 = 0;
//		msg_format->vbn = WRAP_TEST_BUF;
//		msg_format->s1 = 0;
//		msg_format->spare1 = 0;
//		msg_format->spare2 = 0;
//		getWrapReference(port, &lastTime, &lastCtr);
//		msg_format->ctr = lastCtr;
//		msg_format->tdelta = Rtc_GetWaspSimTime() - lastTime;
//		msg_format->btp1 = TWA;
//		msg_format->btp2 = TWB;
//		msg_format->tpr1 = TWA;
//		msg_format->tpr2 = TWB;
//		msg_format->spare3 = 0;
//		msg_format->fxtcf = 0;
//		msg_format->mtcf = 0;
//		msg_format->duml = Dummy_Load;
//		msg_format->cs = 0;
//		msg_format->stao = 0;
//		msg_format->he = 0;
//		msg_format->spare4 = 0;
//
//		out_block.io_pkt.address = (unsigned int *)msg_format;
//
//logMsg("send Utest delta=%d ms ctr %d err=%d\n", 
//	msg_format->tdelta, msg_format->ctr, err);
//
//		status = Send_NTDS_Mesg(device, &out_block, MSG_PRI_NORMAL);
//
//		if (status != OK)
//			logMsg("Send_NTDS_Mesg error %x\n", status);
//
//		else
//		{
//			STest_Count[port]++;
//			SendWrapRespMesg(msg_format);
//		}
//
//	}
//
//	if(semGive(Recovery_Sem[port]) != OK)
//		logMsg("Recovery semGive err\n");
//	return (status);
//}

/* #########################################################################
 *
 *      SYNOPSIS:       sps_status_task
 *
 *      DESCRIPTION:    This task processes enable/disable comm EIs.
 *
 *      PARAMETERS:
 *              INPUT   port:   int
 *
 *
 * #########################################################################*/
//static int sps_status_task (int device, int port)
//{
//	NIO_MESG ei_packet;
//	SPS49_EF_TYPE *received_ei;
//	SPS49_EF_TYPE *sending_ef;
//	PART_ID part_id;
//	int	 status;
//	int	 ei_code;
//
//	/* list of EI's expected by SLAVE */
//	static unsigned int ei_list[] = { 
//		EC,	/* Enable  Communications */
//		DC,	/* Disable Communications */
//		CLR,	/* Channel Clear	  */
//		EI_LIST_END 	};
//
//	/* Register for error task EI's */
//	status = Create_EI_Q (port, SPS49_EI_MASK, ei_list,
//			&Que_List[port][CHANNEL_Q]);
//	if (status != OK)
//	{
//		logMsg("CREATE EI Q FAILURE. 0x%x\n", status);
//		return( ERROR );
//	}
//
//	ei_packet.address = (unsigned int *)Get_NTDS_Buffer( WORD_32, &part_id );
//	ei_packet.req_size = 1;
//	ei_packet.delay_time = 0;
//	ei_packet.time_out = WAIT_FOREVER;
//	ei_packet.retry_count = RETRY_COUNT;
//
//	comm_ef_packet.address = (unsigned int *)Get_NTDS_Buffer( WORD_32, &part_id );
//	comm_ef_packet.req_size = 1;
//	comm_ef_packet.delay_time = 0;
//	comm_ef_packet.time_out = IO_TIMEOUT;
//	comm_ef_packet.retry_count = RETRY_COUNT;
///*	*comm_ef_packet.address = (IntfType[port]) ? MPU_ECA : ECA; */
//
//	sending_ef = (SPS49_EF_TYPE *)comm_ef_packet.address;
//	if (Word_Width[port] == WORD_16)
//	{
//		sending_ef->w16.efcode = (IntfType[port]) ? MPU_ECA : ECA;
//		sending_ef->w16.nw = 0;
//		sending_ef->w16.bufno = 0;
//		sending_ef->w16.unused = 0;
//	}
//	else
//	{
//		sending_ef->w32.efcode = (IntfType[port]) ? MPU_ECA : ECA;
//		sending_ef->w32.nw = 0;
//		sending_ef->w32.bufno = 0;
//		sending_ef->w32.unused = 0;
//	}
//
///*	printf("TYPE %d  ECA %d\n", IntfType[port], *comm_ef_packet.address); */
//
//	while (TRUE)
//	{
//		status = Deque_EI(port, &ei_packet, Que_List[port][CHANNEL_Q]);
//		if (status != OK)
//			logMsg("Deque EI ERROR %x\n", status);
//		else
//		{
//		/*	switch (*ei_packet.address) */
//			received_ei = (SPS49_EF_TYPE *)ei_packet.address;
//			if (Word_Width[port] == WORD_16)
//				ei_code = received_ei->w16.efcode;
//			else
//				ei_code = received_ei->w32.efcode;
//
//			switch (ei_code)
//			{
//			case DC:	/* Disable Communications */
//logMsg("Received DC EF.\n");
//				RDC_Count[port]++;
//				if (Get_Port_Status(port) != CHANNEL_DISABLED)
//				{
//					Report_Port_Status(port, CHANNEL_DISABLED);
//					logMsg("Received DC - port %d\n", port);
//				}
//				else
//				{
//					/* already disabled - just ignore? */
//					logMsg("Received DC EF- when status was DISABLED\n");
//				}
//				break;
//
//			case EC:	/* Enable Communications */
//logMsg("Recv EC- port %d, status %d\n", port, status);
//				REC_Count[port]++;
//				if (Get_Port_Status(port) < CHANNEL_ENABLED)
//				{
//					SECA_Count[port]++;
//					status = Send_EF(port, &comm_ef_packet, NORMAL_EF);
//
//					logMsg("Recv EC- port %d, status %d\n", port, status);
//
//					if (status == NIO_TIMEOUT)
//					{
//						logMsg("Send ECA timed-out\n");
//						break;
//					}
//
//					Report_Port_Status(port, CHANNEL_ENABLED);
//				}
//				else
//				{
//					Report_Port_Status(port, CHANNEL_DISABLED);
//
//					SECA_Count[port]++;
//					status = Send_EF(port, &comm_ef_packet, NORMAL_EF);
//
//					logMsg("Recv EC- port %d, status %d\n", port, status);
//
//					if (status == NIO_TIMEOUT)
//					{
//						logMsg("Send ECA timed-out\n");
//						break;
//					}
//
//					Report_Port_Status(port, CHANNEL_ENABLED);
//				}
//				break;
//			case CLR:	/* Channel Clear */
//				RCLR_Count[port]++;
//logMsg("Received CLR - port %d\n", port);
//				ChanClear[port] = 1;
//				if (Get_Port_Status(port) != CHANNEL_DISABLED)
//				{
//					logMsg("Received CLR - port %d\n", port);
//
					/* will go back to READY after Wrap Received */
					//Report_Port_Status(port, CHANNEL_ENABLED);

	//				sps_failed_comm_proc(device, port, 0);

	//				/* send Communications Acknowledge EF */
	//				SECA_Count[port]++;
	//				status = Send_EF(port, &comm_ef_packet, NORMAL_EF);
	//			}
	//			break;
	//		default:
	//			logMsg("Received undefined EI - port %d\n", port);
	//			break;
	//		} /* end switch */
	//	}
	//} /* end while */
//} /* end sps_status task */
//
/* #########################################################################
 *
 *      SYNOPSIS:       SPS Display
 *
 *      DESCRIPTION:    This function displays the sps proto transfer 
 *                      counts.
 *
 *      PARAMETERS:
 *              INPUT:  none
 *
 *      RETURNS:        none
 *
 * #########################################################################*/
//static void sps_display()
//{
//	int port;
//	char clear[5];
//	char exit[3];
//
//	printf("Show SPS Protocol Transfer Counts\n\n");
//	port = -1;
//	printf("Enter Port Assignment from 0 to %d..",NUM_OF_NTDS_PORTS-1);
//	scanf("%d",&port);
//	if (port > NUM_OF_NTDS_PORTS)
//	{
//		printf("Invalid Port Assignment");
//		return;
//	}
//
//	exit[0] = 'O';
//	while ((exit[0] != 'X') && (exit[0] != 'x'))  {
//		if (Get_Port_Status(port) == CHANNEL_READY)
//		{
//			printf("Channel Status Port %d READY\n",port);
//		}
//		else if (Get_Port_Status(port) == CHANNEL_ENABLED)
//		{
//			printf("Channel Status Port %d ENABLED\n",port);
//		}
//		else
//		{
//			printf("Channel Status Port %d DOWN\n",port);
//		}
//		printf("             Sent Counts        Received Counts \n");
//		printf("Messages:     %8d              ", SMesg_Count[port]);
//		printf("%8d\n", RMesg_Count[port]);
//		printf("Dequed Mesgs: %8d\n", DqMesg_Count[port]);
//		printf("RD:           %8d              ", SRD_Count[port]);
//		printf("%8d\n",RRD_Count[port]);
//		printf("RTR:          %8d              ", SRTR_Count[port]);
//		printf("%8d\n", RRTR_Count[port]);
//		printf("EC:                                 ");
//		printf("%8d\n", REC_Count[port]);
//		printf("ECA:          %8d\n", SECA_Count[port]);
//		printf("DC:                                 ");
//		printf("%8d\n", RDC_Count[port]);
//		printf("CLR:                                ");
//		printf("%8d\n", RCLR_Count[port]);
//		printf("TEST:         %8d              ", STest_Count[port]);
//		printf("%8d\n", RTest_Count[port]);
//		printf("Timeouts:     %8d              ", OB_TO_Count[port]);
//		printf("%8d\n", IB_TO_Count[port]);
//
//		printf("To Exit Protocol Display Enter: X...");
//		scanf("%1s",exit);
//		Clr_Screen();
//	} /*end while*/
//	clear[0] = 'N';
//	printf("To Clear All Protocol Counts, Enter Y(es)...");
//	scanf("%1s",clear);
//	if (clear[0] == 'Y')
//		clearXferCounts(port);
//}

/* #########################################################################
 *
 *      SYNOPSIS:       clearXferCounts
 *
 *      DESCRIPTION:    This function clears the sps proto transfer 
 *                      counts.
 *
 *      PARAMETERS:
 *              INPUT:  port
 *
 *      RETURNS:        none
 *
 * #########################################################################*/
//void clearXferCounts(int port)
//{
//	/* Initialize Message status counts */
//	DqMesg_Count[port] = 0;
//	SMesg_Count[port] = 0;
//	RMesg_Count[port] = 0;
//	REC_Count[port] = 0;
//	RDC_Count[port] = 0;
//	SECA_Count[port] = 0;
//	RRD_Count[port] = 0;
//	SRD_Count[port] = 0;
//	RRTR_Count[port] = 0;
//	SRTR_Count[port] = 0;
//	RCLR_Count[port] = 0;
//	STest_Count[port] = 0;
//	RTest_Count[port] = 0;
//	OB_TO_Count[port] = 0;
//	IB_TO_Count[port] = 0;
//}

/* #########################################################################
 *
 *      SYNOPSIS:       numRcvdEc
 *
 *      DESCRIPTION:    This function provides the count of received
 *                      EC EF's
 *
 *      PARAMETERS:
 *              INPUT:  port
 *
 *      RETURNS:        int - number of EC EF's received
 *
 * #########################################################################*/
 
//int  numRcvdEc(int port)
//{
// 
//        return (REC_Count[port]); 
// 
//}

/* #########################################################################
 *
 *      SYNOPSIS:       numRcvdClr
 *
 *      DESCRIPTION:    This function provides the count of received
 *                      CLR EF's
 *
 *      PARAMETERS:
 *              INPUT:  port
 *
 *      RETURNS:        int - number of CLR EF's received
 *
 * #########################################################################*/
 
//int  numRcvdClr(int port)
//{
// 
//        return (RCLR_Count[port]); 
// 
//}

/* #########################################################################
 *
 *      SYNOPSIS:       numRcvdRd
 *
 *      DESCRIPTION:    This function provides the count of received
 *                      RD EF's
 *
 *      PARAMETERS:
 *              INPUT:  port
 *
 *      RETURNS:        int - number of RD EF's received
 *
 * #########################################################################*/
 
//int  numRcvdRd(int port)
//{
// 
//        return (RRD_Count[port]); 
// 
//}

/* #########################################################################
 *
 *      SYNOPSIS:       numRcvdRtr
 *
 *      DESCRIPTION:    This function provides the count of received
 *                      RTR EF's
 *
 *      PARAMETERS:
 *              INPUT:  port
 *
 *      RETURNS:        int - number of RTR EF's received
 *
 * #########################################################################*/
 
//int  numRcvdRtr(int port)
//{
// 
//        return (RRTR_Count[port]); 
// 
//}

/* #########################################################################
 *
 *      SYNOPSIS:       numRcvdDc
 *
 *      DESCRIPTION:    This function provides the count of received
 *                      DC EF's
 *
 *      PARAMETERS:
 *              INPUT:  port
 *
 *      RETURNS:        int - number of DC EF's received
 *
 * #########################################################################*/
 
//int  numRcvdDc(int port)
//{
// 
//        return (RDC_Count[port]); 
// 
//}

/* #########################################################################
 *
 *      SYNOPSIS:       numRcvdWrapTest
 *
 *      DESCRIPTION:    This function provides the count of received
 *                      Wrap Test messages
 *
 *      PARAMETERS:
 *              INPUT:  port
 *
 *      RETURNS:        int - number of Wrap Test messagess received
 *
 * #########################################################################*/
 
//int  numRcvdWrapTest(int port)
//{
// 
//        return (RTest_Count[port]);
// 
//}

/* #########################################################################
 *
 *      SYNOPSIS:       numSentEca
 *
 *      DESCRIPTION:    This function provides the count of sent
 *                      ECA EF's
 *
 *      PARAMETERS:
 *              INPUT:  port
 *
 *      RETURNS:        int - number of ECA EF's sent
 *
 * #########################################################################*/
 
//int  numSentEca(int port)
//{
// 
//        return (SECA_Count[port]); 
// 
//}

/* #########################################################################
 *
 *      SYNOPSIS:       numSentRd
 *
 *      DESCRIPTION:    This function provides the count of sent
 *                      RD EF's
 *
 *      PARAMETERS:
 *              INPUT:  port
 *
 *      RETURNS:        int - number of RD EF's sent
 *
 * #########################################################################*/
 
//int  numSentRd(int port)
//{
// 
//        return (SRD_Count[port]); 
// 
//}

/* #########################################################################
 *
 *      SYNOPSIS:       numSentRtr
 *
 *      DESCRIPTION:    This function provides the count of sent
 *                      RTR EF's
 *
 *      PARAMETERS:
 *              INPUT:  port
 *
 *      RETURNS:        int - number of RTR EF's sent
 *
 * #########################################################################*/
 
//int  numSentRtr(int port)
//{
// 
//        return (SRTR_Count[port]); 
// 
//}

/* #########################################################################
 *
 *      SYNOPSIS:       numSentWrapResp
 *
 *      DESCRIPTION:    This function provides the count of sent
 *                      Wrap Response Messages
 *
 *      PARAMETERS:
 *              INPUT:  port
 *
 *      RETURNS:        int - number of Wrap Response Messages sent
 *
 * #########################################################################*/
 
//int  numSentWrapResp(int port)
//{
// 
//        return (STest_Count[port]); 
// 
//}

/* #########################################################################
 *
 *      SYNOPSIS:       setDumlWrapResp
 *
 *      DESCRIPTION:    This function allows the developer to set the 
 *						dummy load bit of the Wrap Response Messages
 *
 *      PARAMETERS:
 *              INPUT:  0 or 1.
 *
 *      RETURNS:        OK or ERROR.
 *
 * #########################################################################*/

//STATUS setDumlWrapResp(int val)
//{
//
//	STATUS retn = OK;
// 
//	if (val == 0 || val == 1) {
//		Dummy_Load = val;
//		retn = OK;
//	}
//	else {
//		retn = ERROR;
//	}
//
//	return retn;
// 
//}

/* #########################################################################
 *
 *      SYNOPSIS:       getDumlWrapResp
 *
 *      DESCRIPTION:    This function returns the value of the 
 *						dummy load bit of the Wrap Response Message
 *
 *      PARAMETERS:
 *
 *      RETURNS:        Dummy_Load
 *
 * #########################################################################*/

//int getDumlWrapResp(void)
//{
//
//	return Dummy_Load;
// 
//}

/* set time reference and ctr from latest TEST MESG */
//static void setWrapReference(int port, CLOCK wrapTime, int wrapCtr)
//{
//	/* get semaphore */
//	if( semTake(Sps_Wrap_Sem[port], WAIT_FOREVER) == ERROR)
//		printf( "SPS49:IOSemId take error");
//
//	WrapLastTime[port] = wrapTime;
//	WrapLastCtr[port] = wrapCtr;
//
//	/* release semaphore */
//	if (semGive(Sps_Wrap_Sem[port]) == ERROR)
//		printf( "SPS49:semGive IO sem error");
//
//	return;
//}
//
///* get time reference and ctr from latest TEST MESG */
//void getWrapReference(int port, CLOCK *wrapTime, int *wrapCtr)
//{
//	/* get semaphore */
//	if( semTake(Sps_Wrap_Sem[port], WAIT_FOREVER) == ERROR)
//		printf( "SPS49:IOSemId take error");
//
//	*wrapTime = WrapLastTime[port];
//	*wrapCtr = WrapLastCtr[port];
//
//	/* release semaphore */
//	if (semGive(Sps_Wrap_Sem[port]) == ERROR)
//		printf( "SPS49:semGive IO sem error");
//
//	return;
//}

/* ---------- */
/* MODULE END */
/* ---------- */















