/*
*********************************************************************************************************
*                                               SmpOS
*                                        The Real-Time Kernel
*
*                         (c) Copyright 2013-2083, Changzhi Yu
*                                          All Rights Reserved
*
* File         : SmpOS_CPU.h
*********************************************************************************************************
*/

#if !defined __SMPOS_CPU_H__
#define __SMPOS_CPU_H__

/*
;**********************************************************************************************************
;                                          ARM CPU context
;
; The stack frame is assumed to look as follows:
;
;							    Entry Point(Thread Name)				(High memory)
;                               LR(R14)
;                               SP(R13)
;                               R12
;                               R11
;                               R10
;                               R9
;                               R8
;                               R7
;                               R6
;                               R5
;                               R4
;                               R3
;                               R2
;                               R1
;                               R0 : argument
; OSTCBHighRdy->OSTCBStkPtr --> CPSR								(Low memory)
;
; Note : SmpOS_StartThread() MUST:
;           a) Call SmpOS_ThreadSwHook() then,
;           b) Set SmpOS_Running to TRUE,
;           c) Switch to the highest priority thread.
;**********************************************************************************************************
*/

#define USR_MODE 0x10 			/* User mode */
#define FIQ_MODE 0x11 			/* Fast Interrupt Mode (FIQ) */
#define IRQ_MODE 0x12			/* Interrupt Mode (IRQ) */
#define SVC_MODE 0x13			/* Supervisor Mode (SVC) */
#define ABT_MODE 0x17			/* Abort Mode (Abort) */
#define UND_MODE 0x1B			/* Undefine Mode (Undefine) */
#define SYS_MODE 0x1F 			/* System mode */
#define MOD_MASK 0x1F			/* Processor Mode Mask */

#define I_BIT 0x80 				/* Interrupt bit of CPSR and SPSR */
#define F_BIT 0x40 				/* Interrupt bit of CPSR and SPSR */
#define INT_BIT 0xC0 			/* Interrupt bits */
#define T_BIT 0x20 				/* Thumb mode control bit */

typedef struct arm_context
{
	SMPOS_STK CPSR;
	SMPOS_STK R0;
	SMPOS_STK R1;
	SMPOS_STK R2;
	SMPOS_STK R3;
	SMPOS_STK R4;
	SMPOS_STK R5;
	SMPOS_STK R6;
	SMPOS_STK R7;
	SMPOS_STK R8;
	SMPOS_STK R9;
	SMPOS_STK R10;
	SMPOS_STK R11;
	SMPOS_STK R12;
	SMPOS_STK SP;
	SMPOS_STK LR;
	SMPOS_STK PC;
} ARM_CONTEXT,*PARM_CONTEXT;

VOID SmpOS_ARMContextInit(THREADPROC ThreadProc, VOID* pArg, SMPOS_STK* pStack, PARM_CONTEXT pARMcontext);
VOID SmpOS_ARMContextEndProc(THREADPROC postProc, PARM_CONTEXT pARMcontext);

#endif /* __SMPOS_CPU_H__ */

