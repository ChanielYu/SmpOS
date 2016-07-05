;********************************************************************************************************
;*                                               SmpOS
;*                                        The Real-Time Kernel
;*
;*                         (c) Copyright 2013-2083, Changzhi Yu
;*                                          All Rights Reserved
;*
;* File         : SmpOS_SysCall.s
;********************************************************************************************************

SYSCALL_USRENTERSYS 		EQU 	0x00000000
SYSCALL_ENABLEIRQ			EQU 	0x00000001
SYSCALL_DISABLEIRQ			EQU 	0x00000002
SYSCALL_CONTEXTSWITCH		EQU 	0x00000003
SYSCALL_STRATRDYTHREAD 		EQU 	0x00000004

	AREA SYSCALL, CODE, READONLY

	GLOBAL EnterSysMode
EnterSysMode
	SWI SYSCALL_USRENTERSYS
	MOV PC,LR

	GLOBAL EnterCritical
EnterCritical
	SWI SYSCALL_DISABLEIRQ
	MOV PC,LR

	GLOBAL ExitCritical
ExitCritical
	SWI SYSCALL_ENABLEIRQ
	MOV PC,LR

	GLOBAL SmpOS_ContextSwitch
SmpOS_ContextSwitch
	SWI SYSCALL_CONTEXTSWITCH
	MOV PC,LR

	GLOBAL SmpOS_StartThread
SmpOS_StartThread
	SWI SYSCALL_STRATRDYTHREAD
	MOV PC,LR

	

	END
