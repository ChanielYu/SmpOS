/*
*********************************************************************************************************
*                                               SmpOS
*                                        The Real-Time Kernel
*
*                         (c) Copyright 2013-2083, Changzhi Yu
*                                          All Rights Reserved
*
* File         : SmpOS_Config.h
*********************************************************************************************************
*/

#if !defined __SMPOS_CONFIG_H__
#define __SMPOS_CONFIG_H__
	

#define ARM_ARMULATOR
#define OS_CRITICAL_METHOD 0

//#define UCOSII_COMPATIBLE

#define SMPOSMAXTCBPOOLSIZE 64

#define INITIALTHREADSTACKSIZE 0x2000

#define SYSTEMCLOCK 100 /* PROCESSORCLK */

#endif /* __SMPOS_CONFIG_H__ */

