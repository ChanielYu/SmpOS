/*
*********************************************************************************************************
*                                               SmpOS
*                                        The Real-Time Kernel
*
*                         (c) Copyright 2013-2083, Changzhi Yu
*                                          All Rights Reserved
*
* File         : SmpOS_Core.c
*********************************************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <SmpOS.h>
#include <SmpOS_Core.h>

UINT8 const SmpOSMapTbl[] =
{
	0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80
};

UINT8 const SmpOSUnMapTbl[] =
{
	0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x00 to 0x0F                             */
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x10 to 0x1F                             */
	5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x20 to 0x2F                             */
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x30 to 0x3F                             */
	6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x40 to 0x4F                             */
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x50 to 0x5F                             */
	5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x60 to 0x6F                             */
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x70 to 0x7F                             */
	7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x80 to 0x8F                             */
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x90 to 0x9F                             */
	5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xA0 to 0xAF                             */
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xB0 to 0xBF                             */
	6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xC0 to 0xCF                             */
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xD0 to 0xDF                             */
	5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xE0 to 0xEF                             */
	4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0        /* 0xF0 to 0xFF                             */
};

STATIC PSMPOS_THREAD pSmpOS_ReadyThreads;
STATIC PSMPOS_THREAD pSmpOS_WaitThreads;
STATIC SMPOS_THREAD SmpOS_ThreadPool[SMPOSMAXTCBPOOLSIZE];

PSMPOS_TCB pSmpOS_CurTCB;
PSMPOS_TCB pSmpOS_RdyTCB;

/*
*********************************************************************************************************
*                                             INITIALIZATION
*                                       INITIALIZE THE READY LIST
*
* Description: This function is called by SmpOS_Init() to initialize the Ready List.
*
* Arguments  : none
*
* Returns    : none
*********************************************************************************************************
*/

VOID SmpOS_CoreInit(VOID)
{
	memset(SmpOS_ThreadPool,0,sizeof(SmpOS_ThreadPool));
	pSmpOS_ReadyThreads = NULL;
	pSmpOS_CurTCB = NULL;
	pSmpOS_RdyTCB = NULL;
}

/*
*********************************************************************************************************
*                                   GET A FREE OS_TCB LIST FROM POOL
*
* Description: This function is called by SmpOS_Init() to initialize the Ready List.
*
* Arguments  : none
*
* Returns    : none
*********************************************************************************************************
*/

PSMPOS_THREAD SmpOS_CoreObtainThreadList(VOID)
{
	UINT32 i;
	PSMPOS_THREAD pRet = NULL;
	OS_ENTER_CRITICAL();
	for(i=0;i<SMPOSMAXTCBPOOLSIZE;i++)
	{
		if(FALSE == SmpOS_ThreadPool[i].inUse)
		{
			SmpOS_ThreadPool[i].inUse = TRUE;
			pRet = &SmpOS_ThreadPool[i];
			break;
		}
	}
	OS_EXIT_CRITICAL();
	return pRet;
}

/*
*********************************************************************************************************
*                                   FREE A USED OS_TCB LIST TO POOL
*
* Description: This function is called by ???.
*
* Arguments  : pThread the list to be free.
*
* Returns    : none
*********************************************************************************************************
*/

BOOL SmpOS_CoreFreeThreadList(PSMPOS_THREAD pThread)
{
	//OS_ENTER_CRITICAL();
	pThread->inUse = FALSE;
	//OS_EXIT_CRITICAL();
	return TRUE;
}

/*
*********************************************************************************************************
*                                   ADD TO READY LIST TO BE SCHEDULED
*
* Description: This function is called by SmpOS_ThreadCreate() or other thread management functions.
*
* Arguments  : pThread the list to be free.
*
* Returns    : none
*********************************************************************************************************
*/

VOID SmpOS_CoreThreadinit(PSMPOS_THREAD pThread, UINT8 prio)
{
	pThread->SmpOStcb.Finished = FALSE;
	pThread->SmpOStcb.pThread = pThread;
	pThread->SmpOStcb.Prio = prio;
	pThread->SmpOStcb.Status = SMPOSTHREAD_READY;
}

/*
*********************************************************************************************************
*                                   ADD TO READY LIST TO BE SCHEDULED
*
* Description: This function is called by SmpOS_ThreadCreate() or other thread management functions.
*
* Arguments  : pThread the list to be free.
*
* Returns    : none
*********************************************************************************************************
*/

SMPOSERR SmpOS_CoreAddToReadyList(PSMPOS_THREAD pThread)
{
	OS_ENTER_CRITICAL();
	if(pSmpOS_ReadyThreads)
	{
		pSmpOS_ReadyThreads->pPrev->pNext = pThread;
		pThread->pPrev = pSmpOS_ReadyThreads->pPrev;
		pSmpOS_ReadyThreads->pPrev = pThread;
		pThread->pNext = pSmpOS_ReadyThreads;
	}
	else
	{
		pSmpOS_ReadyThreads = pThread;
		pSmpOS_ReadyThreads->pPrev = pThread;
		pSmpOS_ReadyThreads->pNext = pThread;
	}	
	OS_EXIT_CRITICAL();
	return SMPOS_SUCCESS;
}

/*
*********************************************************************************************************
*                                   FREE A FREE OS_TCB LIST TO POOL
*
* Description: This function is called by SmpOS_Init() to initialize the Ready List.
*
* Arguments  : pThread the list to be free.
*
* Returns    : none
*********************************************************************************************************
*/

SMPOSERR SmpOS_CoreDelFromReadyList(PSMPOS_THREAD pThread)
{
	PSMPOS_THREAD prev = NULL;
	PSMPOS_THREAD next = NULL;
	OS_ENTER_CRITICAL();
	prev = pThread->pPrev;
	next = pThread->pNext;
	prev->pNext = next;
	next->pPrev = prev;
	OS_EXIT_CRITICAL();
	return SMPOS_SUCCESS;
}

/*
*********************************************************************************************************
*                                   FREE A FREE OS_TCB LIST TO POOL
*
* Description: This function is called by SmpOS_KernelStart(), SmpOS_KernelSched() and IRQ.
*
* Arguments  : none
*
* Returns    : none
*********************************************************************************************************
*/

SMPOSERR SmpOS_CoreNextReady(VOID)
{
	SMPOSERR err;
	pSmpOS_RdyTCB = &pSmpOS_ReadyThreads->SmpOStcb;
	pSmpOS_ReadyThreads = pSmpOS_ReadyThreads->pNext;
	if(pSmpOS_CurTCB == pSmpOS_RdyTCB)
	{
		err =  SMPOS_CORE_NONEEDTOSWITCH;
	}
	else
	{
		err = SMPOS_SUCCESS;
	}
	return err;
}

/*
*********************************************************************************************************
*                                   SmpOS_CoreGetCurTCB
*
* Description: This function is called by SmpOS_Init() to initialize the Ready List.
*
* Arguments  : pThread the list to be free.
*
* Returns    : none
*********************************************************************************************************
*/

PSMPOS_TCB SmpOS_CoreGetCurTCB(VOID)
{
	return pSmpOS_CurTCB;
}

/*
*********************************************************************************************************
*                                              SmpOS_CoreIntTimeTick
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

VOID SmpOS_CoreIntTimeTick(VOID)
{
	UINT32 i;
	//OS_ENTER_CRITICAL();
	for(i=0;i<SMPOSMAXTCBPOOLSIZE;i++)
	{
		if(SmpOS_ThreadPool[i].inUse || !SmpOS_ThreadPool[i].SmpOStcb.Finished)
		{
			if(SmpOS_ThreadPool[i].SmpOStcb.Delay>0)
			{
				--SmpOS_ThreadPool[i].SmpOStcb.Delay;
			}
		}
	}
	//OS_EXIT_CRITICAL();
}

