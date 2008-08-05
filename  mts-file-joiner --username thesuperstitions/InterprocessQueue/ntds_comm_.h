#ifndef NTDS_COMMON_KWR__H
#define NTDS_COMMON_KWR__H

#include <vxWorks.h>
#include "ntdsTypes.h"
//#include "ntds_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 *                             COPYRIGHT NOTICE
 *
 *Developed by The Johns Hopkins University/Applied Physics Laboratory (JHU/APL)
 * Copyright (c) 1996 The Johns Hopkins University/Applied Physics Laboratory
 *
 * Permission to copy all or part of this work is granted, provided that
 * the copies are made or distributed only for the CEC project
 * and that this copyright notice is reproduced on all such copies.  This
 * material may be reproduced by or for the U.S. Government pursuant to the
 * copyright license und/er the clause at DFARS 252.227-7013 (OCT 1988).
 * For any other permissions please contact the CEC Program Office at JHU/APL.
 *
 *
static char ntds_comm__h[] = "$Header: /cec/generic/delivered/ntds_common/incl/RCS/ntds_comm_.h,v 4.24 2000/03/03 20:01:38 ceplib Exp $";
 ************************************************************************
 * Developed by The Johns Hopkins University/Applied Physics Laboratory
 *
 *      Project:        Common NTDS Interface Package
 *
 *	Module Name:	ntds_comm_.h  ( NTDS communications package )
 *	Synopsis (Usage and Parameters):
 *		See content.
 *
 *
 *	Description:
 *		This include file contains:
 *			a) constant definitions for use with the NTDS
 *			   protocol package.
 *			b) NTDS protocol function specifications.
 *
 *			    The functions contained in this file provide an
 *			interface between the interface protocol tasks and the
 *			application.  The functions that an application calls
 *			to communicate with an NTDS device are noted with
 *			the word application in parenthesis next to the function
 *			name.  The functions that a protocol task calls to
 *			perform input, output, control, and status functions
 *			have the word protocol in parenthesis next to the
 *			function name.
 *
 *
 *	Files:
 *		ntds_comm.c
 *
 *
 *	Programmer:	R. A. Beseke
 *	Organization:	JHU/APL
 *	Host System:	HP/HPUX
 *	Language:	C
 *	Date Created:	9/06/91
 *	Reviewed:		By:
 *	Modifications:
 *
 * $Log: ntds_comm_.h,v $
 * Revision 4.24  2000/03/03 20:01:38  ceplib
 * Modified to incorporate an NTDS buffer-tracking mechanism IAW TR#4468.  adb
 *
 * Revision 4.23  1999/12/15 18:59:03  ceplib
 * Modified to compile under the Green Hills C and C++ compilers, as well as
 * under the GNU C and C++ compilers IAW TR#4387.  adb
 *
 * Revision 4.22  1999/04/13 17:59:32  ceplib
 * Changes were made to implement task-switching capabilities for "NTDS
 * Trace" IAW TR#4275.  adb
 *
 * Revision 4.21  1998/10/27 12:35:18  ceplib
 * Changed function 'Get_NTDS_Device_Name' so that it takes the "port" as the
 * input parameter IAW TR#4063.  adb
 *
 * Revision 4.20  1998/09/23 23:49:29  ceplib
 * Modified to implement N+1 handling capabilities IAW TR #4034.  -gpg
 *
 * Revision 4.19  1998/09/16 18:14:03  ceplib
 * Modified to accomodate N+1 functionality IAW TR#4034.  Implemented new
 * NTDS Statuses for NTDS Board Configuration Failure IAW TR#4001.  adb
 *
 * Revision 4.18  1998/07/02 15:01:41  ceplib
 * Modified to incorporate a queue-synchronization method that doesn't
 * interfere with USG1 operations.  It also provides a more precise
 * synchronization of the redundant-channel output queue swap IAW TR#3942.
 * adb
 *
 * Revision 4.17  1998/05/08 19:09:22  ceplib
 * Changes were made to incorporate full port-swapping capabilities IAW
 * TR#3872.  adb
 *
 * Revision 4.15  1998/02/27 11:25:16  ceplib
 * Modified to define the new "redundant_channel_flag" IAW TR#3594.  adb
 *
 * Revision 4.14  1997/12/04 17:47:38  ceplib
 * Modified to implement the basic redundant-channel functionality IAW
 * TR#3594.  adb
 *
 * Revision 4.13  1997/09/11 15:41:06  ceplib
 * Create a name string that ends on a long word boundary for the PowerPC
 * IAW TR#3504.  adb
 *
 * Revision 4.12  1997/09/10 13:10:19  ceplib
 * Modified the ethernet package to a functionality for application control
 * of Level 2 testing IAW TR#3504.  adb
 *
 * Revision 4.11  1997/04/30 13:08:24  ceplib
 * Modified to support the 4001A interface card IAW TR#3382.  adb
 *
 * Revision 4.10  1997/03/03 17:58:35  ceplib
 * Added code to support CES remote interface communications.  Added function
 * protoype for Recv_Alternate_NTDS_Error, NTDS_Secondary_Control,
 * Get_Alternate_NTDS_Port, Get_NTDS_Word_Size, Get_NTDS_Port,
 * Get_Port_Status_String, and Test_NTDS_Card IAW TR#3279.  adb
 *
 * Revision 4.9  1996/07/23 17:42:32  ceplib
 * Modified to add more user fields in the DEVICE_DATA structure IAW CGA
 * TR#26.  adb
 *
 * Revision 4.8  1996/04/22  16:03:49  ceplib
 * Allow an application to not use the remote interface capability IAW TR#2735.
 * adb
 *
 * Revision 4.5  1996/03/06  16:12:00  ceplib
 * Standardize the function calls Determine_NTDS_Board, Determine_Antares_Board,
 * and Determine_Get_Board IAW TR#2635.  adb
 *
 * Revision 4.4  1996/02/14  12:50:15  ceplib
 * Modified to support the expanded capability of the the NTDS trace package
 * IAW TR#2604.  adb
 *
 * Revision 4.3  1996/01/30  17:41:14  ceplib
 * Modified to support the new NTDS drivers IAW TR#2481.  Modified to support
 * the new remote NTDS capability IAW TR# 2507.  Modified to perform auto
 * board detection during initialization IAW TR#2514.  adb
 *
 * Revision 4.1  1994/09/29  18:53:24  ceplib
 * Modified to support the new INS interface IAW TR#2044.  adb
 *
 * Revision 4.0  1994/07/12  14:33:44  ceplib
 * Initial code for start of CEP_2.1.1.
 *
 * Revision 1.9  1994/04/29  11:14:41  ceplib
 * Modified to add code to support passive tap board IAW TR#1715.  adb
 *
 * Revision 1.8  1993/08/26  14:20:05  ceplib
 * Added Show_NTDS_Config function protoype IAW TR#1002.  adb
 *
 * Revision 1.7  1993/05/05  12:46:48  ceplib
 * odified to validate the port of protocol requests IAW TR#569.  adb
 *
 * Revision 1.6  1993/04/29  14:25:37  ceplib
 * Modified to be compliant with the compile option -Wall IAW TR#548.  adb
 *
 * Revision 1.5  1993/04/09  15:58:01  ceplib
 * Modifying code to run under the new vxWorks 5.1 kernel IAW TR#457.  adb
 *
 * Revision 1.4  1993/01/13  13:25:16  ceplib
 * Modified to support the NTDS wrap package IAW TR#185.  adb
 * /
 *
 * Revision 1.3  1992/12/04  14:08:04  ceplib
 * Added capability of allowing more than one task to register for a
 * specfic message IAW TR#128.  Added capability of allowing more than one
 * task to receive a NTDS Status change IAW TR#126.   adb
 *
 * Revision 1.2  1992/10/26  15:04:05  ceplib
 * Corrected max NTDS que count detection IAW TR#65.  adb
 *
 * Revision 1.1  1992/10/23  16:51:35  ceplib
 * The file has been modified to support the LLS upgrade IAW TR#62.  adb
 *
 * Revision 1.5  1992/05/28  13:28:00  ceplib
 * Initial version of vxWorks IAW TR#1.  adb
 *
 *
 */



     /* Possible init modes supported by the device configuration parameter
      * init_mode.
      *
      * Any value other than LOCAL_INTERFACE implies that the
      * interface is not colocated with the host
      * processor regardless of the init_mode value.
      */
#define LOCAL_INTERFACE         0 /* Indicates the NTDS cards are with the
                                   * host processor.
                                   */
#define REMOTE_INTERFACE        1 /* Indicates that the NTDS cards are NOT
                                   * located with the host processor.
                                   */
#define SATELLITE_INTERFACE     2 /* Value indicating the user is in an external
                                   * unit.
                                   */
#define TEST_INTERFACE          3 /* Used to allow applications to run without
                                   * a protocol or driver. Mainly used during
                                   * prototyping.
                                   */


     /* The following is a list of the drivers that are available to the
      * driver selector function.
      */ 
#define NO_BOARD        0 
#define ANTARES_BOARD   1  /* 4001 board */
#define ANTARES2_BOARD  2  /* 4002 board */
#define VME_BACKPLANE   3
#define GET_BOARD       4
#define SABTECH_BOARD   5
#define ANTARES_A_BOARD 6  /* 4001A board */


    /* Various word sizes usd by the NTDS interfaces */
#define WORD_8    1
#define WORD_16   2            /* NTDS wordsizes */
#define WORD_32   4            /* Also the number of bytes in the word  */

   /* Defines the different input buffer queuing mechanisms available for a
    * protocol to send messages to the application.
    */

#define QUEUE_INPUT_MESSAGES   0
#define QUEUE_RAW_INPUT_BUFFER 1

	/* Defines the end of a message list for creating queues */

#define MESG_LIST_END	   0

       /* This parameter is used in a message list when one queue is
	* created to receive all messages
	*/

#define SINGLE_MESG_QUE      -1

     /* The next parameters are used to determine if a sending task will
      * wait for an output status response.  It is the responsiblity of
      * the protocol output to return a status if one is expected.
      */

#define NO_CONFIRM_OUTPUT   0
#define CONFIRM_OUTPUT      1

      /* The next parameters are used to determine the disposal of a message
       * buffer
       */

#define NO_MESG_BUFFER     0
#define KEEP_MESG_BUFFER   0
#define FREE_MESG_BUFFER   1
#define KEEP_MESG_ON_Q_ERR 2

       /* This definition determines if an extra word is added to the
        * next message address in Find_NTDS_Mesg.
        */

#define NW_INCLUDES_HEADER_WORD         0
#define NW_DOES_NOT_INCLUDE_HEADER_WORD 1

      /* The following definitions are used by the parser functions to determine
       * the source of the data being parsed.
       */
#define LOCAL_INPUT  0
#define REMOTE_INPUT 1


     /* The following macros are used by the Check_For_NTDS_Boards
      * function to return the result of the function.
      */
#define NO_BOARDS_FOUND    0
#define FIRST_BOARD_FOUND  1
#define SECOND_BOARD_FOUND 2
#define BOTH_BOARDS_FOUND  3

   /******************************
	 * NTDS Control Command Codes *
	 ******************************/

/*     The following are command codes that may be sent to a device using
 * the NTDS control function.
 */

#define INITIALIZE_CHANNEL           1
#define RESUME_CHANNEL               2
#define SUSPEND_CHANNEL              3
#define ENABLE_CHANNEL               4
#define DISABLE_CHANNEL              5
#define RESTART_CHANNEL              6
#define RESET_CHANNEL                7
#define TEST_CHANNEL                 8


	/************************************
	 * Status Return Code Definitions *
	  ************************************/
/*
 *     The following are status return codes that may be returned when an
 *  application calls the NTDS status function.
 */

#define PORT_STATUS_UNKNOWN -3      /* This can be returned from a call to
                                     * Get_NTDS_Port_Status.
                                     */
#define CHANNEL_STATUS_UNKNOWN -2   /* The port is set to this state at the
                                     * very start of initialization
                                     */
#define CHANNEL_FAILED_CONFIG  -1   /* If the NTDS_Comm or driver lauers fail
                                     * fail for any reason this status should be
                                     * set at the completion of configuration
                                     */
#define CHANNEL_RESET           0   /* This status is set if the NTDS_Comm and
                                     * driver layers were successful during
                                     * configuration.
                                     */
#define CHANNEL_INITIALIZING    1   /* Set at the start of the NTDS_Control(
                                     * INITIALIZE_CHANNEL) call only if the
                                     * current channel status is CHANNEL_RESET.
                                     */
#define CHANNEL_INITIALIZED     2   /* Set at the end of the INITIALIZE_CHANNEL
                                     * call but again ONLY if the current 
                                     * status is CHANNEL_RESET or higher.
                                     */
#define CHANNEL_TEST            3   /* This is typically set by the WRAP test
                                     * processing to indicate that the channel
                                     * is being tested. */
#define CHANNEL_ENET_DOWN       4   /* Set by the I/O converter 
                                     * package when I/O converter units are
                                     * used.  This status indicates that the
                                     * ethernet interface is down.  This is only
                                     * applicable when remote communications are
                                     * used.
                                     */
#define CHANNEL_ENET_UP         5   /* Set by the I/O converter 
                                     * package when remote I/O converter units 
                                     * are used.  This status indicates that the
                                     * ethernet interface is up.  This is only
                                     * applicable when remote communications are
                                     * used.
                                     */
#define CHANNEL_DISABLED        6   /* Set in one of two ways. Either by the
                                     * user interactively to control operations
                                     * or by the interface master, depending on
                                     * the protocol.
                                     */
 
    /* The remainder of the interface statuses are protocol dependent
     * and may or may not be used on a specific interface.  The following
     * are guidelines for their use.
     */

#define CHANNEL_ENABLING        7   /*  Channel is being started */ 
#define CHANNEL_ENABLED         8   /*  Channel is has exchanged a mimimum of
                                     * interface information
                                     */
#define CHANNEL_RESTARTING      9   /*  Channel had an error and is being
                                     *  restarted  */
#define CHANNEL_READY          10   /* Channel is ready for communications */

/* The following two definitions are applicable only in a redundant
 * channel environment for interfaces using the ATES protocol. */
#define PORT_SWAP_TO_ALTERNATE 11   /* The alternate port is
                                     * designated as primary (and
                                     * the normal port is
                                     * designated as secondary) */
 
#define PORT_SWAP_TO_NORMAL    12   /* The normal port is
                                     * desginated as primary (and
                                     * the alternate port is
                                     * designated as secondary) */

/* The following defines are used to notify the application of N+1 channel    */
/* status changes.                                                            */                                     
#define NORMAL_PORT_SWAP_TO_NPLUS1            13
#define ALTERNATE_PORT_SWAP_TO_NPLUS1         14
#define NPLUS1_PORT_SWAP_TO_NORMAL            15
#define NPLUS1_PORT_SWAP_TO_ALTERNATE         16
#define NORMAL_CHAN_NTDS_BOARD_CONFIG_ERR     17
#define ALTERNATE_CHAN_NTDS_BOARD_CONFIG_ERR  18
#define NPLUS1_CHAN_NTDS_BOARD_CONFIG_ERR     19

/*
 *     The following are status return codes that may be returned as a
 *  function status.
 */

#define INVALID_DEVICE	          -1
#define BAD_PORT_ID  	          -2
#define INVALID_COMMAND           -3
#define NOT_LONG_ALIGNED          -4
#define QUE_NOT_FOUND             -5
#define QUE_COUNT_ERR             -6
#define UNKNOWN_BUFFER_TYPE       -7
#define MULTI_QUE_ERR             -8
#define BUFFER_TYPE_ERR           -9
#define BUFFER_PART_ERR          -10
#define MT_REGISTER_ERR          -11
#define INVALID_CONFIGURATION    -12
#define DEVICE_NOT_CONFIGURED    -13
#define FUNCTION_NOT_IMPLEMENTED -14
#define COULD_NOT_QUE_MESG       -15
#define NO_STATUS_BUFFER         -16
#define QUE_REGISTER_ERR         -17
#define NO_WRAP_FUNCTION         -18
#define CHANNEL_READINESS_ERR    -19
#define ENET_READINESS_ERR       -20
#define UNKNOWN_DRIVER_TYPE      -21
#define NO_ALTERNATE_PORT        -22
#define NO_SECONDARY_PORT        -22
#define NO_PRIMARY_PORT          -23
#define NO_NORMAL_PORT           -23

/* The following definition is a status that can be returned to the application 
 * if it trys to invoke a protocol's LEVEL2 function dispatcher and the pointer 
 * to the dispatcher, as returned during initialization by the protocol, is 
 * NULL. 
 */

#define LEVEL2_FUNCTIONS_NOT_AVAILABLE -23

/* This definition is a status that can be returned by a protocol if the 
 * protocol was told to invoke a Level 2 function that has not been 
 * implemented. 
 */
#define LEVEL2_FUNCTION_NOT_IMPLEMENTED   -24

/* The following definitions only concern synchronizing the output queues of  */
/* a redundant-channel configuration for a device.                            */
#define REDUNDANT_CHANNEL_QUE_SYNC                       -25
#define GET_REDUNDANT_CHANNEL_QUEUE_SYNC_SEMAPHORE_ERROR -26

/* The following definition determines the size of character strings for
 * ethernet dot format addresses.
 */

#define ENET_ADDRESS_SIZE 20

/* The next definition is used by the dual-channel operations. */
#define PORT_SWAPPING_FAILED -1

/* The next difinition is the "size" constant for the NTDS Gate revision information string. */
#define NTDS_GATE_REVISION_SIZE 84

/* The next definitions are related to the Redundant Channel Operation.
   The applications (SPY & CND) use them to identify which port is being set up
   for a device.  NTDS_Comm uses them when determining where to store the data
   for that port. */
#define NTDS_PRIMARY_PORT   0
#define NTDS_SECONDARY_PORT 1
#define NTDS_NPLUS1_Port    2


     /***************************************************
      *    typedefs used by the NTDS package            *
      ***************************************************/

typedef unsigned int NTDS_MSG_TYPES;

typedef struct   /* structure of NIO Message Packet */
{
    unsigned int   *address;   /* Buffer Address */
    unsigned int   req_size;   /* Number of words (interface width) */
    int            time_out;   /* Referenced in tics   */
    unsigned int   delay_time; /* Granularity of 10 usecs */
    unsigned int   tfr_size;   /* Number of words (interface width) */
    unsigned int   buf_time;   /* Local time the buffer was finished */
    short int      data_msg_number;   /* unique # for each message */
    unsigned short int retry_count; /* How many times to retry the I/O */
} NIO_MESG;

    /*	The following structure is used to decode messages from a block of
     *   messages.  This structure is used by Find_NTDS Message
     */
typedef struct {
   unsigned int *address;
   unsigned int *next_mesg;
   int          word_size;
   unsigned int mt_mask;
   unsigned int size_mask;
   unsigned int mt_shift;
   unsigned int size_shift;
   unsigned int buffer_length;
   unsigned int msg_size;
   unsigned int msg_type;
   unsigned int num_words_type;
} MESG_BLOCK;

   /*  The following structures are used by the application and
    * protocol to pass message buffer information when using the appropriate
    * message input and output functions.
    */

typedef struct
  {
    NIO_MESG io_pkt;   /* The I/O packet that is received from the protocol */
    PART_ID  partition_id;  /* The partition Id of the data buffer  */
    unsigned int remote_time; /* This value is set by a protocol to tell
                               * the application what the external device's
                               * time was when it sent the buffer.
                               */
    char     free_buffer;   /* Flag to release the data buffer */

  } NTDS_INPUT_MSGS;

typedef struct
  {
    NIO_MESG      io_pkt;   /* The I/O packet that is sent to the driver */
    PART_ID       partition_id; /* Partition ID of the buffer being sent */
    unsigned int  *status;  /* Pointer to the status buffer if confirm is set */
    unsigned int              : 21,
                  user_option : 8,
                  confirm     : 1,  /* Wait for an output status.  Must provide
                                     * a status buffer address in the status
                                     * field.
                                     */
                  free_buffer : 2;  /* Controls whether the protocol frees the
                                     * data buffer.
                                     */

   } NTDS_OUTPUT_MSGS;

typedef struct
  {
    unsigned int time;
    unsigned int event;
    unsigned int user1;
    unsigned int user2;
    unsigned int user3;
    unsigned int user4;
    unsigned int user5;
    unsigned int user6;

  } NTDS_SIGNAL_MSGS;

/* This structure is used to pass protocol-specific instructions to
   a protocol's Level 2 control function.  The application wishing to 
   start a Level 2 test on a protocol fill out an instance of this 
   structure and passes it to the NTDS_Comm function "Start_NTDS_Level2".
   Start_NTDS_Level2 then passes it to the protocol's level2_control function.
   The level2_control function pulls out any pertinent information from the
   NTDS_TEST_MSGS structure and uses it to perform the specified Level 2 test. */
typedef struct
  {
    unsigned int time;
    unsigned int test;
    unsigned int user1;
    unsigned int user2;

  } NTDS_TEST_MSGS;

typedef struct
  {
    unsigned int time;
    int status;

  } NTDS_STATUS_MSGS;

typedef struct
  {
    unsigned int time;
    unsigned int error;

  } NTDS_ERROR_MSGS;

    /* This structure is used by the Get_Device_Configuration function to
       report the status of a NTDS device configuration.
    */

typedef struct
{
   int		port;
   unsigned int word_size;
   unsigned int mode;
   unsigned int ei_mode;
   unsigned int init_mode;
   char         enet_address[ENET_ADDRESS_SIZE];
} NTDS_CONFIG;

    /* This structure is used by the Get_Device_Configuration function to
       report the status of a NTDS device configuration.
    */

typedef struct
{
   unsigned int *bd_addr;
   int          bd_type;
   int          io_type;
} NTDS_BOARD_VENDOR;

   /* The following ifdef is used to be backward compatible with the old
    * system.
    */

typedef struct   /* structure of NIO Configuration Packet */
{
        /* Primary port address is Used as backplane id on VME driver */
   unsigned int   primary_ntds_port_address;
   unsigned int   secondary_ntds_port_address;
   int            address_modifier;
   char           enet_address[ENET_ADDRESS_SIZE];
   int            enet_port;
 
   unsigned int                       :  3,
                io_mode               :  4, /* CAT I, CAT II, CAT III */
                interrupt_level       :  3, /* VME interrupt level    */
                manual_ei_mode        :  1, /* Auto or Manual         */
                word_size             :  4, /* BYTE, WORD, LONG WORD  */
                io_type               :  4, /* A, B, C, D, or E       */
                int_enable            :  1, /* Enable interrupts T/F  */
                passive_mode          :  1, /* passive tap            */
                server_enable         :  1, /* enables the vme server */
                driver_type           :  4, /* VME, ANTARES, GET,     */
                secondary_driver_type :  4, /* VME, ANTARES, GET,     */
                init_mode             :  2; /* LOCAL, REMOTE, SATELLITE_INTERFACE, or TEST */
} NIO_BD_CONFIG;
 
   /* The following structure is used to save the address of protocol functions
    * that are called by NTDS_Control.  This structure is saved during device
    * initialization and used by NTDS_Control.
    */

typedef struct
{
   int  (*init_comm) (int, int);
   int  (*enable_comm) (int, int);
   int  (*disable_comm) (int, int);
   int  (*reset_comm) (int, int);
   int  (*restart_comm) (int, int);
   int  (*test_comm) (int, int);  /* Used for NTDS_Wrap */
   int  (*level2_comm) (int, NTDS_TEST_MSGS); /* allows invocation of protocol's Level 2 function dispatcher.*/
   int  (*output_comm) (int, int);
   int  (*input_comm) (int, int, NIO_MESG *);
   int  (*spcl_comm) (int, int);
   int  (*suspend_comm) (int, int);
   int  (*resume_comm) (int, int);
   int  (*redundant_channel_comm) (int, int, int, int); /* Device, Port, State */
} NTDS_CTRL_FUNC;

  /*  This structure is used to maintain the input queue information for
   *  The following structure is used to configure a port and device driver
   *  for communications.
   */

typedef struct device_node
{
   int device_id;
   int port;
   int enet_port;
   char enet_address[ENET_ADDRESS_SIZE];
   unsigned int                        : 26,
                redundant_channel_flag :  1, /* 0=Primary port, 1=Secondary port. */
                no_remote_enable       :  1, /* Determines if remote is tried */
                raw_input_que_type     :  1, /* RAW or PARSED          */
                packed_output_queue    :  1, /* Determine if msg packing is used*/
                in_signal_queue        :  1, /* NO LONGER USED  */
                out_signal_queue       :  1; /* Application sends signals */
   char         name_string[12];             /* Must be a multiple 4 */
   unsigned int user1;
   unsigned int user2;
   unsigned int user3;
   unsigned int user4;
   unsigned int user5;
   unsigned int user6;
   unsigned int user7;
   unsigned int user8;
   unsigned int user9;
   unsigned int user10;
   NIO_BD_CONFIG board;
   NTDS_CTRL_FUNC function;
   struct device_node *next;
} DEVICE_DATA;


	      /* This identifier is used by the NTDS_Comm input functions to
	       * identify input queues.
	       */

typedef unsigned int NTDS_QUE_ID;



	/*********************************************************
	 *   Function Specifications for the NTDS_COMM Module	 *
	 *********************************************************/

/*#########################################################################
 *
 * SYNOPSIS: Get_Device_Index
 *
 * DESCRIPTION: This function attempts to find the index into the Device_Ports
 *              array for the input device.
 *
 * PARAMETERS:
 *
 *   INPUT     device  This parameter contains the logical unit number of
 *                     the device whose port is being found.
 *
 *   OUTPUT    Nothing
 *   RETURNS   Index used when referencing the Device_Ports array.
 *             INVALID_DEVICE
 *
 *
 * #########################################################################*/
int
Get_Device_Index (
   int device
);

/*#########################################################################
 *
 * SYNOPSIS: Configure_NTDS_Device  (application)
 *
 *
 * DESCRIPTION: This function configures and initializes an interface to
 *                a specified device.
 *
 *                To communicate with the protocol tasks, the ntds_comm package
 *                uses queues which are created by this function.  The
 *              application determines the queues that may be created in
 *                addition to an output queue which is always created and input
 *                queues created by the 'Create_NTDS_Input_Q' function.
 *
 * PARAMETERS:
 *
 *     INPUT
 *       device_list_ptr :  This parameter is a pointer to a list of structures
 *                 that contain the information necessary for initializing a
 *                 device's channel.  The list may contain a single device or
 *                 list of devices.  The last entry in the list must have a
 *                 NULL entry.
 *
 *                 The parameters in this structure include the following
 *                 parameters:
 *
 *       id : The identification number of the device being initialized.
 *
 *       port : The hardware port that will be assigned to the device.
 *
 *       primary_port_address : The base VME address of the NTDS interface board
 *                              being used.
 *
 *       secondary_port_address : The base VSB address of the NTDS interface
 *                                board being used.
 *
 *                   NOTE : If a board does not respond at the VME address
 *                          the VSB base address will be used to attempt to
 *                          establish a communications link.
 *
 *       mode :  This parameter determines the NTDS mode of the interface.
 *               The options are:
 *                                COMPUTER
 *                                INTERCOMPUTER
 *                                PERIPHERIAL
 *
 *       interrupt_level :  The VME interrupt level that the interface
 *                          board will use to communicate response information
 *                          back to the host.
 *
 *       host_interrupt_level :  The VME interrupt level that this board will 
 *                               use to communicate with the remote board that
 *                               is on the bus.
 *
 *       manual_ei_mode :   This parameter determines the method of accepting 
 *                          External Interrupts from the remote NTDS device.
 *                          The options are: AUTO_EI_MODE, MANUAL_EI_MODE.
 *
 *       word_size :  This parameter determines the word width of the NTDS
 *                         interface device.  The options are: W_16, W_32.
 *
 *       io_type :  This parameter determines the type of NTDS interface being
 *                  used.  The following choices are available: 
 *                                      NTDS_SLOW
 *                                      NTDS_FAST
 *                                      NTDS_ANEW
 *                                      NTDS_SERIAL
 *                                      NTDS_NATO_SERIAL
 *
 *       queues : This parameter contains information for creating
 *                           queues used by the application.  The application
 *                           has the option of creating an error queue and/or
 *                           a signal queue for receiving information from
 *                           the interface protocol package.  The following 
 *                           codes are used to enable the creation of queues:
 *
 *                                     NTDS_IN_SIGNAL_QUEUE
 *                                     NTDS_OUT_SIGNAL_QUEUE
 *                                     NTDS_PACKED_OUT_QUEUE
 *                                     BOTH_NTDS_SIGNAL_QUEUES
 *                                     ALL_NTDS_QUEUES
 *
 *        input_que_type :  This parameter determines the type of input message
 *                          queuing to be performed.  The options are:
 *                               QUEUE_RAW_INPUT_BUFFER or
 *                               QUEUE_INPUT_MESSAGES
 *
 *           NOTE:
 *
 *          The following parameters are pointers to functions
 *          that may be called by the application using the
 *          NTDS_Control function.
 *
 *       *init_comm_func :  This parameter is a pointer to the protocol
 *                          function that will be invoked when NTDS_Control
 *                          is called with an INITIALIZE_CHANNEL command code.
 *
 *       *enable_comm_func : This parameter is a pointer to the protocol
 *                           function that will be invoked when NTDS_Control
 *                           is called with an ENABLE_CHANNEL command code.
 *
 *       *disable_comm_func : This parameter is a pointer to the protocol
 *                            function that will be invoked when NTDS_Control
 *
 *       *reset_comm_func : This parameter is a pointer to the protocol
 *                          function that will be invoked when NTDS_Control
 *                          is called with a RESET_CHANNEL command code.
 *
 *       *restart_comm_func : This parameter is a pointer to the protocol
 *                            function that will be invoked when NTDS_Control
 *                            is called with a RESTART_CHANNEL command code.
 *
 *       *test_comm_func : This parameter is a pointer to the protocol
 *                         function that will be invoked when NTDS_Control
 *                         is called with an TEST_CHANNEL command code.
 *
 *   OUTPUT  NONE
 *
 *   RETURNS OK
 *           NO_MEMORY_POOL
 *           INVALID_CONFIGURATION
 *           VxWorks error code
 *
 * #########################################################################*/
int
Configure_NTDS_Device (
   DEVICE_DATA *device_list_ptr
);


void Delete_NTDS_Interprocess_Queues(unsigned int port);


/*#########################################################################
 *
 * SYNOPSIS: Get_Device_Data  (application)
 *
 * DESCRIPTION: This function returns the DEVICE_DATA structure of an NTDS port.
 *
 * PARAMETERS:
 *
 *     INPUT  device :  This parameter contains the port number for which the
 *                      DEVICE_DATA structure pointer is returned.
 *
 *    device_data_ptr :  This parameter is a pointer to a variable that
 *                      contains the DEVICE_DATA information.
 *
 *    OUTPUT  status :   The DEVICE_DATA information.
 *
 *    RETURNS None
 *
 *
 * #########################################################################*/
void
Get_Device_Data (
   int         port,
   DEVICE_DATA *device_data_ptr
);

/*#########################################################################
 *
 * SYNOPSIS: Get_Device_Configuration  (application)
 *
 * DESCRIPTION: This function returns the configuration of a NTDS device.
 *
 * PARAMETERS:
 *
 *     INPUT  device :  This parameter contains the logical unit number of
 *                      of the device being read.
 *
 *    device_status_ptr :  This parameter is a pointer to a variable that
 *                      contains the device configuration information.
 *
 *    OUTPUT  status :   The device configuration information.
 *
 *    RETURNS OK
 *            INVALID_DEVICE
 *            vxWorks error code
 *
 *
 * #########################################################################*/
int
Get_Device_Configuration (
   int         device,
   NTDS_CONFIG *device_status_ptr
);

/*#########################################################################
 *
 * SYNOPSIS:  NTDS_Status_Change_  (application)
 *
 * DESCRIPTION:    The NTDS_Status function returns a change of interface
 *                 status to the caller.  The requestor will be suspended
 *                 until an interface status change occurs.  It is the
 *                 responsbility of the interface protocol to send status
 *                 changes to the application.  This can be accomplished
 *                 by calling the Report_Port_Status function.
 *
 * PARAMETERS:
 *
 *    INPUT  :
 *
 *      device :     This parameter contains the logical unit number of
 *                   the device being used.
 *
 *      mesg_ptr :    This parameter is a pointer to the variable that
 *                    will contain the latest status update.
 *
 *      time_out :    This parameter determines how long an application will
 *                    wait for a status change.
 *
 *    OUTPUT :
 *
 *         mesg_ptr :  This parameter contains the following updated
 *                     information if the timeout did not occur; otherwise
 *                     the values are zero.
 *
 *                   *status_ptr :   This parameter is a pointer to the
 *                                  variable that will contain the
 *                                  status.  The actual status that is
 *                                  transferred is dependent on the application.
 *
 *                   *time_ptr  :   This parameter is a pointer to the
 *                                  variable that will contain the time the
 *                                  status change was detected.
 *
 * RETURNS OK 
 *         QUE_REGISTER_ERR
 *         vXWorks ERROR
 *
 *#########################################################################*/
int
NTDS_Status_Change (
   int              device,
   NTDS_STATUS_MSGS *mesg_ptr,
   int              time_out
);

/*#########################################################################
 *
 * SYNOPSIS:  Get_NTDS_Buffer
 *
 * #########################################################################*/
char *
Get_NTDS_Buffer (
  unsigned int size,
  PART_ID      *partition_id
);

/*#########################################################################
 *
 * SYNOPSIS: Show_NTDS_Config  (application)
 *
 * DESCRIPTION: This function displays the configuration of 
 *              a specified NTDS device.
 *
 *
 * PARAMETERS:
 *
 *     INPUT  device :  This parameter contains the logical unit number of
 *                      of the device being read.
 *
 *        OUTPUT :  NOTHING 
 *
 *        RETURNS NOTHING
 *
 * #########################################################################*/
void
Show_NTDS_Config (
   void
);

/* #########################################################################
 *
 * SYNOPSIS:    Test_NTDS_Level2 (application)
 * 
 * DESCRIPTION: This function is used by the application to invoke a LEVEL 2
 *              test in a protocol. It's operation is similar to that of 
 *              NTDS_Control.  Upon protocol initialization, the protocol puts
 *              the address of its Level2 control function into the "level2_comm"
 *              function pointer (part of the NTDS_CTRL_FUNC structure which is 
 *              part of the list of DEVICE_DATA structrures that are sent to
 *              the protocol initialization function).  The "level2_comm" function
 *              is invoked when an application calls Test_NTDS_Level2 in order
 *              to start a Level 2 test scenario.
 *
 * PARAMETERS:  
 *
 *   INPUT:     device - This parameter is the numeric identifier associated
 *                       with an NTDS port.
 *              level2_test_params - this is a structure of type NTDS_TEST_MSGS
 *                                   which is filled out by the application
 *                                   and passed to Test_NTDS_Level2, which 
 *                                   passes it to the protocol's "level2_comm"
 *                                   function.  By using a structure which
 *                                   contains several integers, NTDS_Comm 
 *                                   provides a way to let the protocol and
 *                                   application perform whatever Level2 
 *                                   functions that are needed.
 *
 *   OUTPUT:    NONE                                                         
 *   DATA :     OK                                                           
 *              DEVICE_NOT_CONFIGURED                                        
 *              LEVEL2_FUNCTIONS_NOT_AVAILABLE
 *              subordinate function returns
 * #########################################################################*/
int 
Test_NTDS_Level2(
   int device,
   NTDS_TEST_MSGS level2_test_params
);
 
/* #########################################################################
  *
  * SYNOPSIS:    Get_NTDS_Device_Name (application)
  *
  * DESCRIPTION: This function is used to convert the input Device ID value (an
  *              integer) to its associated Device Name (a string), which is
  *              returned to the calling routine.
  *
  * PARAMETERS:
  *
  *   INPUT:     port - This parameter is the numeric identifier associated
  *                     with an NTDS port.
  *
  *   OUTPUT:    Device Name - This function returns a character string which
  *                            represents the input Device_ID.
  *
  *   DATA :     device_config - Static data structure which contains port
  *                              context information for each NTDS device.
  *
  * #########################################################################*/
char*
Get_NTDS_Device_Name(
   int port
);

/* ##############################################################################
 *
 * SYNOPSIS:    Show_NTDS_Device_Name (Application)
 *
 * DESCRIPTION: This function is used to convert the input Port ID value to
 *              its associated Device Name and then display it on the standard
 *              output device.  First, the input Port ID is examined to see if
 *              is within the legal range (A - Z).  If not, an error message is
 *              displayed, along with the correct calling format.
 *
 * INPUT:       device_ID - This parameter is the integer identifier associated
 *                          with an NTDS port.
 *
 * OUTPUT:      The device name associated with the input Device_ID is printed
 *              to stdout.
 *
 * FUNCTIONS CALLED : Get_NTDS_Device_Name - This function is called to obtain
 *                                           device name of the input Device ID.
 *
 * ##########################################################################*/
void
Show_NTDS_Device_Name(
   int device_ID
);


/*#########################################################################
 *
 * SYNOPSIS: Send_NTDS_Mesg_To_Port   (application)
 *
 * DESCRIPTION:     This function queues an output request to the specified
 *                port queue.  The caller provides the port id, a buffer
 *                descriptor, and a queuing priority.
 *
 *                The buffer descriptor is of an NTDS_OUTPUT_MSGS type containing
 *                the starting address of the message, and the length of the
 *                message. It also includes the buffer partition_id.
 *
 *                   The caller determines how the output request will be queued
 *                by setting the priority parameter to either MSG_PRI_NORMAL
 *                or MSG_PRI_URGENT.  If the priority is set to MSG_PRI_NORMAL,
 *                the output request is placed at the end of the output queue.
 *                If the priority is set to MSG_PRI_URGENT, the output request
 *                is placed at the front of the queue.
 *
 *                   The protocol output task is expected to dequeue the
 *                output messages by calling the Deque_NTDS_Output_Mesg
 *                function.
 *
 * PARAMETERS:
 *
 *    INPUT   port    :    This parameter contains the logical unit number of
 *                        the port being used.
 *
 *        *buffer_ptr :    This parameter contains a pointer to the message
 *                        buffer of type NTDS_OUTPUT_MSGS.
 *
 *                     The following fields are passed to the application in the
 *                     buffer parameter:
 *
 *        io_pkt  : This field is a structure of information required for
 *                  performing the buffer transfer.
 *
 *        partition_id : This field contains the partition_id of the
 *                       buffer.  This allows the protocol task to return
 *                       the buffer to the proper partition when partitions
 *                       are being used. When malloc is being used this
 *                       field should be NULL.
 *
 *        status : This field contains a pointer to the status buffer that
 *            will be used by the protocol to save the transfer status.  This
 *            field is only used if the "confirm" flag is set.  Likewise, if the
 *            "confirm" flag is set a valid pointer must be provided.  If the
 *            "confirm" flag is false the status pointer should be NULL.
 *
 *        confirm : This field determines if the protocol task should return a
 *            status to the application.  If the flag is "TRUE" a valid status
 *            pointer must be provided.  There are two possibilities for this
 *            field  (TRUE, FALSE).
 *
 *        free_buffer : This field determines if the protocol should free the
 *            buffer being sent.  There are two possibilities for this field.
 *            (TRUE, FALSE)
 *
 *              priority :    This parameter contains the priority at which the
 *             message buffer will be placed into the output
 *             queue.  If the priority is set to MSG_PRI_NORMAL,
 *             the message will be put at the end of the queued
 *             message list.  If the priority is set to
 *             MSG_PRI_URGENT the message will be placed at the
 *             front of the list.
 *
 *   OUTPUT  NONE
 *
 *   RETURNS OK
 *           NOT_LONG_ALIGNED
 *           DEVICE_NOT_CONFIGURED
 *           CHANNEL_READINESS_ERR
 *           FUNCTION_NOT_IMPLEMENTED
 *           NO_STATUS_BUFFER
 *
 *           subordinate function returns
 *           VxWorks error code
 *
 *########################################################################*/
//int
//Send_NTDS_Mesg_To_Port (
//  int                  port,
//  NTDS_OUTPUT_MSGS   * buffer_ptr,
//  int                  priority
//);


/*#########################################################################
 *
 * SYNOPSIS: Create_NTDS_Input_Q   (application)
 *
 * DESCRIPTION:        This function creates an input message queue for the
 *                  specified device.  The function returns an index to the
 *                  NTDS_QUEUE_CTRL_BLK which is to used when requesting one
 *                  of the registered message types from the remote device.
 *
 *                     If more than one queue is created, the caller must
 *                  provide a list of message types defining the messages
 *                  to be placed in the new queue.
 *
 * PARAMETERS:
 *
 *    INPUT    device :     This parameter contains the logical unit number of
 *                       the device for which the queue will be created.
 *
 *             buffer_size :  This parameter is used to determine the size of
 *                           message buffers if the application wants to use
 *                           a partition of buffers. The word size value is
 *                           the max number of NTDS words that will be placed
 *                           in a buffer.  The buffer size must be large
 *                           enough to receive the largest message that
 *                           will be placed in the queue.
 *
 *             n_buffers :     This parameter determines the number of buffers
 *                          to be created in the partition.
 *
 *
 *        NOTE :      If the number_of_buffers parameter equals zero the
 *                NTDS_Comm package will malloc memory for each received
 *                message instead of using a unique partition for a specific
 *                group of messages when the buffer size and number of 
 *                buffers are provided by the caller.  
 *
 *        *msg_type_list_ptr :     This parameter contains a list of message
 *                               types expected to be placed in the new
 *                               queue.  The list must be terminated with a
 *                               MESG_LIST_END parameter to allow the function
 *                               to determine the end of the list.
 *                               The user may set first element of the array to
 *                               a SINGLE_MESG_QUE if this will be the only
 *                               input queue for this device and all messages
 *                               are to be routed to this queue.
 *
 *    OUTPUT   *index_ptr :  This parameter is a pointer to the variable that
 *                     will contain an index to the queue control block entry
 *                     of the created queue.  The value returned is an index
 *                     into the Que_List array for rapid access to parameters
 *                     in the control block.
 *
 *
 *    RETURNS  OK
 *             DEVICE_NOT_CONFIGURED
 *             MULTI_QUE_ERR
 *             MT_REGISTER_ERR
 *
 *             subordinate function returns
 *             VxWorks error code
 *
 *
 * #########################################################################*/
int
Create_NTDS_Input_Q (
   int             device,
   unsigned int    buffer_size,
   unsigned int    n_buffers,
   NTDS_MSG_TYPES  *msg_type_list_ptr,
   NTDS_QUE_ID     *index_ptr
);

/*#########################################################################
 *
 * SYNOPSIS: Send_NTDS_Mesg   (application)
 *
 * DESCRIPTION:     This function queues an output request to the specified
 *                device queue.  The caller provides the device id, a buffer
 *                descriptor, and a queuing priority.
 *
 *                The buffer descriptor is of a NTDS_OUTPUT_MSGS type containing
 *                the starting address of the message, and the length of the 
 *                message. It also includes the buffer partition_id.
 *
 *                   The caller determines how the output request will be queued
 *                by setting the priority parameter to either MSG_PRI_NORMAL
 *                or MSG_PRI_URGENT.  If the priority is set to MSG_PRI_NORMAL,
 *                the output request is placed at the end of the output queue.
 *                If the priority is set to MSG_PRI_URGENT, the output request
 *                is placed at the front of the queue.
 *
 *                   The protocol output task is expected to dequeue the
 *                output messages by calling the Deque_NTDS_Output_Mesg
 *                function.
 *
 * PARAMETERS:
 *
 *    INPUT   device  :    This parameter contains the logical unit number of
 *                        the device being used.
 *
 *        *buffer_ptr :    This parameter contains a pointer to the message
 *                        buffer of type NTDS_OUTPUT_MSGS.
 *
 *                     The following fields are passed to the application in the
 *                     buffer parameter:
 *
 *        io_pkt  : This field is a structure of information required for
 *                  performing the buffer transfer.
 *
 *        partition_id : This field contains the partition_id of the
 *                       buffer.  This allows the protocol task to return
 *                       the buffer to the proper partition when partitions
 *                       are being used. When malloc is being used this
 *                       field should be NULL.
 *
 *        status : This field contains a pointer to the status buffer that
 *            will be used by the protocol to save the transfer status.  This
 *            field is only used if the "confirm" flag is set.  Likewise, if the
 *            "confirm" flag is set a valid pointer must be provided.  If the
 *            "confirm" flag is false the status pointer should be NULL.
 *
 *        confirm : This field determines if the protocol task should return a
 *            status to the application.  If the flag is "TRUE" a valid status
 *            pointer must be provided.  There are two possibilities for this
 *            field  (TRUE, FALSE).
 *
 *        free_buffer : This field determines if the protocol should free the
 *            buffer being sent.  There are two possibilities for this field.
 *            (TRUE, FALSE)
 *
 *              priority :    This parameter contains the priority at which the
 *             message buffer will be placed into the output
 *             queue.  If the priority is set to MSG_PRI_NORMAL,
 *             the message will be put at the end of the queued
 *             message list.  If the priority is set to
 *             MSG_PRI_URGENT the message will be placed at the
 *             front of the list.
 *
 *   OUTPUT  NONE
 *
 *   RETURNS OK
 *           NOT_LONG_ALIGNED
 *           DEVICE_NOT_CONFIGURED
 *           CHANNEL_READINESS_ERR
 *           FUNCTION_NOT_IMPLEMENTED
 *           NO_STATUS_BUFFER
 *
 *           subordinate function returns
 *           VxWorks error code
 *
 *########################################################################*/
int
Send_NTDS_Mesg (
  int                  device,
  NTDS_OUTPUT_MSGS   * buffer_ptr,
  int                  priority
);

/*#########################################################################
 *
 * SYNOPSIS: Send_NTDS_Mesg_Block   (application)
 *
 * DESCRIPTION:    This function queues a mesg block for output to the specified
 *                device queue.  The caller provides the device id, a buffer
 *                descriptor, and a queuing priority.
 *
 *                The buffer descriptor is of a NTDS_OUTPUT_MSGS type containing
 *                the starting address of the message, and the length of the 
 *                message. It also includes the buffer partition_id.
 *
 *                   The caller determines how the output request will be queued
 *                by setting the priority parameter to either MSG_PRI_NORMAL
 *                or MSG_PRI_URGENT.  If the priority is set to MSG_PRI_NORMAL,
 *                the output request is placed at the end of the output queue.
 *                If the priority is set to MSG_PRI_URGENT, the output request
 *                is placed at the front of the queue.
 *
 *                   The protocol output task is expected to dequeue the
 *                output messages by calling the Deque_NTDS_Output_Mesg_Block
 *                function.
 *
 * PARAMETERS:
 *
 *    INPUT   device  :    This parameter contains the logical unit number of
 *                        the device being used.
 *
 *        *buffer_ptr :    This parameter contains a pointer to the message
 *                        buffer of type NTDS_OUTPUT_MSGS.
 *
 *                     The following fields are passed to the application in the
 *                     buffer parameter:
 *
 *        io_pkt  : This field is a structure of information required for
 *                  performing the buffer transfer.
 *
 *   partition_id : This field contains the partition_id of the
 *                  buffer.  This allows the protocol task to return
 *                  the buffer to the proper partition when partitions
 *                  are being used. When malloc is being used this
 *                  field should be NULL.
 *
 *        status : This field contains a pointer to the status buffer that
 *            will be used by the protocol to save the transfer status.  This
 *            field is only used if the "confirm" flag is set.  Likewise, if the
 *            "confirm" flag is set a valid pointer must be provided.  If the
 *            "confirm" flag is false the status pointer should be NULL.
 *
 *        confirm : This field determines if the protocol task should return a
 *            status to the application.  If the flag is "TRUE" a valid status
 *            pointer must be provided.  There are two possibilities for this
 *            field  (TRUE, FALSE).
 *
 *        free_buffer : This field determines if the protocol should free the
 *            buffer being sent.  There are two possibilities for this field.
 *            (TRUE, FALSE)
 *
 *              priority :    This parameter contains the priority at which the
 *             message buffer will be placed into the output
 *             queue.  If the priority is set to MSG_PRI_NORMAL,
 *             the message will be put at the end of the queued
 *             message list.  If the priority is set to
 *             MSG_PRI_URGENT the message will be placed at the
 *             front of the list.
 *
 *   OUTPUT  NONE
 *
 *   RETURNS OK
 *           NOT_LONG_ALIGNED
 *           DEVICE_NOT_CONFIGURED
 *           CHANNEL_READINESS_ERR
 *           FUNCTION_NOT_IMPLEMENTED
 *           NO_STATUS_BUFFER
 *
 *           subordinate function returns
 *           VxWorks error code
 *
 * ########################################################################*/
int
Send_NTDS_Mesg_Block (
  int                device,
  NTDS_OUTPUT_MSGS   * buffer_ptr,
  int                priority
);

/*#########################################################################
 *
 * SYNOPSIS: Recv_NTDS_Mesg  (application)
 *
 * DESCRIPTION:      This function allows the application to request a message
 *                from an input queue provided by the caller.  The caller also
 *                provides a pointer to a buffer descriptor (NTDS_INPUT_MSGS)
 *                to put the received message information when a buffer
 *                has been received.
 *
 *                   The caller determines if it will check and/or wait for a
 *                message to be received.  If the caller elects to not wait
 *                by setting the wait_opt parameter to NO_WAIT, a message will
 *                be taken from the queue if a message is availaible.  If a
 *                message is not available, the caller will receive a no message
 *                status.  When the caller elects to wait for a message, the
 *                calling task will be suspended until a message is received or
 *                the timeout has expired.  The timeout is set by the caller
 *                by providing a value in the timeout parameter.  This value is
 *                the number of vxWorks tics that the caller will wait for the
 *                message to be received.  If the timeout value is WAIT_FOREVER,
 *                the caller will wait until a message is received.
 *
 *                   When a message is available, the buffer descriptor returned
 *                is of type NTDS_INPUT_MSGS. The buffer descriptor contains the
 *                starting address of the message, the length of the message,
 *                and a time stamp.  It also includes the buffer partition_id.
 *                The buffer partition_id is set to NULL if the memory was
 *                obtained using malloc.
 *
 * PARAMETERS:
 *
 *    INPUT   device :   This parameter contains the logical unit number of
 *                     the device being used.
 *
 *            qid :    This parameter determines the input queue from which a
 *                   message will be taken.
 *
 *            time_out :    This parameter determines how long the caller will
 *                       wait for a message to be received before declaring
 *                       an input failure.  If this parameter is WAIT_FOREVER,
 *                       caller will wait forever for a message to be received.
 *                       if this parameter is NO_WAIT, it will return
 *                       immediately.
 *
 *   OUTPUT    *buffer_ptr :  This parameter is a pointer to the mesg descriptor
 *                       variable that will contain the message information
 *                       of the new buffer.
 *
 *               The buffer variable is updated with
 *             message information from the newly received buffer.
 *             The following fields are passed to the application in the
 *             buffer parameter:
 *
 *                  *address : This field is a pointer to the message that
 *                            was received.
 *
 *                  partition_id : This field contains the partition_id of the
 *                             buffer.  This allows the application to return
 *                            the buffer to the proper partition when partitions
 *                            are being used. When malloc is being used this
 *                            field will be NULL.
 *
 *                  length : This field contains the length of the data buffer
 *                            to be transferred. The range of this field is from
 *                            0 to 65535.
 *
 *                  time : Time stamp of received message.
 *
 *   RETURNS OK
 *           DEVICE_NOT_CONFIGURED
 *
 *           subordinate function returns
 *           VxWorks error code
 *
 * #########################################################################*/
int
Recv_NTDS_Mesg (
   int             device,
   NTDS_QUE_ID     lcl_index,
   NTDS_INPUT_MSGS *buffer_ptr,
   int             timeout
);

/*##########################################################################
 *
 * SYNOPSIS:       Recv_NTDS_Signal   (application)
 *
 * DESCRIPTION:    This function returns a special event signal from the
 *                 selected device.  The caller determines if it will wait for
 *                 a signal response by setting the time_out variable.
 *
 *                    It is expected that the interface protocol will place
 *                 detected signals in the signal queue by calling the
 *                 Report_NTDS_Signal function.
 *
 * PARAMETERS:
 *
 *    INPUT  device :   This parameter contains the logical unit number of the
 *                    device being monitored.
 *
 *         signal_ptr :   A pointer the variable that will hold the updated
 *                      signal information.
 *
 *         time_out :   This parameter determines how long the caller will
 *                      wait for a message to be received before declaring
 *                      an input failure.  The time_out can also be specified
 *                      as NO_WAIT or WAIT_FOREVER.
 *
 *    OUTPUT :
 *
 *        *signal_ptr :  This parameter contains the following updated
 *                     information if the timeout did not occur; otherwise
 *                     the values are zero.
 *
 *                   event_ptr:     This parameter is a pointer to the
 *                                  variable that will contain the signal
 *                                  status.  The actual status that is
 *                                  transferred is dependent on the application.
 *
 *                   time_ptr:      This parameter is a pointer to the
 *                                  variable that will contain the time the
 *                                  signal status was detected.
 *
 * RETURNS   OK
 *           DEVICE_NOT_CONFIGURED
 *           VxWorks error status
 *
 * #########################################################################*/
int
Recv_NTDS_Signal (
   int              device,
   NTDS_SIGNAL_MSGS *signal_ptr,
   int              timeout
);

/*#########################################################################
 *
 * SYNOPSIS:  Send_NTDS_Signal    (application)
 *
 * DESCRIPTION:       This function routes a signal code to the protocol for
 *                 processing.  The protocol is expected to remove the
 *                 signal entry by calling the Deque_Output_Signal function.
 *
 * PARAMETERS:
 *
 *     INPUT :
 *
 *         device :   This variable determines which devices's signal queue
 *                    will receive the signal code.
 *
 *       signal_ptr :   A pointer the variable that will hold the updated
 *                    signal information.
 *
 *                   event :   This parameter is the variable that contains
 *                             the signal value.  The actual value that is
 *                             transferred is dependent on the application.
 *
 *                   time  :   This parameter is the variable that contains
 *                             the time that the signal was sent.  The use of
 *                             this values is application dependent.
 *
 *     OUTPUT     NOTHING
 *
 *     RETURNS  OK
 *              DEVICE_NOT_CONFIGURED
 *              vxWorks error code
 *
 *#########################################################################*/
int
Send_NTDS_Signal (
   int              device,
   NTDS_SIGNAL_MSGS *signal_ptr
);

/*##########################################################################
 *
 * SYNOPSIS:       Recv_NTDS_Error   (application)
 *
 * DESCRIPTION:       Returns an error message from the selected device.  The
 *                 caller determines if it will wait for an error response.
 *                 If the caller sets the wait option, the timeout parameter
 *                 will be used to determine how long the caller will wait.
 *
 *                 It is expected that the interface protocol will place
 *                 detected errors in the queue by calling the Report_NTDS_Error
 *                 function.
 *
 * PARAMETERS:
 *
 *    INPUT :
 *         device :   This parameter contains the logical unit number of the
 *                    device being monitored.
 *
 *       error_ptr:   A pointer the variable that will hold the updated
 *                    error information.
 *
 *                   *event_ptr :   This parameter is a pointer to the
 *                                  variable that will contain the error
 *                                  status.  The actual status that is
 *                                  transferred is dependent on the application.
 *
 *                   *time_ptr  :   This parameter is a pointer to the
 *                                  variable that will contain the time the
 *                                  error status was detected.
 *
 *            time_out :   This parameter determines how long the caller will
 *                       wait for a message to be received before declaring
 *                       an input failure.  The time_out can also be specified
 *                       as NO_WAIT or WAIT_FOREVER.
 *
 *    OUTPUT :
 *
 *       error_ptr :   A pointer the variable that will hold the updated
 *                    error information.
 *
 *                   *event_ptr :   This parameter is a pointer to the
 *                                  variable that will contain the error
 *                                  status.  The actual status that is
 *                                  transferred is dependent on the application.
 *
 *                   *time_ptr  :   This parameter is a pointer to the
 *                                  variable that will contain the time the
 *                                  error status was detected.
 *
 * RETURNS   OK
 *           DEVICE_NOT_CONFIGURED
 *           VxWorks error status
 *
 * #########################################################################*/
int
Recv_NTDS_Error (
   int             device,
   NTDS_ERROR_MSGS *mesg_ptr,
   int             timeout
);

/*##########################################################################
 *
 * SYNOPSIS:       Recv_Secondary_NTDS_Error   (application)
 *
 * DESCRIPTION:       Returns an error message from the selected device's 
 *                 secondary port.  The caller determines if it will wait for 
 *                 an error response.  If the caller sets the wait option, the 
 *                 timeout parameter will be used to determine how long the 
 *                 caller will wait.
 *
 *                 It is expected that the interface protocol will place
 *                 detected errors in the queue by calling the Report_NTDS_Error
 *                 function.
 *
 *                 This function is typically called by interfaces that use
 *                 redundant channels.  Typically, both channels are maintaining
 *                 an interface by passing protocol messages.  Only one of the
 *                 channels is actually sending and receiving messages.  It is
 *                 the application's responsibility to determine which channel
 *                 is the primary channel (CURRENT_PORT).  The function
 *                 Exchange_NTDS_Ports performs the actual swapping if 
 *                 channels.
 *
 * PARAMETERS:
 *
 *    INPUT :
 *         device :   This parameter contains the logical unit number of the
 *                    device being monitored.
 *
 *       error_ptr:   A pointer the variable that will hold the updated
 *                    error information.
 *
 *                   *event_ptr :   This parameter is a pointer to the
 *                                  variable that will contain the error
 *                                  status.  The actual status that is
 *                                  transferred is dependent on the application.
 *
 *                   *time_ptr  :   This parameter is a pointer to the
 *                                  variable that will contain the time the
 *                                  error status was detected.
 *
 *            time_out :   This parameter determines how long the caller will
 *                       wait for a message to be received before declaring
 *                       an input failure.  The time_out can also be specified
 *                       as NO_WAIT or WAIT_FOREVER.
 *
 *    OUTPUT :
 *
 *       error_ptr :   A pointer the variable that will hold the updated
 *                    error information.
 *
 *                   *event_ptr :   This parameter is a pointer to the
 *                                  variable that will contain the error
 *                                  status.  The actual status that is
 *                                  transferred is dependent on the application.
 *
 *                   *time_ptr  :   This parameter is a pointer to the
 *                                  variable that will contain the time the
 *                                  error status was detected.
 *
 * RETURNS   OK
 *           DEVICE_NOT_CONFIGURED
 *           VxWorks error status
 *
 * #########################################################################*/
int
Recv_Secondary_NTDS_Error (
   int             device,
   NTDS_ERROR_MSGS *mesg_ptr,
   int             timeout
);

/*#########################################################################
 *
 * SYNOPSIS:           NTDS_Control   (application)
 *
 * DESCRIPTION:       NTDS_Control provides run time control of the NTDS
 *                   interface.  The definition and usage of these functions is
 *       dependent on the protocol being used.  Therefore, each
 *       interface protocol function provides the functions required to
 *       implement the protocol.  The following is a list of functions that
 *       may be invoked by NTDS control.
 *
 *        Init_Comm ()
 *        Enable_Comm ()
 *        Suspend_Comm ()
 *        Resume_Comm ()
 *        Disable_Comm ()
 *        Reset_Comm ()
 *        Restart_Comm ()
 *        Test_Comm ()
 *
 *     NOTE:    If any of these functions are not required by a protocol a
 *              NULL pointer should be provided for those functions when
 *              the device is initialized.  See "Configure_NTDS_Device".
 *
 * PARAMETERS:
 *
 *   INPUT   device :        This parameter contains the logical unit number of the
 *                      device being used.
 *
 *             command : This parameter contains the command to be executed.
 *
 *   OUTPUT  NONE
 *
 *   RETURNS OK
 *           DEVICE_NOT_CONFIGURED
 *           INVALID_COMMAND
 *           subordinate function returns
 *
 * #########################################################################*/
int
NTDS_Control (
   int device,
   int command
);

/*#########################################################################
 *
 * SYNOPSIS:           NTDS_Secondary_Control   (application)
 *
 * DESCRIPTION:       NTDS_Secondary_Control provides run time control of the secondary
 *       NTDS interface.  The definition and usage of these functions is
 *       dependent on the protocol being used.  Therefore, each
 *       interface protocol function provides the functions required to
 *       implement the protocol.  The following is a list of functions that
 *       may be invoked by NTDS control.
 *
 *        Init_Comm ()
 *        Enable_Comm ()
 *        Suspend_Comm ()
 *        Resume_Comm ()
 *        Disable_Comm ()
 *        Reset_Comm ()
 *        Restart_Comm ()
 *        Test_Comm ()
 *
 *     NOTE:    If any of these functions are not required by a protocol a
 *              NULL pointer should be provided for those functions when
 *              the device is initialized.  See "Configure_NTDS_Device".
 *
 * PARAMETERS:
 *
 *   INPUT   device :        This parameter contains the logical unit number of the
 *                      device being used.
 *
 *             command : This parameter contains the command to be executed.
 *
 *   OUTPUT  NONE
 *
 *   RETURNS OK
 *           DEVICE_NOT_CONFIGURED
 *           INVALID_COMMAND
 *           subordinate function returns
 *
 * #########################################################################*/
int
NTDS_Secondary_Control (
   int device,
   int command
);


/*#########################################################################
 *
 * SYNOPSIS:           Redundant_Channel_Control   (application)
 *
 * DESCRIPTION:        Redundant_Channel_Control provides a means by which
 *                     a state, detected on one channel in a redundant-channel
 *                     configuration, can cause the invocation of an action on
 *                     the other channel, assuming it is able to carry out the
 *                     action.
 *
 *
 * PARAMETERS:
 *
 *   INPUT   device :   This parameter contains the logical unit number of the
 *                      device being used.
 *
 *           port   :   The port detected the "State" which is to be acted upon.
 *
 *
 *           state  : This parameter contains the "state" of the port. An action
 *                    may be carried out on the redundant-channel in response
 *                    to this "state" being reported.
 *
 *   OUTPUT  NONE
 *
 *   RETURNS OK
 *           DEVICE_NOT_CONFIGURED
 *           INVALID_COMMAND
 *           subordinate function returns
 *
 * #########################################################################*/
int
Redundant_Channel_Control(
  int device,
  int port,
  int state
);

//#ifndef USG1
/*#########################################################################
 *
 * SYNOPSIS:           Get_Redundant_Channels_Queue_Sync_Semaphore (application)
 *
 * DESCRIPTION:        Get_Redundant_Channels_Queue_Sync_Semaphore is called by
 *                     a port when its output message queue is awakened by the
 *                     receipt of a REDUNDANT_CHANNEL_SYNC_MT.  This function
 *                     returns a semaphore to the caller.  The caller blocks on
 *                     this semaphore, waiting for 2nd port to wake up and call
 *                     this function.  When this function is called by the 2nd
 *                     port of the redundant-channel pair, the QIDs of the two
 *                     ports are swapped and then a "semGive" is
 *                     performed on each semaphore.  This will allow both ports
 *                     to block on their output message queues, which were
 *                     swapped, at the same time.  This prevents one port from
 *                     swapping prior to the 2nd and stealing the 2nd port's
 *                     REDUNDANT_CHANNEL_SYNC_MT message.
 *
 *
 * PARAMETERS:
 *
 *   INPUT   port :   Channel identifier for queue sync operations.
 *
 *
 *   OUTPUT  Swapped QIDs
 *           Queue synchronization messages
 *
 *
 *
 *   RETURNS None
 *
 * #########################################################################*/
SEM_ID
Get_Redundant_Channels_Queue_Sync_Semaphore(
  int port
);
#endif

#ifndef USG1
/*#########################################################################
 *
 * SYNOPSIS:           Change_Port_Name (application)
 *
 * DESCRIPTION:        This function changes the name of the input port, to
 *                     the name specified in the "New_Name" parameter.
 *
 *
 * PARAMETERS:
 *
 *   INPUT   Port :   Channel identifier for queue sync operations.
 *           New_Name: Name to give the port.
 *
 *
 *   OUTPUT  Nothing
 *
 *
 *
 *   RETURNS Nothing.
 *
 *
 * #########################################################################*/
void
Change_Port_Name(
  int Port,
  char* New_Name
);
#endif

/*#########################################################################
 *
 * SYNOPSIS:  Send_Swap_Status    (protocol)
 *
 * DESCRIPTION:      This function sends swap notifications to applications
 *                that have redundant channels.  The notification will be
 *                sent only after a swap has occurred.
 *
 * PARAMETERS:
 *
 *    INPUT   device    :  This parameter contains the device id of the
 *                         interface cards involved in the port swap.
 *
 *            swap_msg  :  This parameter indicates the direction of the swap.
 *
 *    OUTPUT  NOTHING
 *
 * RETURNS OK or
 *         vxWorks ERROR code.
 *
 *#########################################################################*/
int
Send_Swap_Status (
   int device,
   int swap_msg
);


/*##########################################################################
 *
 * SYNOPSIS:       App_NTDS_Debug   (application)
 *
 * DESCRIPTION:    Allows an application send a debug message to the the
 *               interface tracer.
 *
 * PARAMETERS:
 *
 *    INPUT :
 *         device :   This parameter contains the logical unit number of the
 *                    device being monitored.
 *
 *       value1 :   The first value to be saved in the trace.
 *
 *       value2 :   The second value to be saved in the trace.
 *
 *       value3 :   The third value to be saved in the trace.
 *
 *    OUTPUT : NOTHING
 *
 * RETURNS   NOTHING
 *
 * #########################################################################*/
//void
//App_NTDS_Debug (
//   int device,
//   int value1,
//   int value2,
//   short int value3
//);

/*#########################################################################
 *
 * SYNOPSIS:  Check_NTDS_Input_Que    (application)
 *
 * DESCRIPTION:    The Check_NTDS_Input_Que function checks an input 
 *                 message queue for messages waiting to be processed.  The
 *                 function also returns the number of times the sender
 *                 timed out trying to queue a message.  THis is an 
 *                 indication of how backed up the queue has become.
 *                 caller.
 *
 * PARAMETERS:
 *
 *    INPUT   device :    This parameter contains the logical unit number of
 *                        the device being used.
 *
 *            qid    :    The index of the input Queue to be checked.
 *
 *            msg_count_ptr   : Pointer to a variable that will reflect the
 *                              number of messages in the queue.
 *
 *            msg_timeout_ptr : Pointer to a variable that will reflect the
 *                              number of times the sender was rejected.
 *
 *    OUTPUT  msg_count_ptr   : Contains an updated value that reflects the
 *                              number of messages in the queue.
 *
 *            msg_timeout_ptr : Contains an updated value that reflects the
 *                              number of times the sender was rejected.
 *
 *
 * RETURNS NOTHING
 *
 *#########################################################################*/
//void
//Check_NTDS_Input_Que (
//   int          device,
//   NTDS_QUE_ID  lcl_index,
//   unsigned int *msg_count,
//   unsigned int *msg_timeout
//);

/*#########################################################################
 *
 * SYNOPSIS:  Get_NTDS_Port    (application)
 *
 * DESCRIPTION:    The Get_NTDS_Port function finds the current low 
 *                 level port that is mapped to the selected device.
 *
 * PARAMETERS:
 *
 *    INPUT   device :  This parameter contains the logical unit number of
 *                      the device being used.
 *
 *    OUTPUT  NOTHING
 *
 *
 * RETURNS  The device's current port.
 *          INVALID_DEVICE  If a valid port could not be found.
 *
 *#########################################################################*/
int
Get_NTDS_Port (
   int device
);

/*#########################################################################
 *
 * SYNOPSIS:  Get_NTDS_Word_Size    (application)
 *
 * DESCRIPTION:    The Get_NTDS_Word_Size function returns the interface's
 *                 word size as defined in the IDS.
 *
 * PARAMETERS:
 *
 *    INPUT   device :  This parameter contains the logical unit number of
 *                      the device being used.
 *
 *    OUTPUT  NOTHING
 *
 *
 * RETURNS  The device's word_size.
 *          INVALID_DEVICE  If a valid port could not be found.
 *
 *#########################################################################*/
unsigned int
Get_NTDS_Word_Size (
   int device
);

/*#########################################################################
 *
 * SYNOPSIS:  Get_Interface_Status    (application)
 *
 * DESCRIPTION:    The Get_Interface_Status function returns one of two values
 *                 to the caller.  Either the "Interface_Down_Status" or the
 *                 "Interface_Up_Status".  If there is no viable channel
 *                 operating for the "device", then "Interface_Down_Status" is
 *                 returned.  If at least one channel is viable,
 *                 "Interface_Up_Status" is returned.
 *
 * PARAMETERS:
 *
 *    INPUT   device :  number associated with the piece of hardware on the
 *                      other side of the interface.
 *            Interface_Up_Status : value that's returned if at least one
 *                      channel to the device is viable.
 *            Interface_Down_Status : value that's returned if there is NO viable
 *                      channel to the device is viable.
 *
 *    OUTPUT  NOTHING
 *
 *
 * RETURNS  The an Interface status.
 *
 *
 *#########################################################################*/
int
Get_Interface_Status (
  int Device,
  int Interface_Down_Status,
  int Interface_Up_Status
);

/*#########################################################################
 *
 * SYNOPSIS:  Get_Port_Characteristic    (application)
 *
 * DESCRIPTION:    The Get_Port_Characteristic function returns one of two values
 *                 to the caller.  Either the Primary Port's characteristic or the
 *                 Secondary port's characteristic, depending if the input port
 *                 identifier is the Primary or Secondary port for the device.
 *
 * PARAMETERS:
 *
 *    INPUT   device :  number associated with the piece of hardware on the
 *                      other side of the interface.
 *            Primary_Port_Characteristic : value that's returned if the input
 *                      port identifier is the Primary port for the device.
 *            Secondary_Port_Characteristic : value that's returned if the input
 *                      port identifier is the Secondary port for the device.
 *
 *    OUTPUT  NOTHING
 *
 *
 * RETURNS  The appropriate characteristic value.
 *
 *
 *#########################################################################*/
int
Get_Port_Characteristic (
  int Device,
  int Port,
  int Primary_Port_Characteristic,
  int Sedondary_Port_Characteristic
);

/*#########################################################################
 *
 * SYNOPSIS:  Get_Channel_ID    (application)
 *
 * DESCRIPTION:    The Get_Channel_ID function determines if the input "port"
 *                 parameter is the "Primary" or "Secondary" port for
 *                 its associated device.  The return value is a Channel ID
 *                 value associated with either the Primary or Secondary channel.
 *
 * PARAMETERS:
 *
 *    INPUT   port :  This parameter contains the port number assigned to a
 *                    particular instance of a protocol which is servicing a
 *                    particular device.
 *
 *    OUTPUT  NOTHING
 *
 *
 * RETURNS  The port's associated "Channel ID".
 *
 *
 *#########################################################################*/
int
Get_Channel_ID (
   int port
);

/*#########################################################################
 *
 * SYNOPSIS:  Get_Alternate_NTDS_Port    (application)
 *
 * DESCRIPTION:    The Get_NTDS_Port function finds the alternate low 
 *                 level port that is mapped to the selected device.
 *
 * PARAMETERS:
 *
 *    INPUT   device :  This parameter contains the logical unit number of
 *                      the device being used.
 *
 *    OUTPUT  NOTHING
 *
 *
 * RETURNS  The device's alternate port.
 *          INVALID_DEVICE  If a valid port could not be found.
 *
 *#########################################################################*/
int
Get_Alternate_NTDS_Port (
   int device
);

/*#########################################################################
 *
 * SYNOPSIS:  Get_Normal_NTDS_Port    (application)
 *
 * DESCRIPTION:    The Get_NTDS_Port function finds the normal low
 *                 level port that is mapped to the selected device.
 *
 * PARAMETERS:
 *
 *    INPUT   device :  This parameter contains the logical unit number of
 *                      the device being used.
 *
 *    OUTPUT  NOTHING
 *
 *
 * RETURNS  The device's normal port.
 *          INVALID_DEVICE  If a valid port could not be found.
 *
 *#########################################################################*/
int
Get_Normal_NTDS_Port (
   int device
);


/*#########################################################################
 *
 * SYNOPSIS:  Display_Port_Status    (application)
 *
 * DESCRIPTION:    The Display_Port_Status function finds the statuses of
 *                 the ports which are mapped to the selected device and
 *                 displays them at the operator's console.
 *
 * PARAMETERS:
 *
 *    INPUT   device :  This parameter contains the logical unit number of
 *                      the device being used.
 *
 *    OUTPUT  NOTHING
 *
 *
 * RETURNS  Nothing.
 *
 *#########################################################################*/
//void
//Display_Port_Status (
//   int device
//);

/*#########################################################################
 *
 * SYNOPSIS:  Get_Primary_NTDS_Port    (application)
 *
 * DESCRIPTION:    The Get_Primary_NTDS_Port function finds the primary low
 *                 level port that is mapped to the selected device.
 *
 * PARAMETERS:
 *
 *    INPUT   device :  This parameter contains the logical unit number of
 *                      the device being used.
 *
 *    OUTPUT  NOTHING
 *
 *
 * RETURNS  The device's primary port.
 *          INVALID_DEVICE  If a valid port could not be found.
 *
 *#########################################################################*/
int
Get_Primary_NTDS_Port (
   int device
);

/*#########################################################################
 *
 * SYNOPSIS:  Get_Secondary_NTDS_Port    (application)
 *
 * DESCRIPTION:    The Get_Secondary_NTDS_Port function finds the secondary low
 *                 level port that is mapped to the selected device.
 *
 * PARAMETERS:
 *
 *    INPUT   device :  This parameter contains the logical unit number of
 *                      the device being used.
 *
 *    OUTPUT  NOTHING
 *
 *
 * RETURNS  The device's secondary port.
 *          INVALID_DEVICE  If a valid port could not be found.
 *
 *#########################################################################*/
int
Get_Secondary_NTDS_Port (
   int device
);

/*#########################################################################
 *
 * SYNOPSIS:  Check_NTDS_Block_Que    (protocol)
 *
 * DESCRIPTION:    The Check_NTDS_Block_Que function checks the NTDS Blocked
 *                 message queue for messages waiting to be sent.  The
 *                 number of messages waiting to be sent is returned to the
 *                 caller.
 *
 * PARAMETERS:
 *
 *    INPUT   port :     This parameter contains the logical unit number of
 *                      the port being used.
 *
 *    OUTPUT  NOTHING
 *
 *
 * RETURNS 0     = No Messages waiting
 *         Non 0 = Messages in Queue
 *         BAD_PORT_ID
 *
 *#########################################################################*/
int
Check_NTDS_Block_Que (
   int port
);

/*#########################################################################
 *
 * SYNOPSIS:  Check_NTDS_Output_Que    (protocol)
 *
 * DESCRIPTION:    The Check_NTDS_Output_Que function checks the NTDS Outputed
 *                 message queue for messages waiting to be sent.  The
 *                 number of messages waiting to be sent is returned to the
 *                 caller.
 *
 * PARAMETERS:
 *
 *    INPUT   port :     This parameter contains the logical unit number of
 *                      the port being used.
 *
 *    OUTPUT  NOTHING
 *
 *
 * RETURNS 0     = No Messages waiting
 *         Non 0 = Messages in Queue
 *         BAD_PORT_ID
 *
 *#########################################################################*/
int
Check_NTDS_Output_Que (
   int port
);

/*#########################################################################
 *
 * SYNOPSIS:  Get_NTDS_Port_Status    (application)
 *
 * DESCRIPTION:    The Get_NTDS_Port_Status function returns the current status
 *                 of a particular port.
 *
 * PARAMETERS:
 *
 *    INPUT   port :     This parameter contains the logical unit number of
 *                      the port being used.
 *
 *    OUTPUT  NOTHING
 *
 *
 * RETURNS PORT_STATUS
 *         PORT_STATUS_UNKNOWN
 *
 *#########################################################################*/
int
Get_NTDS_Port_Status (
   int port
);

/*#########################################################################
 *
 * SYNOPSIS:  NTDS_Status    (application)
 *
 * DESCRIPTION:    The NTDS_Status function returns the current status of the
 *                 interface.  It is the responsbility of the protocol
 *                 interface to keep the NTDS_Channel_Status updated to
 *                 provide a timely status.  This can be accomplished
 *                 by calling the Report_Port_Status function.
 *
 * PARAMETERS:
 *
 *    INPUT   device :     This parameter contains the logical unit number of
 *                      the device being used.
 *
 *    OUTPUT  NOTHING
 *
 *
 * RETURNS CHANNEL_STATUS
 *         CHANNEL_STATUS_UNKNOWN
 *
 *#########################################################################*/
int
NTDS_Status (
   int device
);

/*#########################################################################
 *
 * SYNOPSIS:  Get_NTDS_Status_String    (application)
 *
 * DESCRIPTION:    The Get_NTDS_Status_String function returns a pointer
 *                 to a string that describes the current status of
 *                 the interface.
 *
 * PARAMETERS:
 *
 *    INPUT   device :     This parameter contains the logical unit number of
 *                      the device being used.
 *
 *    OUTPUT  NOTHING
 *
 *
 * RETURNS Pointer to a text string describing the interface status. 
 *
 *#########################################################################*/
char *
Get_NTDS_Status_String (
   int device
);

/*#########################################################################
 *
 * SYNOPSIS:  NTDS_Status_Change  (application)
 *
 * DESCRIPTION:    The NTDS_Status function returns a change of interface
 *                 status to the caller.  The requestor will be suspended
 *                 until an interface status change occurs.  It is the
 *                 responsbility of the interface protocol to send status
 *                 changes to the application.  This can be accomplished
 *                 by calling the Report_Port_Status function.
 *
 * PARAMETERS:
 *
 *    INPUT  :
 *
 *      device :     This parameter contains the logical unit number of
 *                   the device being used.
 *
 *      mesg_ptr :    This parameter is a pointer to the variable that
 *                    will contain the latest status update.
 *
 *      time_out :    This parameter determines how long an application will
 *                    wait for a status change.
 *
 *    OUTPUT :
 *
 *         mesg_ptr :  This parameter contains the following updated
 *                     information if the timeout did not occur; otherwise
 *                     the values are zero.
 *
 *                   *status_ptr :   This parameter is a pointer to the
 *                                  variable that will contain the
 *                                  status.  The actual status that is
 *                                  transferred is dependent on the application.
 *
 *                   *time_ptr  :   This parameter is a pointer to the
 *                                  variable that will contain the time the
 *                                  status change was detected.
 *
 * RETURNS OK 
 *         QUE_REGISTER_ERR
 *         vXWorks ERROR
 *
 *#########################################################################*/
int
NTDS_Status_Change (
   int              device,
   NTDS_STATUS_MSGS *mesg_ptr,
   int              time_out
);

/*#########################################################################
 *
 * SYNOPSIS:   Deque_Output_Mesg  (protocol)
 *
 * DESCRIPTION:     This function allows a protocol task to dequeue a message
 *                from the application's output queue.  The function checks
 *                the message queue for a pending output request.  If an
 *                output request is not available, the timeout parameter is
 *                tested to determine if the caller wants to wait for an
 *                output request before returning.  If the caller elects
 *                not to wait, a S_objLib_OBJ_UNAVAILABLE status may be returned
 *                with the address field set to a NULLPTR.
 *
 *
 *        PARAMETERS:
 *
 *    INPUT   port :     This parameter contains the port id of the board
 *                    dequeuing the message buffer.
 *
 *            timeout :   This parameter determines the amount of time the
 *                       caller will wait.  The time_out can also be specified
 *                       as NO_WAIT or WAIT_FOREVER.
 *
 *             NOTE :   If an output buffer is not taken from the output queue
 *                    the caller will receive an error response and the buffer
 *                    parameters will be zeroed.
 *
 *    OUTPUT  *buffer_ptr :    This parameter contains a pointer to the message
 *                      buffer of type NTDS_OUTPUT_MSGS.
 *
 *                   The following fields are passed to the application in the
 *                   buffer parameter:
 *
 *                  *address : This field is a pointer to the message buffer to
 *                            be transferred.
 *
 *                  partition_id : This field contains the partition_id of the
 *                             buffer.  This allows the protocol task to return
 *                            the buffer to the proper partition when partitions
 *                            are being used. When malloc is being used this
 *                            field should be NULL.
 *
 *                  timeout : This field provides a timeout value for the
 *                            output task to use for the buffer transfer.  This
 *                            parameter has a range of 0..255.  The actual
 *                            time involved with this count is dependent on
 *                            the protocol implementation.  However, the value
 *                            is expected to be referenced in VxWorks ticks.
 *
 *                   length : This field contains the length of the data buffer
 *                            to be transferred. The range of this field is from
 *                            0 to 65535.
 *
 *
 *    RETURNS   OK
 *              BAD_PORT_ID
 *              VxWorks error code
 *
 *########################################################################*/
int
Deque_Output_Mesg (
   int              port,
   NTDS_OUTPUT_MSGS *buffer_ptr,
   int              timeout
);

/*#########################################################################
 *
 * SYNOPSIS:   Deque_Packed_Output_Mesg_Block  (protocol)
 *
 * DESCRIPTION:     This function allows a protocol task to dequeue a packed
 *                message block from the application's output queue.  The
 *                function checks the message queue for a pending output 
 *                request.  If an output request is not available, the timeout
 *                parameter is tested to determine if the caller wants to wait
 *                for an output request before returning.  If the caller elects
 *                not to wait, a S_objLib_OBJ_UNAVAILABLE status may be returned
 *                with the address field set to a NULLPTR.
 *
 *
 *        PARAMETERS:
 *
 *    INPUT   port :     This parameter contains the port id of the board
 *                    dequeuing the message buffer.
 *
 *            timeout :   This parameter determines the amount of time the
 *                       caller will wait.  The time_out can also be specified
 *                       as NO_WAIT or WAIT_FOREVER.
 *
 *             NOTE :   If an output buffer is not taken from the output queue
 *                    the caller will receive an error response and the buffer
 *                    parameters will be zeroed.
 *
 *    OUTPUT  *buffer_ptr :    This parameter contains a pointer to the message
 *                      buffer of type NTDS_OUTPUT_MSGS.
 *
 *                   The following fields are passed to the application in the
 *                   buffer parameter:
 *
 *                  *address : This field is a pointer to the message buffer to
 *                            be transferred.
 *
 *                  partition_id : This field contains the partition_id of the
 *                             buffer.  This allows the protocol task to return
 *                            the buffer to the proper partition when partitions
 *                            are being used. When malloc is being used this
 *                            field should be NULL.
 *
 *                  timeout : This field provides a timeout value for the
 *                            output task to use for the buffer transfer.  This
 *                            parameter has a range of 0..255.  The actual
 *                            time involved with this count is dependent on
 *                            the protocol implementation.  However, the value
 *                            is expected to be referenced in VxWorks ticks.
 *
 *                   length : This field contains the length of the data buffer
 *                            to be transferred. The range of this field is from
 *                            0 to 65535.
 *
 *
 *    RETURNS   OK
 *              BAD_PORT_ID
 *              VxWorks error code
 *
 *########################################################################*/
int
Deque_Packed_Output_Mesg_Block (
   int              port,
   NTDS_OUTPUT_MSGS *buffer_ptr,
   int              timeout
);

/*##########################################################################
 *
 * SYNOPSIS:       Deque_Output_Signal   (protocol)
 *
 * DESCRIPTION:    This function returns a special event signal from the
 *                 selected application.  The caller determines if it will wait for
 *                 a signal response by setting the time_out variable.
 *
 *                    It is expected that the application will place
 *                 special event signals in the queue by calling the
 *                 Send_NTDS_Signal function.
 *
 * PARAMETERS:
 *
 *    INPUT :
 *
 *           port :   This parameter determines the queue from which the
 *                    signal messages will be taken.
 *
 *       mesg_ptr :   A pointer the variable that will hold the updated
 *                    signal information.
 *
 *       time_out :   This parameter determines how long the caller will
 *                    wait for a message to be received before declaring
 *                    an input failure.  The time_out can also be specified
 *                    as NO_WAIT or WAIT_FOREVER.
 *
 *    OUTPUT :
 *
 *         mesg_ptr :  This parameter contains the following updated
 *                     information if the timeout did not occur; otherwise
 *                     the values are zero.
 *
 *                   *event_ptr :   This parameter is a pointer to the
 *                                  variable that will contain the signal
 *                                  status.  The actual status that is
 *                                  transferred is dependent on the application.
 *
 *                   *time_ptr  :   This parameter is a pointer to the
 *                                  variable that will contain the time the
 *                                  signal status was detected.
 *
 * RETURNS   OK
 *           BAD_PORT_ID
 *           VxWorks error status
 *
 * #########################################################################*/
int
Deque_Output_Signal (
   int              port,
   NTDS_SIGNAL_MSGS *mesg_ptr,
   int              timeout
);

/*#########################################################################
 *
 * SYNOPSIS:   Queue_Input_Mesg    (protocol)
 *
 * DESCRIPTION:     This function queues a message to an application's input
 *                queue.  This function searches the message list for a queue
 *                that matches the message type received in the buffer.  If a
 *                queue is found, the message buffer is placed in that queue.
 *                If a queue is not found, the function returns to the caller
 *                with an error status.
 *
 * PARAMETERS:
 *
 *    INPUT   port :    This parameter contains the port id of the board queuing
 *                    the message buffer.
 *
 *            *buffer_ptr :    This parameter contains a pointer to the message
 *                      buffer of type NIO_MESG.
 *
 *      The following fields are passed to the application in the
 *      buffer parameter:
 *
 *                 *address : This field is a pointer to the message buffer to
 *                            be transferred.
 *
 *                 time : Time stamp of received message.
 *
 *                 length : This field contains the length of the data buffer
 *                            to be transferred. The range of this field is from
 *                            0 to 65535.
 *
 *              message_type :  This parameter contains the message type of the
 *                              buffer being queued.
 *
 *    free_buffer  : This parameter determines if the buffer should be
 *        released to the memory pool.  It is the responsibility of the
 *        application to coordinate buffer releasing with the NTDS Comm
 *        package.  (See Recv_NTDS_Mesg)
 *
 *    OUTPUT  NOTHING
 *
 *    RETURNS   OK
 *              COULD_NOT_QUE_MESG
 *              BAD_PORT_ID
 *              BUFFER_PART_ERR
 *              MT_REGISTER_ERR
 *              QUE_NOT_FOUND
 *              VxWorks error code
 *
 *########################################################################*/
int
Queue_Input_Mesg (
   int            port,
   NIO_MESG     * buffer_ptr,
   unsigned int   mesg_type,
   char           free_buffer
);

/*#########################################################################
 *
 * SYNOPSIS:   Queue_Remote_Input_Mesg    (protocol)
 *
 * DESCRIPTION:   This function queues a message to an ethernet socket output
 *                queue.  The message will be packed and transmitted to the
 *                CEP where the Applcation's parser function will be called
 *                to deliver the message to the appropriate input queue.
 *                The socket ID is associated with the Device ID via a table.
 *
 * PARAMETERS:
 *
 *    INPUT   port :    This parameter contains the port id of the board queuing
 *                      the message buffer.
 *
 *            *buffer_ptr :  This parameter contains a pointer to the message
 *                           buffer of type NIO_MESG.
 *
 *           free_buffer  : This parameter determines if the buffer should be
 *                          released to the memory pool.  It is the
 *                          responsibility of the application to coordinate
 *                          buffer releasing with the NTDS Comm package. 
 *                          (See Recv_NTDS_Mesg)
 *
 *    OUTPUT  NOTHING
 *
 *    RETURNS   OK
 *              COULD_NOT_QUE_MESG
 *              BAD_PORT_ID
 *              BUFFER_PART_ERR
 *              MT_REGISTER_ERR
 *              QUE_NOT_FOUND
 *              VxWorks error code
 *
 * ########################################################################*/
int
Queue_Remote_Input_Mesg ( 
   int          port,
   NIO_MESG     *buffer,
   char         free_buffer
);

/*#########################################################################
 *
 * SYNOPSIS: Parse_Remote_Port_Mesg  (protocol)
 *
 * DESCRIPTION: This function performs a callback to a port's protocol
 *             parse function in order to queue a received input message.
 *             It is  the responsibility of the protocol to properly
 *             parse the input data.  This function provides a sanitary
 *             method of accessing that function.
 *
 *
 * PARAMETERS:
 *
 *     INPUT  port :  This parameter contains the logical unit number of
 *                      of the port for which the device ID is requested.
 *
 *    OUTPUT  NOTHING
 *
 *    RETURNS Result of the parse 
 *            OK if NO parse function is available
 *
 *
 * #########################################################################*/
int
Parse_Remote_Port_Mesg (
   int      port,
   int      data_src,
   NIO_MESG *packet
);

/*#########################################################################
 *
 * SYNOPSIS:  Get_Device_Id    (protocol)
 *
 * DESCRIPTION:    The Get_Device_Id function finds the current device 
 *                 that is mapped to the selected port.
 *
 * PARAMETERS:
 *
 *    INPUT   port :  This parameter contains the logical unit number of
 *                    the port being used.
 *
 *    OUTPUT  NOTHING
 *
 *
 * RETURNS  The device assigned to the port.
 *          0 if no device is found.
 *
 *#########################################################################*/
int
Get_Device_Id (
   int port
);

/*#########################################################################
 *
 * SYNOPSIS:  Report_Port_Error   (protocol)
 *
 * DESCRIPTION:      This function routes an error_code to the application's
 *                 error queue.  The application is expected to remove the
 *                 error entry from the queue by calling the Recv_NTDS_Error
 *                 function.
 *
 * PARAMETERS:
 *
 *     INPUT :
 *
 *           port :    This variable determines which port's error queue
 *                     will receive the error code.
 *
 *            mesg_ptr :   A structure that contains the following information:
 *
 *                     error_code :    This parameter contains the error that
 *                                     will be posted to the queue.
 *
 *                           time :    This parameter contains the time that
 *                                     the error occurred.
 *
 *     OUTPUT     NOTHING
 *
 *     RETURNS  OK
 *              BAD_PORT_ID
 *              vxWorks error code
 *
 *#########################################################################*/
int
Report_Port_Error (
   int             port,
   NTDS_ERROR_MSGS *mesg_ptr
);

/*#########################################################################
 *
 * SYNOPSIS:  Report_Port_Signal    (protocol)
 *
 * DESCRIPTION:       This function routes a signal code to the appliation's
 *                 signal queue.  The application is expected to remove the
 *                 signal entry by calling the Recv_NTDS_Signal function.
 *
 * PARAMETERS:
 *
 *     INPUT  port :   This variable determines which port's signal queue
 *                   will receive the signal code.
 *
 *            mesg_ptr :   A structure that contains the following information:
 *
 *                   signal_code : This parameter contains the signal that
 *                                 will be posted to the queue.
 *
 *                   time :  This parameter contains the time that the signal
 *                           occurred.
 *
 *     OUTPUT     NOTHING
 *
 *     RETURNS  OK
 *              BAD_PORT_ID
 *              vxWorks error code
 *
 *#########################################################################*/

int
Report_Port_Signal (
   int               port,
   NTDS_SIGNAL_MSGS  *mesg_ptr
);

/*#########################################################################
 *
 * SYNOPSIS:  Report_Port_Status    (protocol)
 *
 * DESCRIPTION:      This function saves the interface status of a port for
 *                 the application to use.
 *
 * PARAMETERS:
 *
 *    INPUT   port :    This parameter contains the port id of the board
 *                   reporting a status change.
 *
 *            status :  This parameter contains the new interface status.
 *
 *    OUTPUT  NOTHING
 *
 * RETURNS OK or
 *         BAD_PORT_ID
 *         vxWorks ERROR code.
 *
 *#########################################################################*/
int
Report_Port_Status (
   int        port,
   int        readiness
);

/*#########################################################################
 *
 * SYNOPSIS:  Get_Port_Status    (protocol)
 *
 * DESCRIPTION:      This function saves the interface status of a port for
 *                 the application to use.
 *
 * PARAMETERS:
 *
 *    INPUT   port :    This parameter contains the port id of the board
 *                   reporting a status change.
 *
 *            status :  This parameter contains the new interface status.
 *
 *    OUTPUT  NOTHING
 *
 * RETURNS Port status 
 *         BAD_PORT_ID
 *
 *#########################################################################*/
int
Get_Port_Status (
   int port
);

/*#########################################################################
 *
 * SYNOPSIS:  Get_Port_Status_String    (protocol)
 *
 * DESCRIPTION:    The Get_Port_Status_String function returns a pointer
 *                 to a string that describes the current status of
 *                 the interface at the port level.
 *
 * PARAMETERS:
 *
 *    INPUT   port :     This parameter contains the port number of
 *                      the channel being used.
 *
 *    OUTPUT  NOTHING
 *
 *
 * RETURNS Pointer to a text string describing the interface status. 
 *
 *#########################################################################*/
char *
Get_Port_Status_String (
   int port
);

/*#########################################################################
 *
 * SYNOPSIS:  Check_For_NTDS_Boards
 *
 * DESCRIPTION:      This function queries the VME bus for a maximum of two
 *              interface cards.  If the first board and only the first is
 *              found a status of 1 is returned.  If the second board and
 *              only the second board is found, a status of 2 is returned.
 *              If both boards are found, a status of 3 is returned.  Any
 *              other condition results in a 0 being returned.
 *
 * PARAMETERS:
 *
 *    INPUT   address_1 :    This parameter is the first board address.
 *
 *            address_2 :    This parameter is the second board address.
 *
 *    OUTPUT  NOTHING
 *
 * RETURNS 0 NO BOARDS FOUND
 *         1 FIRST BOARD FOUND
 *         2 SECOND BOARD FOUND
 *         3 BOTH BOARDS FOUND
 *
 *#########################################################################*/
int
Check_For_NTDS_Boards (
   unsigned int address_1,
   unsigned int address_2
);

/*#########################################################################
 *
 * SYNOPSIS:  Find_NTDS_Boards 
 *
 * DESCRIPTION:      This function tests a list of possible NTDS card
 *                 addresses that may be available. Each possible address is
 *                 tested until two valid boards are found or the list is
 *                 exhausted, which ever comes first.
 *
 * PARAMETERS:
 *
 *    INPUT   address_list :  This parameter is a pointer to a list of
 *                            addresses to be tested for validity.
 *
 *             first_result :  This parameter contains a pointer to store the
 *                             information on the first board found.
 *
 *             second_result :  This parameter contains a pointer to store the
 *                              information on the second board found.
 *
 *    OUTPUT   first_result :  This parameter updates the pointer values
 *                             storing information on the first board found.
 *
 *             second_result :  This parameter updates the pointer values
 *                              storing information on the second board found.
 *
 *
 * RETURNS 0 If no boards are found
 *         1 If 1 board is found
 *         2 If 2 boards are found
 *
 *#########################################################################*/
int
Find_NTDS_Boards (
   unsigned int *address_ptr,
   NTDS_BOARD_VENDOR *match1,
   NTDS_BOARD_VENDOR *match2
);

/*#########################################################################
 *
 *        SYNOPSIS:        Find_NTDS_Mesg
 *
 *        DESCRIPTION:   This function finds the message type and buffer size
 *                of a message.  The message type and buffer size are
 *                expected to be in the first word pointed to by the
 *                buffer pointer.
 *
 *                This function will also determine if the next message address
 *                is really the next message or the end of the input buffer.
 *                This is to support those interfaces that want to pass the raw
 *                buffer to the application.  The type of message parsing
 *                that is performed is determined when the device is
 *                configured.
 *
 *                Find_NTDS_Mesg receives a mask to determine the bits
 *                to save for both the message type and size of the
 *                buffer.  Also included are variables used to determine
 *                how far to shift the data to right justify it.
 *
 *                This function returns the message type, size of the
 *                buffer, and the next buffer address.
 *
 *
 *        PARAMETERS:
 *
 *    INPUT
 *             port  :  This parameter determines the port that is attempting
 *                      to sort out a message.  This parameter is required
 *                      to determine if raw buffers or messages are being
 *                      computed.
 *
 *             mesg_ptr :  This parameter is a pointer to a structure
 *                         that has the following characteristics.
 *
 *             *buffer_address :  This parameter is a pointer to a pointer
 *                                that points to the first word of the mesg
 *                                buffer.
 *
 *             word_size :  This parameter determines the word width of the
 *                          buffer being used. The two options are WORD_32
 *                          and WORD_16.
 *
 *             msg_mask  :  This parameter contains the mask to be applied
 *                          to the first word of the message to get the
 *                          message type.
 *
 *             size_mask :  This parameter contains the mask to be applied
 *                          to the first word of the message to get the
 *                          size of the buffer.
 *
 *             msg_shift :  This parameter contains the number of shifts
 *                          required to right justify the message type.
 *
 *             size_shift : This parameter contains the number of shifts
 *                          required to right justify the message size.
 *
 *       num_of_words_type: This parameter determines if an extra word will
 *                          be added to the message size and the next message
 *                          address.  If the parameter is set to
 *                          NW_WORDS_DOES_NOT_INCLUDE_HEADER_WORD, both values
 *                          will be incremented appropriately.  If the
 *                          parameter is set to NW_WORDS_INCLUDES_HEADER_WORD,
 *                          the values will be returned as decoded.
 *
 *       buffer_length:     This parameter determines the length of the raw
 *                          input buffer.  This value is usually extracted from
 *                          the input packet's tfr_count parameter.
 *
 *    OUTPUT  *test_patt :  This parameter is updated to point to the
 *                          test pattern following the message.
 *
 *             *buffer_size : This parameter is a pointer that will contain
 *                            the size of the message.
 *
 *             *msg_type    : This parameter is a pointer that will contain
 *                            the message type of the message.
 *
 *             *next_msg_address : This parameter is a pointer that will
 *                                 contain the address of the next message.
 *
 *    RETURNS   NOTHING
 *
 *########################################################################*/
void
Find_NTDS_Mesg (
   int port,
   MESG_BLOCK *mesg_ptr
 
);

/*#########################################################################
 *
 * SYNOPSIS:  Get_NTDS_Partition
 *
 * DESCRIPTION:     This function gets a block of memory that can be accessed by
 *               across the VME bus.  The memory block is taken from the
 *               NTDS buffer pool.  This memory block is converted to a
 *               partition that the caller can used to transfer data to or from
 *               the NIO interface board.  The memory buffer is addressable
 *               by off board processors. (Mapped to VME memory).
 *
 * PARAMETERS:
 *
 *   INPUT : size     This parameter determines the number of bytes that will be
 *                    allocated.
 *
 *
 * OUTPUT :  NONE
 *
 * RETURNS : partition  This parameter returns the partition id of the newly
 *                    created partition.  If the partition id is NULL, a
 *                    partition was not created.
 *
 * #########################################################################*/
PART_ID
Get_NTDS_Partition (
  unsigned int size
);

/*#########################################################################
 *
 * SYNOPSIS:  Get_NTDS_Buffer
 *
 * DESCRIPTION:     This function gets a block of memory that can be accessed by
 *               the NTDS interface board.  The memory buffer is addressable
 *               by off board processors. (Mapped to VME memory).
 *
 * PARAMETERS:
 *
 *   INPUT : size     This parameter determines the number of bytes that will be
 *                    allocated.
 *
 *                    This parameter is a pointer to the variable that will
 *                    contain the partition id of the buffer.
 *
 *  OUTPUT : partition_id  This parameter will contain the new paritition id.
 *
 * RETURNS : *address The base address of the newly received buffer is returned.
 *                    If the buffer address is NULL, a buffer was not allocated.
 *
 * #########################################################################*/
char *
Get_NTDS_Buffer (
  unsigned int size,
  PART_ID      *partition_id
);

/*#########################################################################
 *
 * SYNOPSIS:   Free_NTDS_Msg_Buffer
 *
 *  DESCRIPTION:   This function releases a buffer back to the buffer pool.
 *        The partition id determines the buffer pool that will receive the
 *        memory block.  If the partition id is NULL, the memory block will
 *        be returned using a free block, implying the memory was gotten by
 *        using a malloc command.  If the partition id is not NULL, a
 *        memPartFree call.
 *
 *        PARAMETERS:
 *
 *      INPUT:
 *
 *          partition_id : The identifier determining where the memory
 *                         block was taken.
 *
 *          *address_ptr :  A pointer to the memory block being freed.
 *
 *      OUTPUT : NONE
 *
 *    RETURNS   OK
 *              vxWorks error code
 *
 *########################################################################*/
int
Free_NTDS_Msg_Buffer (
 PART_ID partition_id,
 char    *address_ptr
);

/*#########################################################################
 *
 * SYNOPSIS:   NTDS_Msgs
 *
 *  DESCRIPTION:   This function displays a count of all the data messages
 *        that have been received for application processing.
 *
 *        PARAMETERS:
 *
 *      INPUT : NONE
 *
 *      OUTPUT : NONE
 *
 *    RETURNS   NOTHING
 *
 *########################################################################*/
void
NTDS_Msgs (
   void
);

/*#####################################################################
 *
 * SYNOPSIS:   NTDS_Ques
 *
 *  DESCRIPTION:   This function displays a count of all the data 
 *               messages that have been received for application 
 *               processing.
 *
 *        PARAMETERS:
 *
 *      INPUT : NONE
 *
 *      OUTPUT : NONE
 *
 *    RETURNS   NOTHING
 *
 *########################################################################*/
void
NTDS_Ques (
   void
);

/*#####################################################################
 *
 * SYNOPSIS:   Test_NTDS_Card
 *
 *  DESCRIPTION:   This function allows a person to configure the NTDS
 *               package to communicate with a NTDS card.  The caller is
 *               queried for the appropriate parameters before configuration.
 *               The caller must also provide a valid NTDS card address before
 *               the configuration will continue.
 *
 *  PARAMETERS:
 *
 *      INPUT : NONE
 *
 *      OUTPUT : NONE
 *
 *    RETURNS   NOTHING
 *
 *########################################################################*/
void
Test_NTDS_Card (
   void
);

/*#####################################################################
 *
 * SYNOPSIS:   Set_NTDS_Gate_Revision_Info
 *
 *  DESCRIPTION:   This function is used primarily by the enet client
 *                 in order to report the NTDS Gate's revision information.
 *                 The enet server down in the NTDS Gate board sends a 
 *                 structure called SATELLITE_CONFIGURATION_HDR up to the
 *                 enet client which is in the application's board.  The 
 *                 enet client calls this function which stores the revision
 *                 information in the "NTDS_Gate_Revision_Info" string.
 *
 *  PARAMETERS:
 *
 *      INPUT : revision_info - the revision information string.
 *
 *      OUTPUT : NTDS_Gate_Revision_Info is set to the input string.
 *
 *    RETURNS   NOTHING
 *
 *########################################################################*/
void Set_NTDS_Gate_Revision_Info(
  char* revision_info
);


/*#####################################################################
 *
 * SYNOPSIS:   Get_NTDS_Gate_Revision_Info
 *
 *  DESCRIPTION:    This function is used by anyone needing the NTDS Gate's
 *                 revision information.
 *                 The enet server down in the NTDS Gate board sends a 
 *                 structure called SATELLITE_CONFIGURATION_HDR up to the
 *                 enet client which is in the application's board.  The 
 *                 enet client calls the "Set_NTDS_Gate_Revision_Info"
 *                 function which stores the revision information in the 
 *                "NTDS_Gate_Revision_Info" string.
 *
 *  PARAMETERS:
 *
 *      INPUT : NONE
 *
 *      OUTPUT : NONE
 *
 *    RETURNS   The NTDS Gate revision information string.
 *
 *########################################################################*/
char* Get_NTDS_Gate_Revision_Info(
  void
);


/*#####################################################################
 *
 * SYNOPSIS:   Get_Board_Driver_Type
 *
 *  DESCRIPTION:    This function returns the NTDS board driver type.
 *                  Sometimes apps need to know what kind of NTDS board
 *                  they're talking to.  A call to this function will
 *                  return that information.
 *
 *  PARAMETERS:
 *
 *      INPUT : port - port number associated with the NTDS board of interest.
 *
 *      OUTPUT : NONE
 *
 *    RETURNS   the driver-type of the NTDS board associated with the input port.
 *
 *########################################################################*/
unsigned int Get_Board_Driver_Type(int Port);


/*#####################################################################
 *
 * SYNOPSIS:   Hook_Task_Switching
 *
 *  DESCRIPTION:    This function turns on the capture of task swaps to
 *                  the NTDS Trace buffer.  The user must supply the port
 *                  to which the trace data is to be captured for.
 *
 *  PARAMETERS:
 *
 *      INPUT : port - port for which Tracing of task swaps should be captured.
 *
 *      OUTPUT : Task_Switching_Port.
 *
 *    RETURNS   NONE.
 *
 *########################################################################*/
void Hook_Task_Switching(int port);

#ifdef __cplusplus
}



#endif // #define NTDS_COMMON_KWR__H



