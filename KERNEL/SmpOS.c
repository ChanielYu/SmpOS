/*
*********************************************************************************************************
*                                               SmpOS
*                                        The Real-Time Kernel
*
*                         (c) Copyright 2013-2083, Changzhi Yu
*                                          All Rights Reserved
*
* File         : SmpOS.c
*********************************************************************************************************
*/

#include <SmpOS.h>

/*
*********************************************************************************************************
*                                             INITIALIZATION
*
* Description: This function is used to initialize the internals of SmpOS and MUST be called prior to
*              creating any SmpOS object and, prior to calling SmpOS_Start().
*
* Arguments  : none
*
* Returns    : none
*********************************************************************************************************
*/

VOID SmpOS_Init(VOID)
{
	SmpOS_KernelInit();
	SmpOS_ErrorInit();
#if 0
#if OS_VERSION >= 204
		OSInitHookBegin();											 /* Call port specific initialization code	 */
#endif
	
		OS_InitMisc();												 /* Initialize miscellaneous variables		 */
	
		OS_InitRdyList();											 /* Initialize the Ready List				 */
		OS_InitTCBList();											 /* Initialize the free list of OS_TCBs 	 */
		OS_InitEventList(); 										 /* Initialize the free list of OS_EVENTs	 */
	
#if (OS_VERSION >= 251) && (OS_FLAG_EN > 0) && (OS_MAX_FLAGS > 0)
		OS_FlagInit();												 /* Initialize the event flag structures	 */
#endif
	
#if (OS_MEM_EN > 0) && (OS_MAX_MEM_PART > 0)
		OS_MemInit();												 /* Initialize the memory manager			 */
#endif
	
#if (OS_Q_EN > 0) && (OS_MAX_QS > 0)
		OS_QInit(); 												 /* Initialize the message queue structures  */
#endif
	
		OS_InitTaskIdle();											 /* Create the Idle Task					 */
#if OS_TASK_STAT_EN > 0
		OS_InitTaskStat();											 /* Create the Statistic Task				 */
#endif
	
#if OS_VERSION >= 204
		OSInitHookEnd();											 /* Call port specific init. code			 */
#endif
#endif
}

/*
*********************************************************************************************************
*                                          START MULTITASKING
*
* Description: This function is used to start the multitasking process which lets SmpOS manages the
*              task that you have created.  Before you can call SmpOS_Start(), you MUST have called SmpOS_Init()
*              and you MUST have created at least one task.
*
* Arguments  : none
*
* Returns    : none
*
* Note       : OSStartHighRdy() MUST:
*                 a) Call OSTaskSwHook() then,
*                 b) Set OSRunning to TRUE.
*                 c) Load the context of the task pointed to by OSTCBHighRdy.
*                 d_ Execute the task.
*********************************************************************************************************
*/

VOID SmpOS_Start(VOID)
{
	SmpOS_KernelStart();
}

/*
*********************************************************************************************************
*                                          SmpOS_Sleep
*
* Description: This function is used to start the multitasking process which lets SmpOS manages the
*              task that you have created.  Before you can call SmpOS_Start(), you MUST have called SmpOS_Init()
*              and you MUST have created at least one task.
*
* Arguments  : none
*
* Returns    : none
*
* Note       : OSStartHighRdy() MUST:
*                 a) Call OSTaskSwHook() then,
*                 b) Set OSRunning to TRUE.
*                 c) Load the context of the task pointed to by OSTCBHighRdy.
*                 d_ Execute the task.
*********************************************************************************************************
*/

VOID SmpOS_Sleep(UINT32 ms)
{
	SmpOS_KernelSleep(ms/SYSTEMCLOCK);
}

