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

#include <SmpOS_Include.h>

#define THSTACKSIZE 0x1000
SMPOS_STK thstack[THSTACKSIZE];

VOID ThumbThread(VOID* pd);

INT32 swap(PINT32 a ,PINT32 b)
{
	*a^=*b;
	*b^=*a;
	*a^=*b;
	return 0;
}

VOID SmpOS_Main(VOID* pd)
{
	int a=0,b=0x80000000;
	while(1)
	{
		swap(&a,&b);
		a++;
	}
}

VOID SmpOS_Th1(VOID* pd)
{
	int a=0,b=0x80000000;
	while(1)
	{
		swap(&a,&b);
		SmpOS_KernelSleep(2);
		a++;
	}
}

VOID SmpOS_Th2(VOID* pd)
{
	int a=0,b=0x80000000;
	SmpOS_ThreadCreate(ThumbThread, NULL, (SMPOS_STK*)thstack+THSTACKSIZE, 0);
	while(1)
	{
		swap(&a,&b);
		a++;
	}
}

__align(2)
//asm("	CODE16")

VOID ThumbThread(VOID* pd)
{
	int a=1,b=9;
	while(1)
	{
		swap(&a,&b);
	}
}

//__align(2)
//asm(" CODE32")

