;********************************************************************************************************
;*                                               SmpOS
;*                                        The Real-Time Kernel
;*
;*                         (c) Copyright 2013-2083, Changzhi Yu
;*                                          All Rights Reserved
;*
;* File         : SmpOS_CPU.s
;********************************************************************************************************

	IMPORT EnterSysMode
	
	IMPORT pSmpOS_CurTCB;
	IMPORT pSmpOS_RdyTCB;
	
	AREA SMPOS_CPU, CODE, READONLY
;*********************************************************************************************************
;                                          START MULTITASKING
;                                       void SmpOS_StartThread(void)
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
;********************************************************************************************************** */

	EXPORT StartRdyThread
StartRdyThread
	;---------------------------------------------------------------------------
	; pSmpOS_CurTCB = pSmpOS_RdyTCB;
	;---------------------------------------------------------------------------
	LDR		R0, =pSmpOS_RdyTCB
	LDR		R1, =pSmpOS_CurTCB
	LDR		R0, [R0]
	STR		R0, [R1]

	;---------------------------------------------------------------------------
	; Remember ARM CPU is in priviledge mode now!
	; pSmpOS_RdyTCB->ARMcontext to priviledge LR
	;---------------------------------------------------------------------------
	LDR		R0, =pSmpOS_RdyTCB
	LDR		LR, [R0]

	;---------------------------------------------------------------------------
	; Pop user CPSR from user stack which now in LR.
	;---------------------------------------------------------------------------
	LDMFD 	LR!,{R2}
	;---------------------------------------------------------------------------
	; Save to SPSR, when return from priviledge mode it will be restored to user CPSR.
	;---------------------------------------------------------------------------
	MSR 	SPSR_cxsf,R2
	;---------------------------------------------------------------------------
	; Force user mode R0-R14 registers espetialy SP_usr and LR_usr from priviledge mode.
	;---------------------------------------------------------------------------
	LDMFD 	LR,{R0-R14}^
	;---------------------------------------------------------------------------
	; Avoid a warnning.
	;---------------------------------------------------------------------------
	NOP
	;---------------------------------------------------------------------------
	; Read user mode PC.
	;---------------------------------------------------------------------------
	LDR 	LR,[LR,#60]
	;---------------------------------------------------------------------------
	; Here we go! Swich finished return to next user mode context.
	;---------------------------------------------------------------------------
	MOVS 	PC,LR

	EXPORT IntContexSwitch
IntContexSwitch
	;---------------------------------------------------------------------------
	; Save R10,R11,R12 to priviledge mode SP, we will use them.
	;---------------------------------------------------------------------------
	STMFD 	SP!,{R9-R12}
	
	STMFD 	SP,{SP,LR}^ 		; Force USR mode SP,LR to privilege SP
	NOP
	;---------------------------------------------------------------------------
	; Adjust priviledge mode SP
	; because force user mode STM can't write back priviledge SP.
	;---------------------------------------------------------------------------
	SUB 	SP,SP,#8
	;---------------------------------------------------------------------------
	; Pick USR mode SP in R11 and LR in R12
	; Due to last adjustment SP still need to be restored.
	;---------------------------------------------------------------------------
	LDMFD 	SP!,{R11,R12}
	;---------------------------------------------------------------------------
	; ;;;;;;;LDMFD 	SP!,{R19-R12} 		; Restroe privilege mode stack
	; Restroe privilege mode later not now! So we didn't execute last line.
	;---------------------------------------------------------------------------

	;---------------------------------------------------------------------------
	; R12 = pSmpOS_CurTCB->ARMcontext
	;---------------------------------------------------------------------------
	LDR		R10, =pSmpOS_CurTCB
	LDR		R10, [R10]
	;---------------------------------------------------------------------------
	; Push CPSR to user SP which now saved in R10.
	;---------------------------------------------------------------------------
	MRS 	R9,SPSR
	STMIA 	R10!,{R9}
	;---------------------------------------------------------------------------
	; Save user R0-R9 into user SP which now saved in R10.
	;---------------------------------------------------------------------------
	STMIA 	R10!,{R0-R8}
	;---------------------------------------------------------------------------
	; Restroe privilege mode stack by read saved R9-R12 to R0-R3.
	;---------------------------------------------------------------------------
	LDMFD 	SP!,{R0-R3}
	;---------------------------------------------------------------------------
	; Save user R9-R12 into user SP which now saved in R10.
	;---------------------------------------------------------------------------
	STMIA 	R10!,{R0-R3}
	;---------------------------------------------------------------------------
	; Save user SP which now saved in R11 and LR saved in R12 into user SP which now saved in R10.
	;---------------------------------------------------------------------------
	STMIA 	R10!,{R11,R12}
	;---------------------------------------------------------------------------
	; Push user PC which now in priviledge mode LR into user SP which now saved in R10.
	;---------------------------------------------------------------------------
	STMIA 	R10!,{LR}

	;---------------------------------------------------------------------------
	; pSmpOS_CurTCB = pSmpOS_RdyTCB;
	;---------------------------------------------------------------------------
	LDR		R0, =pSmpOS_RdyTCB
	LDR		R1, =pSmpOS_CurTCB
	LDR		R0, [R0]
	STR		R0, [R1]

	;---------------------------------------------------------------------------
	; Remember ARM CPU is in priviledge mode now!
	; pSmpOS_RdyTCB->ARMcontext to priviledge LR
	; Priviledge LR has saved into user mode ARM_CONTEXT as PC
	; So when next time perform the saved user context,
	; it will return from priviledge mode to saved user ARM_CONTEXT.
	;---------------------------------------------------------------------------
	LDR		R0, =pSmpOS_RdyTCB
	LDR		LR, [R0]

	;---------------------------------------------------------------------------
	; Pop user CPSR from user stack which now in LR.
	;---------------------------------------------------------------------------
	LDMFD 	LR!,{R2}
	;---------------------------------------------------------------------------
	; Save to SPSR, when return from priviledge mode it will be restored to user CPSR.
	;---------------------------------------------------------------------------
	MSR 	SPSR_cxsf,R2
	;---------------------------------------------------------------------------
	; Force user mode R0-R14 registers espetialy SP_usr and LR_usr from priviledge mode.
	;---------------------------------------------------------------------------
	LDMFD 	LR,{R0-R14}^
	;---------------------------------------------------------------------------
	; Avoid a warnning.
	;---------------------------------------------------------------------------
	NOP
	;---------------------------------------------------------------------------
	; Read user mode PC.
	;---------------------------------------------------------------------------
	LDR 	LR,[LR,#60]
	;---------------------------------------------------------------------------
	; Here we go! Swich finished return to next user mode context.
	;---------------------------------------------------------------------------
	MOVS 	PC,LR

	END
