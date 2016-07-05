/*
*********************************************************************************************************
*                                               SmpOS
*                                        The Real-Time Kernel
*
*                         (c) Copyright 2013-2083, Changzhi Yu
*                                          All Rights Reserved
*
* File         : SmpOS_Thread.c
*********************************************************************************************************
*/

#include <SmpOS.h>

#include <SmpOS_Core.h>
/*
*********************************************************************************************************
*                                             SmpOS_ThreadCreate
*
* Description: This function is called by any user function to create a thread to be performed.
*
* Arguments  : ThreadProc, the function of thread.
* Arguments  : pdata, thread parameter.
* Arguments  : pStack, the top of the thread.
* Arguments  : prio,
*
* Returns    : HANDLE of created thread.
*********************************************************************************************************
*/

SMPOSHANDLE SmpOS_ThreadCreate(THREADPROC ThreadProc, VOID* pdata, SMPOS_STK* pStack, UINT8 prio)
{
	SMPOSHANDLE handle = NULL;
	SMPOSERR reterr = SMPOS_UNKNOWN;
	PSMPOS_THREAD pThread = NULL;
	pThread = SmpOS_CoreObtainThreadList();
	if(pThread)
	{
		SmpOS_ARMContextInit(ThreadProc, pdata, pStack, &pThread->SmpOStcb.ARMcontext);
		reterr = SmpOS_CoreAddToReadyList(pThread);
		SmpOS_SetLastError(reterr);
		if(SMPOS_SUCCESS == reterr)
		{
			handle = (SMPOSHANDLE)pThread;
		}
		else
		{
			handle = NULL;
		}
	}
	else
	{
		handle = NULL;
		SmpOS_SetLastError(SMPOS_CORE_NOOSTCBLIST);
	}
	
    return handle;
#if 0
    OS_STK    *psp;
    INT8U      err;

#if OS_ARG_CHK_EN > 0
	if(prio > OS_LOWEST_PRIO)
	{/* Make sure priority is within allowable range */
		return (OS_PRIO_INVALID);
	}
#endif
    OS_ENTER_CRITICAL();
    if(OSTCBPrioTbl[prio] == (OS_TCB *)0)
	{
		/* Make sure task doesn't already exist at this priority */
        OSTCBPrioTbl[prio] = (OS_TCB *)1;    /* Reserve the priority to prevent others from doing ...  */
                                             /* ... the same thing until task is created.              */
        OS_EXIT_CRITICAL();
        pSP = (OS_STK *)OSTaskStkInit(task, pdata, ptos, 0);    /* Initialize the task's stack         */
        err = OS_TCBInit(prio, pSP, (OS_STK *)0, 0, 0, (void *)0, 0);
        if (err == OS_NO_ERR) {
            OS_ENTER_CRITICAL();
            OSTaskCtr++;                                        /* Increment the #tasks counter        */
            OS_EXIT_CRITICAL();
            if (OSRunning == TRUE) {         /* Find highest priority task if multitasking has started */
                OS_Sched();
            }
        } else {
            OS_ENTER_CRITICAL();
            OSTCBPrioTbl[prio] = (OS_TCB *)0;/* Make this priority available to others                 */
            OS_EXIT_CRITICAL();
        }
        return (err);
    }
    OS_EXIT_CRITICAL();
#endif
}

