;********************************************************************************************************
;*                                               SmpOS
;*                                        The Real-Time Kernel
;*
;*                         (c) Copyright 2013-2083, Changzhi Yu
;*                                          All Rights Reserved
;*
;* File         : SmpOS_Init.s
;********************************************************************************************************

USR_MODE 		EQU 	0x10 				; User mode
FIQ_MODE		EQU 	0x11 				; Fast Interrupt Mode (FIQ)
IRQ_MODE		EQU 	0x12				; Interrupt Mode (IRQ)
SVC_MODE		EQU 	0x13				; Supervisor Mode (SVC)
ABT_MODE		EQU 	0x17				; Abort Mode (Abort)
UND_MODE		EQU 	0x1B				; Undefine Mode (Undefine)
SYS_MODE		EQU 	0x1F 				; System mode
MOD_MASK		EQU 	0x1F				; Processor Mode Mask

I_BIT 			EQU 	0x80 				; Interrupt bit of CPSR and SPSR
F_BIT 			EQU 	0x40 				; Interrupt bit of CPSR and SPSR
INT_BIT 		EQU 	0xC0 				; Interrupt bits
T_BIT 			EQU 	0x20 				; Thumb mode control bit

	IF :DEF:SCATTER
	IMPORT ||Image$$SVC_STACKS$$Base||
	IMPORT ||Image$$SVC_STACKS$$Limit||
	
	IMPORT ||Image$$IRQ_STACKS$$Base||
	IMPORT ||Image$$IRQ_STACKS$$Limit||

	IMPORT ||Image$$FIQ_STACKS$$Base||
	IMPORT ||Image$$FIQ_STACKS$$Limit||
	
	IMPORT ||Image$$ABT_STACKS$$Base||
	IMPORT ||Image$$ABT_STACKS$$Limit||

	IMPORT ||Image$$UND_STACKS$$Base||
	IMPORT ||Image$$UND_STACKS$$Limit||

	IMPORT ||Image$$SYS_STACKS$$Base||
	IMPORT ||Image$$SYS_STACKS$$Limit||
	ENDIF

Len_FIQ_Stack 		EQU 	0x100000
Len_IRQ_Stack 		EQU 	0x100000
Len_ABT_Stack 		EQU 	0x100000
Len_UND_Stack 		EQU 	0x100000
Len_SVC_Stack 		EQU 	0x100000
Len_USR_Stack 		EQU 	0x100000

Offset_FIQ_Stack 	EQU 	Len_FIQ_Stack
Offset_IRQ_Stack 	EQU 	Offset_FIQ_Stack + Len_IRQ_Stack
Offset_ABT_Stack 	EQU 	Offset_IRQ_Stack + Len_ABT_Stack
Offset_UND_Stack 	EQU 	Offset_ABT_Stack + Len_UND_Stack
Offset_SVC_Stack 	EQU 	Offset_UND_Stack + Len_SVC_Stack
Offset_USR_Stack 	EQU 	Offset_SVC_Stack + Len_USR_Stack

	;IMPORT INT_Vectors
	
	GLOBAL VextRst
	
	AREA INIT, CODE, READONLY
	ENTRY	
ResetInitialize
VextRst
	; Copy Interrupt vector fast in use
	; C library __main will copy all code and data from load view to run view.
	; We don't need do it by ourselves with ADS.
	;MOV 	R8,#0x00000000
	;LDR 	R9,=INT_Vectors
	;LDMIA 	R9!,{R0-R7}
	;STMIA 	R8!,{R0-R7}
	;LDMIA 	R9!,{R0-R7}
	;STMIA 	R8!,{R0-R7}
;StackInit
	IMPORT top_of_stacks 		; defined in stack.s and located by scatter file
	LDR 	R0, =top_of_stacks

	MSR 	CPSR_c, #FIQ_MODE:OR:INT_BIT ; No interrupts
	ADD 	SP, R0, #Offset_FIQ_Stack
	
	MSR 	CPSR_c, #IRQ_MODE:OR:INT_BIT ; No interrupts
	ADD 	SP, R0, #Offset_IRQ_Stack

	MSR 	CPSR_c, #ABT_MODE:OR:INT_BIT ; No interrupts
	ADD 	SP, R0, #Offset_ABT_Stack

	MSR 	CPSR_c, #UND_MODE:OR:INT_BIT ; No interrupts
	ADD 	SP, R0, #Offset_UND_Stack

    MSR 	CPSR_c, #SVC_MODE:OR:INT_BIT ; No interrupts
    ADD 	SP, R0, #Offset_SVC_Stack

    MSR     CPSR_c, #USR_MODE:OR:F_BIT 		; IRQs now enabled
	ADD     SP, R0, #Offset_USR_Stack

	IMPORT __main
	B 		__main

	END

