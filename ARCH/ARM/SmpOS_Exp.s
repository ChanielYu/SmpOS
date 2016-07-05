;********************************************************************************************************
;*                                               SmpOS
;*                                        The Real-Time Kernel
;*
;*                         (c) Copyright 2013-2083, Changzhi Yu
;*                                          All Rights Reserved
;*
;* File         : SmpOS_Exp.s
;********************************************************************************************************

USR_MODE 		EQU 	0x10 				; User mode
FIQ_MODE		EQU 	0x11 				; Fast Interrupt Mode (FIQ)
IRQ_MODE		EQU 	0x12				; Interrupt Mode (IRQ)
SVC_MODE		EQU 	0x13				; Supervisor Mode (SVC)
ABT_MODE		EQU 	0x17				; Abort Mode (Abort)
UND_MODE		EQU 	0x1B				; Undefine Mode (Undefine)
SYS_MODE		EQU 	0x1F 				; System mode
MOD_MASK		EQU 	0x1F				; Processor Mode Mask

	AREA EXP, CODE, READONLY
	
	EXPORT VectUnd
	EXPORT VectPre
	EXPORT VectAbt
	EXPORT ImgLen

VectUnd
	STMFD 	SP!,{R0-R12,LR}
	LDMFD 	SP!,{R0-R12,PC}^

VectPre
	STMFD 	SP!,{R0-R12,LR}
	LDMFD 	SP!,{R0-R12,LR}
	SUBS 	PC,LR,#4

VectAbt
	STMFD 	SP!,{R0-R12,LR}
	LDMFD 	SP!,{R0-R12,LR}
	SUBS 	PC,LR,#8

ImgLen
	DCD 0x100000

	END