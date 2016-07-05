/*
*********************************************************************************************************
*                                               SmpOS
*                                        The Real-Time Kernel
*
*                         (c) Copyright 2013-2083, Changzhi Yu
*                                          All Rights Reserved
*
* File         : SmpOS_ARMulator.c
*********************************************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SmpOS.h>
#include <SmpOS_ARMulator.h>

VOID InitIntctrl(VOID)
{
	PREGINTCTRL pIntCtrl;
	pIntCtrl = (PREGINTCTRL)IRQ_BASE;
	pIntCtrl->DISABLE = 1;
	pIntCtrl = (PREGINTCTRL)FIQ_BASE;
	pIntCtrl->DISABLE = 1;
}

UINT32 GetIntctrlStatus(VOID)
{
	PREGINTCTRL pIntCtrl;
	pIntCtrl = (PREGINTCTRL)IRQ_BASE;
	return pIntCtrl->STATUS;
}

VOID EnableIntctrlIRQ(UINT32 IrqVect)
{
	PREGINTCTRL pIntCtrl;
	pIntCtrl = (PREGINTCTRL)IRQ_BASE;
	pIntCtrl->ENABLE |= IrqVect;
}

VOID DisableIntctrlIRQ(UINT32 IrqVect)
{
	PREGINTCTRL pIntCtrl;
	pIntCtrl = (PREGINTCTRL)IRQ_BASE;
	pIntCtrl->DISABLE &= ~IrqVect;
}

VOID SoftIntctrlIRQ(UINT32 IrqVect)
{
	PREGINTCTRL pIntCtrl;
	pIntCtrl = (PREGINTCTRL)IRQ_BASE;
	pIntCtrl->SOFTINT = IrqVect;
}

VOID SetTimer1Interval(UINT32 ms)
{
	UINT32 counter;
	PREGTIMER pTimer;
	pTimer = (PREGTIMER)TIMER1_BASE;
	counter = PROCESSORCLK/1000/256/8;
	pTimer->TIMER_LOAD = counter*ms;
}

VOID EnableTimer1(VOID)
{
	PREGTIMER pTimer;
	pTimer = (PREGTIMER)TIMER1_BASE;
	pTimer->TIMER_CTRL = 0x000000C8;
}

VOID ClearTimer1(VOID)
{
	PREGTIMER pTimer;
	pTimer = (PREGTIMER)TIMER1_BASE;
	pTimer->TIMER_CLEAR = 1;
}

VOID EnableTimer2(VOID)
{
	PREGTIMER pTimer;
	pTimer = (PREGTIMER)TIMER2_BASE;
	pTimer->TIMER_LOAD = 0x0000FFFF;
	pTimer->TIMER_CTRL = 0x000000C8;
}

#if 0
InterrutInit
	MOV 	a2,#INT_STATUS
	LDR 	a1,[a2]
	ADD 	a2,a2,#8
	LDR 	a1,[a2]
	MOV 	a1,#0x10
	STR 	a1,[a2] 		; Enable interrupt.
	MOV 	a1,#0 			; Check whether inerrupt enabled.
	LDR 	a1,[a2]
	ADD 	a2,a2,#8
	STR 	a1,[a2] 		; Enable timer interrupt.
	MOV 	PC,LR

EnableTimer1
	LDR 	a1,timer_full
	LDR 	a2,TIMER_LOAD
	STR 	a1,[a2]
	MOV 	a1,#0xC8
	LDR 	a2,TIMER_CTRL
	STR 	a1,[a2]
	MOV 	PC,LR

ClearTimer1
	STMFD 	SP!, {R0,LR}
	LDR 	LR, TIMER_CLEAR
	MOV 	R0, #1
	STR 	R0, [LR]
	LDMFD 	SP!, {R0,LR}
	MOV 	PC,LR

TIMER_LOAD		DCD 0x0A800000
TIMER_VALUE 	DCD 0x0A800004
TIMER_CTRL		DCD 0x0A800008
TIMER_CLEAR 	DCD 0x0A80000C
timer_full		DCD 0x0000FFFF

#endif

