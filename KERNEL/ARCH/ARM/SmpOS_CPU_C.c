/*
*********************************************************************************************************
*                                               SmpOS
*                                        The Real-Time Kernel
*
*                         (c) Copyright 2013-2083, Changzhi Yu
*                                          All Rights Reserved
*
* File         : SmpOS_CPU.c
*********************************************************************************************************
*/

#include <SmpOS.h>


VOID SmpOS_ARMContextInit(THREADPROC ThreadProc, VOID* pArg, SMPOS_STK* pStack, PARM_CONTEXT pARMcontext)
{
#if 0
	pARMcontext->CPSR = (UINT32)0x00000000L|USR_MODE;/* CPSR  (USR mode, Enable both IRQ and FIQ interrupts) */
	pARMcontext->R0 = (UINT32)pArg; 					/* R0 : argument */
	pARMcontext->R1 = (UINT32)0; 					/* R1  */
	pARMcontext->R2 = (UINT32)0; 					/* R2  */
	pARMcontext->R3 = (UINT32)0; 					/* R3  */
	pARMcontext->R4 = (UINT32)0; 					/* R4  */
	pARMcontext->R5 = (UINT32)0; 					/* R5  */
	pARMcontext->R6 = (UINT32)0; 					/* R6  */
	pARMcontext->R7 = (UINT32)0; 					/* R7  */
	pARMcontext->R8 = (UINT32)0; 					/* R8  */
	pARMcontext->R9 = (UINT32)0; 					/* R9  */
	pARMcontext->R10 = (UINT32)0; 					/* R10 */
	pARMcontext->R11 = (UINT32)0; 					/* R11 */
	pARMcontext->ARMcontext.R12 = (UINT32)0; 					/* R12 */
	pARMcontext->ARMcontext.SP = (UINT32)ptos; 					/* R13 SP */
	pARMcontext->ARMcontext.LR = (UINT32)0; 					/* R14 LR */
	pARMcontext->ARMcontext.PC = (SMPOS_STK)ThreadProc; 			/* R15 PC (Entry Point) */
#else
	pARMcontext->CPSR = (UINT32)0x00000000L|USR_MODE;/* CPSR  (USR mode, Enable both IRQ and FIQ interrupts) */
	pARMcontext->R0 = (UINT32)pArg; 					/* R0 : argument */
	pARMcontext->R1 = (UINT32)0x01; 					/* R1  */
	pARMcontext->R2 = (UINT32)0x02; 					/* R2  */
	pARMcontext->R3 = (UINT32)0x03; 					/* R3  */
	pARMcontext->R4 = (UINT32)0x04; 					/* R4  */
	pARMcontext->R5 = (UINT32)0x05; 					/* R5  */
	pARMcontext->R6 = (UINT32)0x06; 					/* R6  */
	pARMcontext->R7 = (UINT32)0x07; 					/* R7  */
	pARMcontext->R8 = (UINT32)0x08; 					/* R8  */
	pARMcontext->R9 = (UINT32)0x09; 					/* R9  */
	pARMcontext->R10 = (UINT32)0x10; 					/* R10 */
	pARMcontext->R11 = (UINT32)0x11; 					/* R11 */
	pARMcontext->R12 = (UINT32)0x12; 					/* R12 */
	pARMcontext->SP = (UINT32)pStack; 					/* R13 SP */
	pARMcontext->LR = (UINT32)0x14; 					/* R14 LR */
	pARMcontext->PC = (SMPOS_STK)ThreadProc; 			/* R15 PC (Entry Point) */
#endif
}

VOID SmpOS_ARMContextEndProc(THREADPROC postProc, PARM_CONTEXT pARMcontext)
{
	pARMcontext->LR = (UINT32)postProc; 			/* R14 LR */
}

