;********************************************************************************************************
;*                                               SmpOS
;*                                        The Real-Time Kernel
;*
;*                         (c) Copyright 2013-2083, Changzhi Yu
;*                                          All Rights Reserved
;*
;* File         : SmpOS_Irq.s
;********************************************************************************************************

USR_MODE 		EQU 	0x10 				; User mode
FIQ_MODE		EQU 	0x11 				; Fast Interrupt Mode (FIQ)
IRQ_MODE		EQU 	0x12				; Interrupt Mode (IRQ)
SVC_MODE		EQU 	0x13				; Supervisor Mode (SVC)
ABT_MODE		EQU 	0x17				; Abort Mode (Abort)
UND_MODE		EQU 	0x1B				; Undefine Mode (Undefine)
SYS_MODE		EQU 	0x1F 				; System mode
MOD_MASK		EQU 	0x1F				; Processor Mode Mask

INT_STATUS		EQU 	0x0A000000	; Interrupt status read only

	IMPORT SmpOS_CoreNextReady
	IMPORT IntContexSwitch
	IMPORT ClearTimer1

	EXPORT VectIrq
	
	AREA IRQ, CODE, READONLY

VectIrq
	SUB 	LR,LR,#4
	STMFD 	SP!,{R0-R12,LR}
	MOV 	a2,#INT_STATUS
	LDR 	a1,[a2]
;switchcontext
	IMPORT SmpOS_CoreIntTimeTick
	BL 		SmpOS_CoreIntTimeTick
	BL 		SmpOS_CoreNextReady
	CMP 	a1, #0
	BL 		ClearTimer1
	BNE 	exitIRQ
	LDMFD 	SP!,{R0-R12,LR}
	B 		IntContexSwitch
exitIRQ
	;BL 		IRQ rpitine; Clear corresponse interrupt
	LDMFD 	SP!,{R0-R12,PC}^

	END
