/*
*********************************************************************************************************
*                                               SmpOS
*                                        The Real-Time Kernel
*
*                         (c) Copyright 2013-2083, Changzhi Yu
*                                          All Rights Reserved
*
* File         : SmpOS.h
*********************************************************************************************************
*/

#if !defined __SMPOS_H__
#define __SMPOS_H__

#include <SmpOS_Config.h>
#include <SmpOS_Type.h>
#include <SmpOS_Error.h>

#include <SmpOS_CPU.h>
#include <SmpOS_SysCall.h>

#include <SmpOS_Kernel.h>

#include <SmpOS_Thread.h>

/*
*********************************************************************************************************
*********************************************************************************************************
*/

#if defined ARCH_ARM

#elif defined __TARGET_ARCH_5TE

#ifdef ARM_ARMULATOR

#include <SmpOS_ARMulator.h>

#else /* ARM_ARMULATOR */
#error Configure an ARM architecture!
#endif /* ARM_ARMULATOR */

#else /* ARCH_ARM */
#error Configure an ARCH!
#endif /* ARCH_ARM */

/*
*********************************************************************************************************
*********************************************************************************************************
*/

VOID SmpOS_Init(VOID);
VOID SmpOS_Start(VOID);

#endif /* __SMPOS_H__ */

