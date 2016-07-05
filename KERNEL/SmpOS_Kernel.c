/*
*********************************************************************************************************
*                                               SmpOS
*                                        The Real-Time Kernel
*
*                         (c) Copyright 2013-2083, Changzhi Yu
*                                          All Rights Reserved
*
* File         : SmpOS_Kernel.c
*********************************************************************************************************
*/


#include <SmpOS.h>

#include <SmpOS_Core.h>
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

VOID SmpOS_KernelInit(VOID)
{
	SmpOS_CoreInit();
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

VOID SmpOS_KernelStart(VOID)
{
	SmpOS_CoreNextReady();
	SmpOS_StartThread();
#if 0
    INT8U y;
    INT8U x;


    if (OSRunning == FALSE) {
        y             = OSUnMapTbl[OSRdyGrp];        /* Find highest priority's task priority number   */
        x             = OSUnMapTbl[OSRdyTbl[y]];
        OSPrioHighRdy = (INT8U)((y << 3) + x);
        OSPrioCur     = OSPrioHighRdy;
        OSTCBHighRdy  = OSTCBPrioTbl[OSPrioHighRdy]; /* Point to highest priority task ready to run    */
        OSTCBCur      = OSTCBHighRdy;
        OSStartHighRdy();                            /* Execute target specific code to start task     */
    }
#endif
}

/*
*********************************************************************************************************
*                                              SCHEDULER
*
* Description: This function is called by other SmpOS services to determine whether a new, high
*              priority task has been made ready to run.  This function is invoked by TASK level code
*              and is not used to reschedule tasks from ISRs (see OSIntExit() for ISR rescheduling).
*
* Arguments  : none
*
* Returns    : none
*
* Notes      : 1) This function is INTERNAL to SmpOS and your application should not call it.
*              2) Rescheduling is prevented when the scheduler is locked (see SmpOS_SchedLock())
*********************************************************************************************************
*/
// Comment may be changed due to SmpOS always switch user threads in previlidge mode. (in a SystemCall by SVC service or in IRQ)

VOID SmpOS_KernelSched(VOID)
{
	OS_ENTER_CRITICAL();
	if(SMPOS_SUCCESS == SmpOS_CoreNextReady())
	{
		SmpOS_ContextSwitch();
	}
	OS_EXIT_CRITICAL();
}

/*
*********************************************************************************************************
*                                              SCHEDULER
*
* Description: This function is called by other SmpOS services to determine whether a new, high
*              priority task has been made ready to run.  This function is invoked by TASK level code
*              and is not used to reschedule tasks from ISRs (see OSIntExit() for ISR rescheduling).
*
* Arguments  : none
*
* Returns    : none
*
* Notes      : 1) This function is INTERNAL to SmpOS and your application should not call it.
*              2) Rescheduling is prevented when the scheduler is locked (see SmpOS_SchedLock())
*********************************************************************************************************
*/
// Comment may be changed due to SmpOS always switch user threads in previlidge mode. (in a SystemCall by SVC service or in IRQ)

VOID SmpOS_KernelSleep(UINT32 tick)
{
	PSMPOS_TCB pOStcb = NULL;
	OS_ENTER_CRITICAL();
	pOStcb = SmpOS_CoreGetCurTCB();
	pOStcb->Delay = tick;
	OS_EXIT_CRITICAL();
	SmpOS_KernelSched();
}

/*
*********************************************************************************************************
*                                              SCHEDULER
*
* Description: This function is called by other SmpOS services to determine whether a new, high
*              priority task has been made ready to run.  This function is invoked by TASK level code
*              and is not used to reschedule tasks from ISRs (see OSIntExit() for ISR rescheduling).
*
* Arguments  : none
*
* Returns    : none
*
* Notes      : 1) This function is INTERNAL to SmpOS and your application should not call it.
*              2) Rescheduling is prevented when the scheduler is locked (see SmpOS_SchedLock())
*********************************************************************************************************
*/
// Comment may be changed due to SmpOS always switch user threads in previlidge mode. (in a SystemCall by SVC service or in IRQ)

VOID SmpOS_KernelTimeTick(VOID)
{
}

