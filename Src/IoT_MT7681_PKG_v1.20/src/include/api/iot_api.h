#ifndef _IOT_API_H_
#define _IOT_API_H_

#include "config.h"
#include "list.h"
#include "cnm_timer.h"
#include "flash_map.h"
#include "stddef.h"
#include "eeprom.h"
#include "rtmp_dot11.h"
#include "rtmp_general_pub.h"
#include "dot11i_wpa.h"
#include "iot_custom.h"
#include "bmd.h"


/******************************************************************************
* MODULE NAME:     iot_api.h
* PROJECT CODE:    __MT7681__
* DESCRIPTION:     
* DESIGNER:        
* DATE:            Jan 2014
*
* SOURCE CONTROL:
*
* LICENSE:
*     This source code is copyright (c) 2014 Mediatek. Inc.
*     All rights reserved.
*
* REVISION     HISTORY:
*   V0.0.1     Jan 2014    - Initial Version V0.0.1
*
*
* SOURCE:
* ISSUES:
*    First Implementation.
* NOTES TO USERS:
*
******************************************************************************/
#ifndef BW_20
#define BW_20		0
#endif
#ifndef BW_40
#define BW_40		1
#endif

#define BEACON_LOST_TIME			(20*1000)	/* unit: msec */
#define AUTH_TIMEOUT				(300)		/* unit: msec */
#define NULL_FRAME_TIMEOUT			(10*1000)	/* unit: msec */
#define BEACON_INTERVAL_TIME		(100)	    /* unit: msec */

#define SM_MAX_SCAN_TIMEOUT_COUNT	(10)		/* unit: s  */
#define SM_MAX_SMNT_TIMEOUT_COUNT	(10)		/* unit: cycles    *(SmartConnection maxchanlnum)  */

#define FOUR_WAY_HS_TIMEOUT			(10*1000)   /* unit: msec */
#define MAX_VALID_CHECK_COUNT   	(1)			/* unit: conter, start from 0*/

//#define DLS_TIMEOUT                 1200      /* unit: msec */
//#define ASSOC_TIMEOUT               300       /* unit: msec */
//#define JOIN_TIMEOUT                2000      /* unit: msec */
//#define CW_MIN_IN_BITS              4         /* actual CwMin = 2^CW_MIN_IN_BITS - 1 */


#define MAC_ADDR_LEN			6
#define MAC_IP_LEN				4
#define MAC_DOMAIN_NAME_LEN		(128)

#define DESC_MAX_LEN			32
#define IOT_MAGIC_NUMBER		0x76814350
#define DEFAULT_SESSION_ID		0xFFFFFFFF
#define PASSWORD_MAX_LEN 		4
#define UART_MAX_DATALEN 		1060-36-28//PKTQU1_SINGLE_BUFFER_SIZE-36-28
#define IOT_BUFFER_LEN 			(256)

#define CP_HDR_LEN sizeof(IoTCtrlProtocolHeader)
#define CP_DATA_HDR_LEN sizeof(DataHeader)


/*type define*/
//typedef unsigned int UINT_32;
//typedef unsigned short UINT_16;
typedef unsigned char UINT_8;
typedef char TYPE;

/* Reason code definitions */
#define REASON_RESERVED                 0
#define REASON_UNSPECIFY                1
#define REASON_NO_LONGER_VALID          2
#define REASON_DEAUTH_STA_LEAVING       3
#define REASON_DISASSOC_INACTIVE        4
#define REASON_DISASSPC_AP_UNABLE       5
#define REASON_CLS2ERR                  6
#define REASON_CLS3ERR                  7
#define REASON_DISASSOC_STA_LEAVING     8
#define REASON_STA_REQ_ASSOC_NOT_AUTH   9
#define REASON_INVALID_IE               13
#define REASON_MIC_FAILURE              14
#define REASON_4_WAY_TIMEOUT            15
#define REASON_GROUP_KEY_HS_TIMEOUT     16
#define REASON_IE_DIFFERENT             17
#define REASON_MCIPHER_NOT_VALID        18
#define REASON_UCIPHER_NOT_VALID        19
#define REASON_AKMP_NOT_VALID           20
#define REASON_UNSUPPORT_RSNE_VER       21
#define REASON_INVALID_RSNE_CAP         22
#define REASON_8021X_AUTH_FAIL          23
#define REASON_CIPHER_SUITE_REJECTED    24
#define REASON_DECLINED                 37
#define REASON_QOS_UNSPECIFY              32
#define REASON_QOS_LACK_BANDWIDTH         33
#define REASON_POOR_CHANNEL_CONDITION     34
#define REASON_QOS_OUTSIDE_TXOP_LIMITION  35
#define REASON_QOS_QSTA_LEAVING_QBSS      36
#define REASON_QOS_UNWANTED_MECHANISM     37
#define REASON_QOS_MECH_SETUP_REQUIRED    38
#define REASON_QOS_REQUEST_TIMEOUT        39
#define REASON_QOS_CIPHER_NOT_SUPPORT     45
#define REASON_FT_INVALID_FTIE			  55

/******************************************************************************
 * UART MACRO & STRUCTURE
 ******************************************************************************/
#define     UART_BAUD_AUTO          0
#define     UART_BAUD_75            75
#define     UART_BAUD_150           150
#define     UART_BAUD_300           300
#define     UART_BAUD_600           600
#define     UART_BAUD_1200          1200
#define     UART_BAUD_2400          2400
#define     UART_BAUD_4800          4800
#define     UART_BAUD_7200          7200
#define     UART_BAUD_9600          9600
#define     UART_BAUD_14400         14400
#define     UART_BAUD_19200         19200
#define     UART_BAUD_28800         28800
#define     UART_BAUD_33900         33900
#define     UART_BAUD_38400         38400
#define     UART_BAUD_57600         57600
#define     UART_BAUD_115200        115200
#define     UART_BAUD_230400        230400
#define     UART_BAUD_460800        460800
#define     UART_BAUD_921600        921600
#define     UART_BAUD_3200000       3200000

typedef enum {
      len_5=5,
      len_6,
      len_7,
      len_8
} UART_bitsPerCharacter;

typedef enum {
      sb_1=1,
      sb_2,
      sb_1_5
} UART_stopBits;

typedef enum {
      pa_none=0,
      pa_odd,
      pa_even,
      pa_space
} UART_parity;

#if (UART_INTERRUPT == 1)
//buffer length for uart rx isr buffer whose data is moved from UART HW RX FIFO
#define    UARTRX_RING1_LEN    64      

//buffer length for uart rx high level buffer whose data is moved from uart rx isr buffer
#define    UARTRX_RING2_LEN    1024   
#define    NUM_DESCS           4

/*
 * 2014/05/13,terrence
 * struct to descrypt the packet in ring buffer
 * we just need to know the packet number and their lengh in sequence
 */
typedef struct {
    UINT8   num_desc;              //packet number in ring buffer

    //be careful!!!,the length is in sequence with index[0,num_desc-1] which mapping the equence in rx ring
    UINT16  pkt_len[NUM_DESCS];   
} PKT_DESC;
#endif


/******************************************************************************
 * uIP MACRO & STRUCTURE
 ******************************************************************************/
struct GNU_PACKED ipv4hdr {
	
	UINT8	version_ihl;
	UINT8	tos;
	UINT16	tot_len;
	UINT16	id;
	UINT16	frag_off;
	UINT8	ttl;
	UINT8	protocol;
	UINT8	check[2];
	UINT32	saddr;
	UINT32	daddr;
	/*The options start here. */
};

struct GNU_PACKED udphdr {
	UINT16	source_port;
	UINT16	dest_port;
	UINT16	len;
	UINT8	check[2];
};

struct GNU_PACKED udppseudohdr {
	UINT32	saddr;
	UINT32	daddr;
	UINT8 ttl;
	UINT8 protocol;
	UINT16 udpdatalen;
	
	UINT16	source_port;
	UINT16	dest_port;
	UINT16	len;
	UINT8	check[2];
};


typedef struct _IOT_CUST_OP_ {
	/*  Customerization access related callback functions */
	VOID (*IoTCustPreInit)(VOID);
	VOID (*IoTCustInit)(VOID);
	VOID (*IoTCustWifiSMInit)(VOID);
	VOID (*IoTCustWifiSMSmnt)(VOID);
	VOID (*IoTCustWifiSMConnect)(VOID);
	//VOID (*IoTCustWifiRxHandler)(PHEADER_802_11 pHeader, USHORT DataSize);  /*DataSize = MPDUtotalByteCount    (not include FCS)*/
	VOID (*IoTCustSMNTStaChgInit)(VOID);
	VOID (*IoTCustSubTask1)(VOID);
}IOT_CUST_OP;


typedef struct GNU_PACKED _IOT_CUST_CFG_{
	TIMER_T   custTimer0;
} IOT_CUST_TIMER;


typedef struct GNU_PACKED _IOT_COMMON_CFG_{
	UINT8	BootFWIdx;
	UINT8	RecovModeStatus;
	UINT8	IOMode;

	UINT32	UART_Baudrate;
	UINT8	UART_DataBits;
	UINT8	UART_Parity;
	UINT8	UART_StopBits;

	UINT8	TCPUDP_CS;
	UINT16	IoT_TCP_Srv_Port;
	UINT16	Local_TCP_Srv_Port;
	UINT16	IoT_UDP_Srv_Port;
	UINT16	Local_UDP_Srv_Port;

	UINT8	Use_DHCP;
	UINT8	STATIC_IP[MAC_IP_LEN];
	UINT8	SubnetMask_IP[MAC_IP_LEN];
	UINT8	DNS_IP[MAC_IP_LEN];
	UINT8	GateWay_IP[MAC_IP_LEN];
	UINT8	IoT_ServeIP[MAC_IP_LEN];
	//UINT8	IoT_ServeDomain[MAC_DOMAIN_NAME_LEN];
	
	UINT8	CmdPWD[PASSWORD_MAX_LEN];
}IOT_COM_CFG;


typedef struct GNU_PACKED _IOT_USER_CFG_{
	UCHAR VendorName[FLASH_USR_CFG_VENDOR_NAME_LEN];
	UCHAR ProductType[FLASH_USR_CFG_PRODUCT_TYPE_LEN];
	UCHAR ProductName[FLASH_USR_CFG_PRODUCT_NAME_LEN];
}IOT_USR_CFG;


typedef struct _IOT_ADAPTER{
	IOT_COM_CFG		ComCfg;
	IOT_USR_CFG		UsrCfg;
	UINT8 			flash_rw_buf[RAM_RW_BUF_SIZE];
}IOT_ADAPTER;


/******************************************************************************
 * DATA PARSER  MACRO & STRUCTURE
 ******************************************************************************/
/*protocol related define*/
#ifdef RT_BIG_ENDIAN
typedef	union _IOT_CTRL_SUB_HDR_STRUC {
	struct {
		UINT_16 SubType:8;				  //subtype
		UINT_16 Type:4; 				  //command type. 0: management command 1: function command
		UINT_16 Flag:4; 				  //reserved
	} field;
	UINT_16 word;
} IOT_CTRL_SUB_HDR_STRUC;
#else
typedef	union _IOT_CTRL_SUB_HDR_STRUC {
	struct {
		UINT_16 Flag:4; 				  //reserved
		UINT_16 Type:4; 				  //command type. 0: management command 1: function command
		UINT_16 SubType:8;				  //subtype
	} field;
	UINT_16 word;
} IOT_CTRL_SUB_HDR_STRUC;
#endif

typedef struct GNU_PACKED t_IoTCtrlProtocolHeader
{
	UINT_32 Magic;                    //protocol magic number
	UINT_8 ReceiveMAC[MAC_ADDR_LEN];  //receive mac address
	UINT_8 SendMAC[MAC_ADDR_LEN];     //sender mac address
	UINT_32 SessionID;                //reserved
	UINT_16 Sequence;                 //sequence number
	IOT_CTRL_SUB_HDR_STRUC SubHdr;
	//UINT_16 Flag:4;                   //reserved
	//UINT_16 Type:4;                   //command type. 0: management command 1: function command
	//UINT_16 SubType:8;	              //subtype
} IoTCtrlProtocolHeader;

typedef enum t_CommandType
{
	MANAGEMENT,
	FUNCTION,
	TYPE_MAX
}CommandType;

typedef enum t_ManagementCommand
{
	QUERY_CAPAB_REQUEST = 1,
	QUERY_CAPAB_RESPONSE,
	CONTROL_CLIENT_OFFLINE_REQUEST,
	CONTROL_CLIENT_OFFLINE_RESPONSE,
	CONTROL_PASSWORD_SET_REQUEST,
	CONTROL_PASSWORD_SET_RESPONSE,
	CONTROL_PASSWORD_SET_CONFIRM,
	MANAGEMENT_COMMAND_MAX
}ManagementCommand;

typedef enum t_FunctionCommand
{
	GPIO_SET_REQUEST = 1,
	GPIO_SET_RESPONSE,
	GPIO_GET_REQUEST,
	GPIO_GET_RESPONSE,
	UART_SET_REQUEST,
	UART_SET_RESPONSE,
	UART_GET_REQUEST,
	UART_GET_RESPONSE,
	PWM_SET_REQUEST,
	PWM_SET_RESPONSE,
	PWM_GET_REQUEST,
	PWM_GET_RESPONSE,
	FUNCTION_COMMAND_MAX
}FunctionCommand;

typedef enum t_DataType
{
	STATUS,
	CLIENT_CAPABILITY,
	UART_INFORMATION,
	GPIO_INFORMATION,
	PWM_INFORMATION,
	CONTROL_PASSWORD
}DataType;

/*Control Data information*/
typedef struct GNU_PACKED t_DataHeader
{
	UINT_16 Type;
	UINT_16 Length;
}DataHeader;

typedef struct GNU_PACKED t_Status
{
	UINT_8 StatusCode;
}Status;


typedef struct GNU_PACKED t_UART_Information
{
	UINT_8 Data[UART_MAX_DATALEN];
}UART_Information;



typedef struct GNU_PACKED t_GPIO_Information
{
	UINT_32 GPIO_List;
    UINT_32 GPIO_Value;
}GPIO_Information;

typedef struct GNU_PACKED t_PWM_Information
{
	UINT_16 RedLevel;
	UINT_16 GreenLevel;
	UINT_16 BlueLevel;
}PWM_Information;

typedef struct GNU_PACKED t_ClientCapability
{
	UINT_16 VendorNameLen;
	UINT_8 VendorName[FLASH_USR_CFG_VENDOR_NAME_LEN];
	UINT_16 ProductTypeLen;
	UINT_8 ProductType[FLASH_USR_CFG_PRODUCT_TYPE_LEN];
	UINT_16 ProductNameLen;
	UINT_8 ProductName[FLASH_USR_CFG_PRODUCT_NAME_LEN];
}ClientCapability;


typedef struct GNU_PACKED t_IoTHardwareRresource
{
	UINT_32 GPIO_Rresource;	/*bitmap for GPIO status:   bit[n] = 1  means GPIO[n] enabled*/
	UINT_32 UART_Rresource;	/*not used now , for extension*/
	UINT_32 PWM_Rresource;	/*not used now , for extension*/
	INT_8 GPIO_Count;		/*not used now , for extension*/
	INT_8 UART_Count;		/*not used now , for extension*/
	INT_8 PWM_Count;		/*not used now , for extension*/
	
} IoTHardwareRresource;
//#define UART_SWITCH_TO_PWM

typedef struct GNU_PACKED t_IoTHardwareStatus
{
	
	UINT_16 RedLevel;
	UINT_16 GreenLevel;
	UINT_16 BlueLevel;
	
}IoTHardwareStatus;

typedef struct GNU_PACKED t_IoTPacketInfo
{
	UINT_32 SessionID;
	UINT_16 Sequence;
	UCHAR ReceiveMAC[6];
	UCHAR SendMAC[6];
	
} IoTPacketInfo;

struct cp_app_conn {
	UINT8 soket_num;
	UINT16 prev_seq;
};

/******************************************************************************
 * Wifi STATE MACHINE  MACRO & STRUCTURE
 ******************************************************************************/
extern UCHAR gCurrentAddress[MAC_ADDR_LEN];	

#define MAX_TCP_DATA		16
#define MAX_IP_STRING_LEN	16
#define MAX_SSID_PASS_LEN	32
#define MAX_AUTH_MODE_LEN	16


/*
	STA's AUTHENTICATION state machine: states, evvents, total function #
*/
#define AUTH_REQ_IDLE                   0
#define AUTH_WAIT_SEQ2                  1
#define AUTH_WAIT_SEQ4                  2
#define MAX_AUTH_STATE                  3

/*
	STA's ASSOC state machine: states, events, total function #
*/
#define ASSOC_IDLE                      0
#define ASSOC_WAIT_RSP                  1
#define REASSOC_WAIT_RSP                2
#define DISASSOC_WAIT_RSP               3
#define MAX_ASSOC_STATE                 4

typedef enum _SCAN_STA {
	SCAN_STA_IDLE,
	SCAN_STA_SCAN,
} SCAN_STA;

typedef enum _WIFI_STATE{
	WIFI_STATE_INIT = 0,
	WIFI_STATE_SMTCNT,
	WIFI_STATE_SCAN,
	WIFI_STATE_AUTH,
	WIFI_STATE_ASSOC,
	WIFI_STATE_4WAY,
	WIFI_STATE_CONNED
}WIFI_STATE;

typedef struct GNU_PACKED _STATE_MACHINE {
	UINT8				CurrState;
	UINT32				RetryCount;
} STATE_MACHINE, *PSTATE_MACHINE;

typedef struct GNU_PACKED _MLME_STRUCT {
	/* STA state machines */
	STATE_MACHINE	CntlMachine;
	STATE_MACHINE	AssocMachine;
	STATE_MACHINE	AuthMachine;
	WIFI_STATE		CurrentWifiState;
	WIFI_STATE		PreWifiState;
	BOOLEAN			UseFlashStaCfg;
	BOOLEAN			VerfiyInit;
	UINT8			DataEnable;
} MLME_STRUCT, *PMLME_STRUCT;


/*  Added new encryption types */
typedef enum _NDIS_802_11_WEP_STATUS
{
    Ndis802_11WEPEnabled,
    Ndis802_11Encryption1Enabled = Ndis802_11WEPEnabled,
    Ndis802_11WEPDisabled,
    Ndis802_11EncryptionDisabled = Ndis802_11WEPDisabled,
    Ndis802_11WEPKeyAbsent,
    Ndis802_11Encryption1KeyAbsent = Ndis802_11WEPKeyAbsent,
    Ndis802_11WEPNotSupported,
    Ndis802_11EncryptionNotSupported = Ndis802_11WEPNotSupported,
    Ndis802_11Encryption2Enabled,
    Ndis802_11Encryption2KeyAbsent,
    Ndis802_11Encryption3Enabled,
    Ndis802_11Encryption3KeyAbsent,
    Ndis802_11Encryption4Enabled,	// TKIP or AES mix
    Ndis802_11Encryption4KeyAbsent,
    Ndis802_11GroupWEP40Enabled,
	Ndis802_11GroupWEP104Enabled
} NDIS_802_11_WEP_STATUS, *PNDIS_802_11_WEP_STATUS, NDIS_802_11_ENCRYPTION_STATUS, *PNDIS_802_11_ENCRYPTION_STATUS;

typedef enum _NDIS_802_11_AUTHENTICATION_MODE
{
	Ndis802_11AuthModeOpen,
	Ndis802_11AuthModeShared,
	Ndis802_11AuthModeAutoSwitch,
	Ndis802_11AuthModeWPA,
	Ndis802_11AuthModeWPAPSK,
	Ndis802_11AuthModeWPANone,
	Ndis802_11AuthModeWPA2,
	Ndis802_11AuthModeWPA2PSK,    
	Ndis802_11AuthModeWPA1WPA2,
	Ndis802_11AuthModeWPA1PSKWPA2PSK,
	Ndis802_11AuthModeMax           // Not a real mode, defined as upper bound
} NDIS_802_11_AUTHENTICATION_MODE, *PNDIS_802_11_AUTHENTICATION_MODE;

typedef struct GNU_PACKED _IOT_SMNT_INFO {
	UCHAR  Ssid[MAX_LEN_OF_SSID+1];
	UCHAR  SsidLen;
	NDIS_802_11_AUTHENTICATION_MODE	AuthMode;	/* This should match to whatever microsoft defined */
	UCHAR  Passphase[CIPHER_TEXT_LEN];
	UINT8  PassphaseLen;
	UCHAR  PMK[CIPHER_TEXT_LEN];				/* WPA2-PSK mode PMK */
} IOT_SMNT_INFO, *PIOT_SMNT_INFO;


typedef struct GNU_PACKED _STA_ADMIN_CONFIG {
	/***********************************************/
	/*Reference to station */
	/***********************************************/
	USHORT DefaultListenCount;
	UCHAR  MyMacAddr[MAC_ADDR_LEN];
	UCHAR  DA[MAC_ADDR_LEN];

	// station rate config/capability/phymode
	UCHAR  SupRate[MAX_LEN_OF_SUPPORTED_RATES];
	UCHAR  ExtRate[MAX_LEN_OF_SUPPORTED_RATES];
	UCHAR  SupRateLen;
	UCHAR  ExtRateLen;
	USHORT CapabilityInfo;
	UINT8  Sta_PhyMode;	 /* Phy mode for current STA */
	BOOLEAN bClearFrame; /* Tx data is clear frame or encrypted*/
	
	/***********************************************/
	/*Reference to AP */
	/***********************************************/
	UCHAR  Bssid[MAC_ADDR_LEN];
	UCHAR  Ssid[MAX_LEN_OF_SSID+1];
	UCHAR  SsidLen;
	USHORT Aid;

	UINT8  Cfg_BW;            /* BW for current AP */
	UINT8  Cfg_Channel;       /* Channel for current AP */
	UINT8  AP_PhyMode;        /* Phy mode for current AP */
	
	NDIS_802_11_AUTHENTICATION_MODE	AuthMode;	/* This should match to whatever microsoft defined */
	UCHAR  CipherAlg;
	UCHAR  Passphase[CIPHER_TEXT_LEN];
	UINT8  PassphaseLen;
	UCHAR  DefaultKeyId;

#if CFG_SUPPORT_4WAY_HS
	//[Arron Modify start]: Added for WPA PSK

	/* Add to support different cipher suite for WPA2/WPA mode */
	NDIS_802_11_ENCRYPTION_STATUS GroupCipher;	/* Multicast cipher suite */
	NDIS_802_11_ENCRYPTION_STATUS PairCipher;	/* Unicast cipher suite */
	BOOLEAN bMixCipher;				/* Indicate current Pair & Group use different cipher suites */
	USHORT RsnCapability;
	
	NDIS_802_11_WEP_STATUS WepStatus;
	
	NDIS_802_11_WEP_STATUS GroupKeyWepStatus;

//	UCHAR WpaPassPhrase[64];			/* WPA PSK pass phrase */
//	UINT WpaPassPhraseLen;			/* the length of WPA PSK pass phrase */
	UCHAR PMK[LEN_PMK];				/* WPA PSK mode PMK */
	UCHAR PTK[LEN_PTK];				/* WPA PSK mode PTK */
//	UCHAR GMK[LEN_GMK];			/* WPA PSK mode GMK only for ap mode */ 
	UCHAR GTK[MAX_LEN_GTK];			/* GTK from authenticator */
//	UCHAR GNonce[32];				/* GNonce for WPA2PSK from authenticator ,only for ap mode*/ 
	CIPHER_KEY PairwiseKey;
	CIPHER_KEY SharedKey[1][4]; 	/* STA always use SharedKey[BSS0][0..3] */
	/* For WPA-PSK supplicant state */
	UINT8 WpaState;					/* Default is SS_NOTUSE and handled by microsoft 802.1x */
	UCHAR R_Counter[LEN_KEY_DESC_REPLAY]; /* store the R_Counter value in 4way-MSG1 or 4way-MSG3 for build response */
	UCHAR ReplayCounter[8];
	UCHAR ANonce[32];				/* ANonce for WPA-PSK from aurhenticator */
	UCHAR SNonce[32];				/* SNonce for WPA-PSK */

	UCHAR RSNIE_Len;
	UCHAR RSN_IE[MAX_LEN_OF_RSNIE]; /* The content saved here should be little-endian format. */

	//[Arron Modify End]: Added for WPA PSK
#endif
	/* New for WPA, windows want us to to keep association information and */
	/* Fixed IEs from last association response */
	//NDIS_802_11_ASSOCIATION_INFORMATION AssocInfo;
	//USHORT ReqVarIELen;			/* Length of next VIE include EID & Length */
	//UCHAR ReqVarIEs[MAX_VIE_LEN];	/* The content saved here should be little-endian format. */
} STA_ADMIN_CONFIG, *PSTA_ADMIN_CONFIG;

/******************************************************************************
 * Interface  MACRO & STRUCTURE
 ******************************************************************************/
#if (UARTRX_TO_AIR_QUERY == 1)
#define UART_RX_RING_BUFF_SIZE IOT_BUFFER_LEN - CP_HDR_LEN - CP_DATA_HDR_LEN
#else
#define UART_RX_RING_BUFF_SIZE IOT_BUFFER_LEN
#endif



#define IOT_PWM_TYPE 		2 // 1 for Hardware pwm,   2 for Software pwm

#if (IOT_PWM_SUPPORT == 1 && IOT_PWM_TYPE == 1)

#define PWM_HIGHEST_LEVEL 	5

#elif (IOT_PWM_SUPPORT == 1 && IOT_PWM_TYPE == 2)

#define PWM_R_GPIO 			0
#define PWM_G_GPIO 			1
#define PWM_B_GPIO 			3 //gpio2 for button input
#define PWM_HIGHEST_LEVEL 	20
#define MAX_PWM_COUNT 		5

typedef struct GNU_PACKED t_HWTimerPWMInfo
{
	VOLATILE INT32 on_time[MAX_PWM_COUNT];
	VOLATILE INT32 off_time[MAX_PWM_COUNT];

	VOLATILE INT32 on_count[MAX_PWM_COUNT];
	VOLATILE INT32 off_count[MAX_PWM_COUNT];

	VOLATILE bool skip_pwm_flag[MAX_PWM_COUNT];

	VOLATILE bool available[MAX_PWM_COUNT];

}HWTimerPWMInfo;

#endif


/******************************************************************************
 * FUNCTIONS DEFINITION  --- SYSTEM
 ******************************************************************************/

INT32 __romtext memcmp(const void * cs,const void * ct, unsigned long count);
INT32 atoi(const int8 *s);
VOID  Printf_High(const char *fmt, ...);

/*Notice:  not allow to use malloc again before free the old one*/
/*example1:  malloc(A)-->free(A)-->malloc(B)-->free(B)   is OK*/
/*example1:  malloc(A)-->malloc(B)-->free(A)-->free(B)   is NG*/
VOID *malloc(unsigned long size);
VOID free(void *ptr);




/******************************************************************************
 * FUNCTIONS DEFINITION
 ******************************************************************************/
INT32 IoT_uart_output(CHAR *msg, size_t count);
INT32 IoT_uart_input(CHAR *msg, INT16 count);

UINT16 uart_get_avail(void);
UCHAR  uart_rb_pop(void);
VOID   uart_rb_init(void);
VOID   UART_PutChar(UCHAR ch);
INT32  UART_GetChar(UCHAR* ch);
VOID   uart_rb_push(UCHAR ch);
UINT32 crc_cal_by_bit(const unsigned char* ptr, unsigned char len);
	

UINT8 spi_flash_update_fw_done(uint8 type);
UINT8 spi_flash_update_fw(uint8 type, uint32 offset, uint8 *pdata, uint16 len);


VOID IoT_software_pwm_handler(VOID);
VOID IoT_software_pwm_init(VOID);

#if (IOT_PWM_SUPPORT == 1)

#if (IOT_PWM_TYPE == 1)
int IoT_led_pwm(int led_num, int brightness);
#elif (IOT_PWM_TYPE == 2)
INT32 IoT_software_pwm_addset(INT32 led_num, INT32 brightness);
#define IoT_led_pwm IoT_software_pwm_addset
#endif

#endif


/*Read gpio status:   (*pPolarity 0=output mode, 1=input mode),  (*pVal  0=low,  1=High) */
VOID  IoT_gpio_read(IN INT32 gpio_num, OUT UINT8* pVal, OUT UINT8* pPolarity);
INT32 IoT_gpio_output(INT32 gpio_num,  INT32 output);
INT32 IoT_gpio_input(INT32 gpio_num,  UINT32 *input);

/*========================================================================
	Routine	Description:
		IoT_Cust_GPIINT_Hdlr --  GPIO interrupt handler
		
	Arguments:
	[IN] GPI_STS  -  [0~6]:  GPIO0~6 Interrupt status
	
	Return Value:  NONE
	Note:
========================================================================*/
VOID IoT_Cust_GPIINT_Hdlr(IN UINT8 GPI_STS);

/*========================================================================
	Routine	Description:
		IoT_Cust_Set_GPIINT_MODE --  Set GPIO interrupt mode
		
	Arguments:
	[IN] GPIO_Num  -  [0~6]
	[IN] Val -0: no trigger
	              1: falling edge trigger
	              2: rising edge trigger
	              3: both falling and rising edge trigger
	Return Value:  0-success    1-invalid input
	Note:
========================================================================*/
UINT8 IoT_Cust_Set_GPIINT_MODE(IN UINT8 GPIO_Num, IN UINT8 Val);

/*========================================================================
	Routine	Description:
		IoT_Cust_Get_GPIINT_MODE --  Get GPIO interrupt mode for GPIO0~6
		
	Arguments:
	[OUT] pGPI_INT_MODE -[1:0] 	  GPIO1 interrupt mode
				   		 [3:2]	  GPIO0 interrupt mode
				    		 [5:4] 	  GPIO2 interrupt mode
				   		 [7:6] 	  GPIO3 interrupt mode
				   		 [9:8] 	  GPIO4 interrupt mode
				   		 [11:10]	  GPIO5 interrupt mode
				   		 [13:12]	  GPIO6 interrupt mode
		  For each GPIO's interrupt mode
		  0: no trigger
		  1: falling edge trigger
		  2: rising edge trigger
		  3: both falling and rising edge trigger
	Return Value:  None
	Note:
========================================================================*/
VOID IoT_Cust_Get_GPIINT_MODE(OUT UINT16* pGPI_INT_MODE);



VOID   IoT_jtag_mode_switch(UINT8 switch_on);
UINT32 IoT_jtag_mode_get(void);


VOID   Sys_reboot(VOID);
VOID   IoT_Cmd_LinkDown(USHORT reason);
VOID   MlmeDeauthReqAction(IN PUCHAR pDA_Addr,
						 IN PUCHAR pBSSID_Addr,
						 IN USHORT Reason);
VOID   UART_Configure_From_Flash(VOID);
INT32  IoT_Xmodem_Update_FW(VOID);
VOID   IoT_Cmd_Set_Channel(UINT8 Channel);



/*if all data is 0xFF or 0x00, we assume it is invalide*/
BOOLEAN check_data_valid(PUINT8 pdata, UINT16 len);
BOOLEAN load_sta_cfg(VOID);
BOOLEAN reset_sta_cfg(VOID);
VOID    store_sta_cfg(VOID);

VOID IoT_Cust_SMNT_Sta_Chg_Init(VOID);
VOID IoT_Cust_SM_Smnt(VOID);
//VOID IoT_Cust_Rx_Handler(PHEADER_802_11 pHeader, USHORT DataSize);





INT32  IoT_process_app_packet(
#if ENABLE_DATAPARSING_SEQUENCE_MGMT	
								UCHAR sock_num,
#endif
								PUCHAR packet , 
								UINT16 rawpacketlength);

VOID   IoT_build_send_udp_packet(PUCHAR pSrcAddr, 
			PUCHAR pDstAddr,
			UINT16 SrcPort,
			UINT16 DstPort,
			PUCHAR pPayload, 
			UINT16  PayloadLen);

INT32  IoT_build_app_response_header(
			PUCHAR buffer,
			UINT_8 ProtoType, 
			UINT_8 ProtoSubType, 
			UINT_16 DataType, 
			UINT_16 DataLen, 
			struct t_IoTPacketInfo *PacketInfo);

INT32  IoT_process_app_function_packet(
		DataHeader* Dataheader, 
		UINT8 FunctionType, 
		IoTPacketInfo  *pPacketInfo);

VOID   IoT_cp_app_connection_init(VOID);
INT16  IoT_cp_app_connection_connected(UINT8 fd
#if (NO_USED_CODE_REMOVE==0)
									,UINT16 lport, 
									PUCHAR raddr, 
									UINT16 rport
#endif
									);
INT16  IoT_cp_app_connection_closed(UINT8 fd);
UINT16 IoT_cp_app_search_seq(UINT8 fd);
INT16  IoT_cp_app_set_seq(UINT8 fd, UINT_16 seq);

struct cp_app_conn * IoT_cp_app_search_connection(UINT8 fd);

VOID  uip_send(const void *data, UINT16 len);






VOID  split_string_cmd(PCHAR string_cmd, INT16 cmdlen, INT16 *pargc, char **argv);
ULONG simple_strtoul(const char *cp,char **endp,unsigned int base);
CHAR  getopt(INT16 argc, char *argv[], char *opstring);
VOID  ATcommandHandler(VOID);

INT32 IoT_uart_AT_config(PCHAR command_buffer, INT16 at_cmd_len);
INT32 IoT_Tcpip_AT_Connect(PCHAR command_buffer, INT16 at_cmd_len);
INT32 IoT_Tcpip_AT_Send(PCHAR command_buffer, INT16 at_cmd_len);
INT32 IoT_Tcpip_AT_Listen(PCHAR command_buffer, INT16 at_cmd_len);
INT32 IoT_Tcpip_AT_Disconnect(PCHAR command_buffer, INT16 at_cmd_len);
INT32 IoT_Tcpip_AT_Udp_Create(PCHAR command_buffer, INT16 at_cmd_len);
INT32 IoT_Tcpip_AT_Udp_Del(PCHAR command_buffer, INT16 at_cmd_len);
INT32 IoT_Tcpip_AT_Udp_Send(PCHAR command_buffer, INT16 at_cmd_len);

INT32 iot_listen (UINT16 port);
INT32 iot_connect(UINT8 *dst, UINT16 port);
VOID  iot_disconnect(UINT8 fd);
INT32 iot_send(UINT8 fd, UINT8 *buf, UINT16 len);
INT32 iot_udp_new(UINT8 *rip, UINT16 lport, UINT16 rport);
VOID  iot_udp_remove(UINT8 fd);
INT32 iot_udp_send(UINT8 fd, UINT8 *buf, UINT16 len, UINT8 *rip, UINT16 rport);
INT32 iot_netif_cfg(UINT8 *ip, UINT8 *mask, UINT8 * gw, UINT8 *dns);




#define AES_STATE_ROWS 4     /* Block size: 4*4*8 = 128 bits */
#define AES_STATE_COLUMNS 4
#define AES_BLOCK_SIZES (AES_STATE_ROWS*AES_STATE_COLUMNS)


/*
========================================================================
Routine Description:
    AES decryption

Arguments:
    CipherBlock      The block of cipher text, 16 bytes(128 bits) each block
    CipherBlockSize  The length of block of cipher text in bytes
    Key              Cipher key, it may be 16, 24, or 32 bytes (128, 192, or 256 bits)
    KeyLength        The length of cipher key in bytes
    PlainBlockSize   The length of allocated plain block in bytes

Return Value:
    PlainBlock       Return plain text
    PlainBlockSize  Return the length of real used plain block in bytes
========================================================================
*/
VOID RT_AES_Decrypt (
    UINT8 CipherBlock[],
    UINT CipherBlockSize,
    UINT8 Key[],
    UINT KeyLength,
    UINT8 PlainBlock[],
    UINT *PlainBlockSize);

/*
========================================================================
Routine Description:
    AES encryption

Arguments:
    PlainBlock       The block of plain text, 16 bytes(128 bits) each block
    PlainBlockSize   The length of block of plain text in bytes
    Key              Cipher key, it may be 16, 24, or 32 bytes (128, 192, or 256 bits)
    KeyLength        The length of cipher key in bytes
    CipherBlockSize  The length of allocated cipher block in bytes

Return Value:
    CipherBlock      Return cipher text
    CipherBlockSize  Return the length of real used cipher block in bytes
========================================================================
*/
VOID RT_AES_Encrypt (
    UINT8 PlainBlock[],
    UINT PlainBlockSize,
    UINT8 Key[],
    UINT KeyLength,
    UINT8 CipherBlock[],
    UINT *CipherBlockSize);

/* 
* password - ascii string up to 63 characters in length 
* ssid - octet string up to 32 octets 
* ssidlength - length of ssid in octets 
* output must be 40 octets in length and outputs 256 bits of key 
*/ 
int RtmpPasswordHash(
	PSTRING password, 
	PUCHAR ssid, 
	INT ssidlength, 
	PUCHAR output);




#if (ATCMD_ATE_SUPPORT == 1)
/*ATE*/
VOID ATESTART(UINT8 mode);
BOOLEAN	Set_ATE_Switch_CH(IN UINT8 Channel);
BOOLEAN	Set_ATE_TX_MODE_Proc(IN UINT8 TxWIPHYMODE);
BOOLEAN	Set_ATE_TX_MCS_Proc(IN UINT8 MCS);
BOOLEAN Set_ATE_TX_FREQ_OFFSET_Proc(IN UINT8 RfFreqOffset);
BOOLEAN	Set_ATE_TX_GI_Proc(IN UINT8 TxWIShortGI);
BOOLEAN	Set_ATE_TX_COUNT_Proc(IN UINT32 TxCount);
BOOLEAN Set_ATE_TX_POWER(IN UINT32 TxPower);
BOOLEAN Set_ATE_Efuse_Read(IN USHORT Offset, OUT UINT8 *pdata);
BOOLEAN Set_ATE_Efuse_Write(IN USHORT Offset,  IN UINT8 data);
#endif

#endif


