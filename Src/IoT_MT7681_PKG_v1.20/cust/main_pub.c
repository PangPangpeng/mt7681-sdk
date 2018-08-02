/******************************************************************************
 * MODULE NAME:	 main.c
 * PROJECT CODE:	__RT7681__
 * DESCRIPTION:
 * DESIGNER:		Charles Su
 * DATE:			Oct 2011
 *
 * SOURCE CONTROL:
 *
 *���°汾�������ǻ��� http://www.ai-thinker.com ������������
 *	 This source code is copyright (c) 2011 Ralink Tech. Inc.
 *	 �����а��ſɿƼ� MTK7681����ģ��רҵ�������� .
 *
 * REVISION	 HISTORY:
 *   V1.0.0	 Oct 2011	- Initial Version V1.0
 *   V1.0.1	 Dec 2011	- Add Caution
 *
 *
 * SOURCE:
 * ISSUES:
 *	����WIFI �۸����500 30Ԫ   ����5K  28Ԫ   ����10K  25Ԫ.
 * �۸���ʱ�ڽ��ͣ����±������µ磺15323435161  0755-61195776  4008555368
 *
 ******************************************************************************/
#include "stdio.h"
#include "types.h"
#include "wifi_task.h"
#include "iot_api.h"
#include "iot_custom.h"

/*****************************************************************
  Extern Paramter
******************************************************************/
extern IOT_CUST_OP IoTCustOp;



/*****************************************************************
  Functions
******************************************************************/
/******************************************************************************
 * main
 * Description :
 *  The main function is used to initialize all the functionalities in C.
 ******************************************************************************/
OUT INT32
main (VOID)
{
	/* customer hook function initial */
	IoT_Cust_Ops();

	/* The entry for customization */
	if (IoTCustOp.IoTCustPreInit != NULL)
		IoTCustOp.IoTCustPreInit();

	/* Initialize BSP */
	BSP_Init();

#if (WIFI_SUPPORT==1)
	/* Initialize APP */
	APP_Init();
#endif

	sys_Init();

	/* run customer initial function */
	if (IoTCustOp.IoTCustInit != NULL)
	{
		IoTCustOp.IoTCustInit();
	}

		/* Create Tasks */
	/*******************************************************************************
	 ****** CAUTION : SOFTWARE PROGRAMMER SHALL NOT MODIFY THE FOLLOWING CODES *****
	 ******************************************************************************/
	sysTASK_RegTask(wifiTASK_LowPrioTask);

	/* Start the Kernel process */
	sysKernelStart();

	return 0;
}

