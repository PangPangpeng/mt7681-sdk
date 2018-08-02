#include <stdio.h>
#include "string.h"
#include "types.h"
#include "iot_api.h"
#include "config.h"
#if 0 //CFG_SUPPORT_TCPIP
#include "uip.h"
#endif
#include "flash_map.h"
#include "uip-conf.h"

/******************************************************************************
* MODULE NAME:     iot_parse_conn_mgmt.c
* PROJECT CODE:    __MT7681__
* DESCRIPTION:     
* DESIGNER:        
* DATE:            Jan 2013
*
*���°汾�������ǻ��� http://www.ai-thinker.com ������������
*
* LICENSE:
*     This source code is copyright (c) 2011 Ralink Tech. Inc.
*     All rights reserved.
*
* �����а��ſɿƼ� MTK7681����ģ��רҵ�������� 
*   V1.0.0     Jan 2012    - Initial Version V1.0
*
*
* ����WIFI �۸����500 30Ԫ   ����5K  28Ԫ   ����10K  20Ԫ
* ISSUES:
*    First Implementation.
* �Ա�����http://anxinke.taobao.com/?spm=2013.1.1000126.d21.FqkI2r
*
******************************************************************************/

#if ENABLE_DATAPARSING_SEQUENCE_MGMT

struct cp_app_conn cp_app_conns[UIP_CONF_MAX_CONNECTIONS];

#define INVALID_SOCK_NUM 255


VOID IoT_cp_app_connection_init(VOID)
{
	UCHAR i = 0;
	DBGPRINT(RT_DEBUG_TRACE, ("IoT_cp_app_connection_init\n"));
	
	for (i=0; i<UIP_CONF_MAX_CONNECTIONS; i++) 
	{
		cp_app_conns[i].soket_num = INVALID_SOCK_NUM;
		cp_app_conns[i].prev_seq = 0;

	}

	return;
}

INT16 IoT_cp_app_connection_connected(UINT8 fd
#if (NO_USED_CODE_REMOVE==0)
											,UINT16 lport, 
											PUCHAR raddr, 
											UINT16 rport
#endif
											)
{
	UCHAR i = 0;
	DBGPRINT(RT_DEBUG_TRACE, ("IoT_cp_app_connection_connected:%d\n",fd));
	
	for (i=0; i<UIP_CONF_MAX_CONNECTIONS; i++) 
	{
		if(cp_app_conns[i].soket_num == INVALID_SOCK_NUM)
		{
			cp_app_conns[i].soket_num = fd;
			cp_app_conns[i].prev_seq = 0;
			return 0;
		}	
	}
	
	return -1;
}

INT16 IoT_cp_app_connection_closed(UINT8 fd)
{

	UCHAR i = 0;
	DBGPRINT(RT_DEBUG_TRACE, ("IoT_cp_app_connection_closed:%d\n",fd));

	for (i=0; i<UIP_CONF_MAX_CONNECTIONS; i++) 
	{
		if(cp_app_conns[i].soket_num == fd)
		{
			cp_app_conns[i].soket_num = INVALID_SOCK_NUM;
			cp_app_conns[i].prev_seq = 0;
			return 0;
		}	
	}

	return -1;
}

UINT16 IoT_cp_app_search_seq(UINT8 fd)
{

	UCHAR i = 0;

	UINT16 seq = 0;
	DBGPRINT(RT_DEBUG_TRACE, ("IoT_cp_app_search_seq:%d\n",fd));

	for (i=0; i<UIP_CONF_MAX_CONNECTIONS; i++) 
	{
		if(cp_app_conns[i].soket_num == fd)
		{
			seq = cp_app_conns[i].prev_seq;
			return seq;
		}	
	}

	return 0;
}

INT16 IoT_cp_app_set_seq(UINT8 fd, UINT16 seq)
{

	UCHAR i = 0;
	DBGPRINT(RT_DEBUG_TRACE, ("IoT_cp_app_set_seq:%d,%d\n", fd, seq));

	for (i=0; i<UIP_CONF_MAX_CONNECTIONS; i++) 
	{
		if(cp_app_conns[i].soket_num == fd)
		{
			cp_app_conns[i].prev_seq = seq;
			return 0;
		}	
	}

	return -1;
}


struct cp_app_conn * IoT_cp_app_search_connection(UINT8 fd)
{

	UCHAR i = 0;

	struct cp_app_conn *conn = NULL;

	for (i=0; i<UIP_CONF_MAX_CONNECTIONS; i++) 
	{
		if(cp_app_conns[i].soket_num == fd)
		{
			conn = &cp_app_conns[i];
				return conn;;
		}	
	}
	
	return NULL;

}

#endif



