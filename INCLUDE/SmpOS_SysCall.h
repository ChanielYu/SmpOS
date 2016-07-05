/*
*********************************************************************************************************
*                                               SmpOS
*                                        The Real-Time Kernel
*
*                         (c) Copyright 2013-2083, Changzhi Yu
*                                          All Rights Reserved
*
* File         : SmpOS_SysCall.h
*********************************************************************************************************
*/

VOID EnterSysMode(VOID);

#if OS_CRITICAL_METHOD == 0

VOID EnterCritical(VOID);
VOID ExitCritical(VOID);

#else
#error OS_CRITICAL_METHOD code does not support!
#endif

VOID SmpOS_StartThread(VOID);
VOID SmpOS_ContextSwitch(VOID);

