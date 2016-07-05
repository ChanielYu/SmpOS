/*
*********************************************************************************************************
*                                               SmpOS
*                                        The Real-Time Kernel
*
*                         (c) Copyright 2013-2083, Changzhi Yu
*                                          All Rights Reserved
*
* File         : SmpOS_Thread.h
*********************************************************************************************************
*/

#if !defined __SMPOS_THREAD_H__
#define __SMPOS_THREAD_H__

#define SMPOS_THREAD_PRIORITY_HIGHEST 	50
#define SMPOS_THREAD_PRIORITY_HIGH 		90
#define SMPOS_THREAD_PRIORITY_NORMAL 	130
#define SMPOS_THREAD_PRIORITY_LOW		170
#define SMPOS_THREAD_PRIORITY_LOWEST 	210

SMPOSHANDLE SmpOS_ThreadCreate(THREADPROC thread, VOID* pdata, SMPOS_STK* ptos, UINT8 prio);

#endif /* __SMPOS_THREAD_H__ */

