/*
*********************************************************************************************************
*                                               SmpOS
*                                        The Real-Time Kernel
*
*                         (c) Copyright 2013-2083, Changzhi Yu
*                                          All Rights Reserved
*
* File         : SmpOS_Kernel.h
*********************************************************************************************************
*/

#if !defined __SMPOS_KERNEL_H__
#define __SMPOS_KERNEL_H__

#define OS_ENTER_CRITICAL() EnterCritical()
#define OS_EXIT_CRITICAL() ExitCritical()

//SMPOSEXT PSMPOS_TCB pSmpOS_CurTCB;
//SMPOSEXT PSMPOS_TCB pSmpOS_RdyTCB;

VOID SmpOS_KernelInit(VOID);
VOID SmpOS_KernelStart(VOID);
VOID SmpOS_KernelSched(VOID);
VOID SmpOS_KernelSleep(UINT32 tick);

#endif /* __SMPOS_KERNEL_H__ */

