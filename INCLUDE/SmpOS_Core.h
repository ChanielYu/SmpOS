/*
*********************************************************************************************************
*                                               SmpOS
*                                        The Real-Time Kernel
*
*                         (c) Copyright 2013-2083, Changzhi Yu
*                                          All Rights Reserved
*
* File         : SmpOS_Core.h
*********************************************************************************************************
*/

#if !defined __SMPOS_CORE_H__
#define __SMPOS_CORE_H__

/*
*********************************************************************************************************

SmpOS_Thread
SmpOS_Core

*********************************************************************************************************
*/

/* running, ready, waiting, start, done */
typedef enum
{
	SMPOSTHREAD_DONE = 0,
	SMPOSTHREAD_READY,
	SMPOSTHREAD_WAITING,
	SMPOSTHREAD_START,
	SMPOSTHREAD_RUNNING
} SMPOS_THREADSTAT;

typedef struct smpos_tcb
{
	ARM_CONTEXT ARMcontext;
	SMPOS_THREADSTAT Status; 			/* Task status                                                  */
	VOID* pThread;
	UINT32 Delay; 						/* Nbr ticks to delay task or, timeout waiting for event */
    UINT8 Prio; 						/* Task priority (0 == highest, 255 == lowest)                   */
	BOOL Finished;
#if 0
	/* Pointer to current top of stack */
	SMPOS_STK* pStackPointer;
#if OS_TASK_CREATE_EXT_EN > 0
    void          *OSTCBExtPtr;        /* Pointer to user definable data for TCB extension             */
    OS_STK        *OSTCBStkBottom;     /* Pointer to bottom of stack                                   */
    INT32U         OSTCBStkSize;       /* Size of task stack (in number of stack elements)             */
    INT16U         OSTCBOpt;           /* Task options as passed by OSTaskCreateExt()                  */
    INT16U         OSTCBId;            /* Task ID (0..65535)                                           */
#endif

    struct os_tcb *OSTCBNext;          /* Pointer to next     TCB in the TCB list                      */
    struct os_tcb *OSTCBPrev;          /* Pointer to previous TCB in the TCB list                      */

#if ((OS_Q_EN > 0) && (OS_MAX_QS > 0)) || (OS_MBOX_EN > 0) || (OS_SEM_EN > 0) || (OS_MUTEX_EN > 0)
    OS_EVENT      *OSTCBEventPtr;      /* Pointer to event control block                               */
#endif

#if ((OS_Q_EN > 0) && (OS_MAX_QS > 0)) || (OS_MBOX_EN > 0)
    void          *OSTCBMsg;           /* Message received from OSMboxPost() or OSQPost()              */
#endif

#if (OS_VERSION >= 251) && (OS_FLAG_EN > 0) && (OS_MAX_FLAGS > 0)
#if OS_TASK_DEL_EN > 0
    OS_FLAG_NODE  *OSTCBFlagNode;      /* Pointer to event flag node                                   */
#endif    
    OS_FLAGS       OSTCBFlagsRdy;      /* Event flags that made task ready to run                      */
#endif

    INT16U         OSTCBDly;           /* Nbr ticks to delay task or, timeout waiting for event        */
    INT8U          OSTCBStat;          /* Task status                                                  */
    INT8U          OSTCBPrio;          /* Task priority (0 == highest, 63 == lowest)                   */

    INT8U          OSTCBX;             /* Bit position in group  corresponding to task priority (0..7) */
    INT8U          OSTCBY;             /* Index into ready table corresponding to task priority        */
    INT8U          OSTCBBitX;          /* Bit mask to access bit position in ready table               */
    INT8U          OSTCBBitY;          /* Bit mask to access bit position in ready group               */

#if OS_TASK_DEL_EN > 0
    BOOLEAN        OSTCBDelReq;        /* Indicates whether a task needs to delete itself              */
#endif
#endif
} SMPOS_TCB,*PSMPOS_TCB;

typedef struct smpos_thread
{
	SMPOS_TCB SmpOStcb;
	struct smpos_thread* pPrev;
	struct smpos_thread* pNext;
	BOOL inUse;
} SMPOS_THREAD,*PSMPOS_THREAD;

VOID SmpOS_CoreInit(VOID);
PSMPOS_THREAD SmpOS_CoreObtainThreadList(VOID);
BOOL SmpOS_CoreFreeThreadList(PSMPOS_THREAD pThread);
SMPOSERR SmpOS_CoreAddToReadyList(PSMPOS_THREAD pThread);
SMPOSERR SmpOS_CoreDelFromReadyList(PSMPOS_THREAD pThread);
SMPOSERR SmpOS_CoreNextReady(VOID);
PSMPOS_TCB SmpOS_CoreGetCurTCB(VOID);

#endif /*  __SMPOS_CORE_H__ */

