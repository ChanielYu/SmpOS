;********************************************************************************************************
;*                                               SmpOS
;*                                        The Real-Time Kernel
;*
;*                         (c) Copyright 2013-2083, Changzhi Yu
;*                                          All Rights Reserved
;*
;* File         : SmpOS_Svc.s
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

SVC_MAXSERVICE 	EQU 	0x00000004

	IMPORT StartRdyThread
	IMPORT IntContexSwitch
	EXPORT VectSvc

	AREA SVC, CODE, READONLY
	
VectSvc
	STMFD	SP!,{R0-R12,LR}
	; The follow three lines load LR from stack, now we load LR directly
	;MOV 	a1,#13
	;LDR 	a2,[SP,a1,LSL #2]
	;LDRH 	a1,[a2,#-4]
	
	MRS 	v1,SPSR
	TST 	v1,#T_BIT
	LDRNEB 	v2,[LR,#-2]
	LDREQH 	v2,[LR,#-4]
	B 		SvcProc

SvcProc
	CMP 	v2,#SVC_MAXSERVICE
	BHI 	SvcReturn
	ADR 	v3,SvcSwitchTab
	LDR 	v4,[v3,v2,LSL #2]
	MOV 	PC,v4
Svc0
; Enter SYS mode from USR mode, only call this service in USR mode!
	MRS 	v1,SPSR 							; Pickup current CPSR
	BIC 	v1,v1,#MOD_MASK 					; Clear the mode bits
	ORR 	v1,v1,#SYS_MODE 					; Set the supervisor mode bits
	MSR 	SPSR_cxsf,v1
	B 		SvcReturn
Svc1
; Enable CPU IRQ
	MRS 	v1,SPSR 							; Pickup current CPSR
	BIC 	v1,v1,#INT_BIT 						; Clear the interrupt bits
	MSR 	SPSR_cxsf,v1
	B 		SvcReturn
Svc2
; Disable CPU IRQ
	MRS 	v1,SPSR 							; Pickup current CPSR
	ORR 	v1,v1,#INT_BIT 						; Clear the interrupt bits
	MSR 	SPSR_cxsf,v1
	B 		SvcReturn
Svc3
; Perform a user context switch this will not return!
	LDMFD 	SP!,{R0-R12,LR} 	; Restroe SVC mode stack
	B 		IntContexSwitch

Svc4
; Perform a user context switch this will not return!
	LDMFD	SP!,{R0-R12,LR} 	; Restroe SVC mode stack
	B		StartRdyThread

SvcReturn
	LDMFD 	SP!,{R0-R12,PC}^

SvcSwitchTab
	DCD 	Svc0
	DCD 	Svc1
	DCD 	Svc2
	DCD 	Svc3
	DCD 	Svc4

	END
