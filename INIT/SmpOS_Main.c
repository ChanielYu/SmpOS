/*
*********************************************************************************************************
*                                               SmpOS
*                                        The Real-Time Kernel
*
*                         (c) Copyright 2013-2083, Changzhi Yu
*                                          All Rights Reserved
*
* File         : SmpOS_Main.c
*********************************************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SmpOS.h>

//THREADPROC MainThread;
/*
********************************************************************************
* Test only
*/
//#define USER_STACKOFFSET 0x600000+INITIALTHREADSTACKSIZE
#define USER_STACKOFFSET 0x700000

extern SMPOS_STK top_of_stacks;

#define TH2STACKSIZE 0x1000
SMPOS_STK th2stack[TH2STACKSIZE];

VOID SmpOS_Th1(VOID* pd);
VOID SmpOS_Th2(VOID* pd);

/*
********************************************************************************
*/
VOID SmpOS_Main(VOID* pd);

INT32 main(void)
{
	InitIntctrl();
	SetTimer1Interval(2000/*1000/SYSTEMCLOCK*/);
	EnableTimer1();
	EnableIntctrlIRQ(IRQCTRL_TMR1);
	SmpOS_Init();
	SmpOS_ThreadCreate(SmpOS_Main, NULL, (SMPOS_STK*)&top_of_stacks+0x700000/4, SMPOS_THREAD_PRIORITY_NORMAL);
	SmpOS_ThreadCreate(SmpOS_Th1, NULL, (SMPOS_STK*)&top_of_stacks+0x700000/4-1024, SMPOS_THREAD_PRIORITY_NORMAL);
	SmpOS_ThreadCreate(SmpOS_Th2, (VOID*)&th2stack[TH2STACKSIZE], (SMPOS_STK*)th2stack+TH2STACKSIZE, SMPOS_THREAD_PRIORITY_NORMAL);
	SmpOS_Start();
	return 0;
}

