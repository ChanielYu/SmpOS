;-------------------------------------------------------------------------------
; Task switch sample code.
;
;
;-------------------------------------------------------------------------------

USR_MODE		EQU 	0x10				; User mode
FIQ_MODE		EQU 	0x11				; Fast Interrupt Mode (FIQ)
IRQ_MODE		EQU 	0x12				; Interrupt Mode (IRQ)
SVC_MODE		EQU 	0x13				; Supervisor Mode (SVC)
ABT_MODE		EQU 	0x17				; Abort Mode (Abort)
UND_MODE		EQU 	0x1B				; Undefine Mode (Undefine)
SYS_MODE		EQU 	0x1F				; System mode
MOD_MASK		EQU 	0x1F				; Processor Mode Mask

I_BIT			EQU 	0x80				; Interrupt bit of CPSR and SPSR
F_BIT			EQU 	0x40				; Interrupt bit of CPSR and SPSR
INT_BIT 		EQU 	0xC0				; Interrupt bits
T_BIT			EQU 	0x20				; Thumb mode control bit

	;IMPORT
	GLOBAL CreateTask
	GLOBAL StartTask
	GLOBAL IntContexSwitch

	AREA TEXT, CODE, READONLY
	
CreateTask
	MOV a1,#0x11
	MOV a2,#0x22
	MOV a3,#0x33
	MOV a4,#0x44
	MOV v1,#0x55
	MOV v2,#0x66
	MOV v3,#0x77
	MOV v4,#0x88
	MOV v5,#0x99
	MOV v6,#0xAA
	MOV v7,#0xBB
	MOV v8,#0xCC
	MOV ip,#0xDD
	STMFD SP!,{R0-R12}
	
	LDR 	a1,task1sp
	MOV 	a2,SP
	ADR 	a3,Task1
	;LDR 	a3,=Task1
	STMFD 	a1!,{a3} ; Push PC
	STMFD 	a1!,{LR} ; Push LR it should be 0 cause it doesn't need to return, whien inintializing just set it = PC
	LDR 	a3,task1sp
	STMFD 	a1!,{a3} ; Push SP
	STMFD 	a1!,{R3-R12} ; Push R3-R12
	LDMFD 	a2!,{v1-v3} ; Load last R0-R2 registers means
	STMFD 	a1!,{v1-v3}
	; Make CPSR for task
	LDR 	IP,=Task1
	TST 	IP,#0x00000001
	MRS 	v1,CPSR
	BIC 	v1,v1,#MOD_MASK 					; Clear the mode bits
	ORR 	v1,v1,#USR_MODE 					; Set the user mode bits
	BIC 	v1,v1,#INT_BIT 						; Insure IRQ/FIQ interrupts are enabled
	BEQ 	%F1
	MOV 	v2,#T_BIT
	ORR 	v1,v1,v2
1
	STMFD 	a1!,{v1} ; Push CPSR
	STR 	a1,task1cb

	LDMFD SP,{R0-R12}
	LDR 	a1,task2sp
	MOV 	a2,SP
	ADR 	a3,Task2
	;LDR 	a3,=Task2
	STMFD 	a1!,{a3} ; Push PC
	STMFD 	a1!,{LR} ; Push LR it should be 0 cause it doesn't need to return, whien inintializing just set it = PC
	LDR 	a3,task2sp
	STMFD 	a1!,{a3} ; Push SP
	STMFD 	a1!,{R3-R12} ; Push LR it should be 0 cause it doesn't need to return, whien inintializing just set it = PC
	LDMFD 	a2!,{v1-v3} ; Load last 6 registers means R12,11,10,9,8,7
	STMFD 	a1!,{v1-v3}
	; Make CPSR for task
	LDR 	IP,=Task2
	TST 	IP,#0x00000001
	MRS 	v1,CPSR
	BIC 	v1,v1,#MOD_MASK 					; Clear the mode bits
	ORR 	v1,v1,#USR_MODE 					; Set the user mode bits
	BIC 	v1,v1,#INT_BIT 						; Insure IRQ/FIQ interrupts are enabled
	BEQ 	%F1
	MOV 	v2,#T_BIT
	ORR 	v1,v1,v2
1
	STMFD 	a1!,{v1} ; Push CPSR
	STR 	a1,task2cb

	LDMFD SP,{R0-R12}
	LDR 	a1,task3sp
	MOV 	a2,SP
	ADR 	a3,Task3
	;LDR 	a3,=Task3
	STMFD 	a1!,{a3} ; Push PC
	STMFD 	a1!,{LR} ; Push LR it should be 0 cause it doesn't need to return, whien inintializing just set it = PC
	LDR 	a3,task3sp
	STMFD 	a1!,{a3} ; Push SP
	STMFD 	a1!,{R3-R12} ; Push LR it should be 0 cause it doesn't need to return, whien inintializing just set it = PC
	LDMFD 	a2!,{v1-v3} ; Load last 6 registers means R12,11,10,9,8,7
	STMFD 	a1!,{v1-v3}
	; Make CPSR for task
	LDR 	IP,=Task3
	TST 	IP,#0x00000001
	MRS 	v1,CPSR
	BIC 	v1,v1,#MOD_MASK 					; Clear the mode bits
	ORR 	v1,v1,#USR_MODE 					; Set the user mode bits
	BIC 	v1,v1,#INT_BIT 						; Insure IRQ/FIQ interrupts are enabled
	BEQ 	%F1
	MOV 	v2,#T_BIT
	ORR 	v1,v1,v2
1
	STMFD 	a1!,{v1} ; Push CPSR
	STR 	a1,task3cb

	LDMFD SP!,{R0-R12}
	MOV 	PC,LR

StartTask
	MSR 	CPSR_c,#SVC_MODE|INT_BIT ; Change to SVC mode.
	LDR 	a1,taskcb
	LDR 	a2,CurTask
	LDR 	LR,[a1,a2,LSL #2]
	LDMFD 	LR!,{a3}
	MSR 	SPSR_cxsf,a3
	LDMFD 	LR,{R0-R14}^
	NOP
	LDR 	LR,[LR,#60]
	MOVS 	PC,LR

IntContexSwitch
	LDMFD 	SP!,{R0-R12,LR} 	; Restroe SVC mode stack

	STMFD 	SP!,{R0-R2}
	STMFD 	SP,{SP,LR}^ 		; Force USR mode SP,LR to privilege SP
	NOP
	SUB 	SP,SP,#8
	LDMFD 	SP!,{a1,a3} 		; Pick USR mode SP and LR
	;LDMFD 	SP!,{R0-R2} 		; Restroe privilege mode stack

	MOV 	a2,a1 	;Save USR SP to a2.
	STMFD 	a1!,{LR} ; Push PC
	STMFD 	a1!,{a3} ; Push LR it should be 0 cause it doesn't need to return, whien inintializing just set it = PC
	STMFD 	a1!,{a2} ; Push USR SP
	STMFD 	a1!,{R3-R12} ; Push LR it should be 0 cause it doesn't need to return, whien inintializing just set it = PC
	LDMFD 	SP!,{v1-v3}
	STMFD 	a1!,{v1-v3}
	MRS 	v1,SPSR
	STMFD 	a1!,{v1} ; Push CPSR
	MOV 	v1,a1

	LDR 	a1,taskcb
	LDR 	a2,CurTask
	STR 	v1,[a1,a2,LSL #2]
	ADD 	a2,a2,#1
	CMP 	a2,#2
	MOVHI	a2,#0
	STR 	a2,CurTask 				; Save current tast's sp to TCB.
	LDR 	LR,[a1,a2,LSL #2]
	LDMFD 	LR!,{a3}
	MSR 	SPSR_cxsf,a3
	LDMFD 	LR,{R0-R14}^
	NOP
	LDR 	LR,[LR,#60]
	MOVS 	PC,LR
	
	ALIGN 2
	CODE16
Task1
	MOV 	a1,#0x10
task1loop
	ADD 	a1,a1,#1
	SWI 	0xFF
	B 		task1loop
Task2
	MOV 	a1,#0x20
	SWI 	0x000001
task2loop
	ADD 	a1,a1,#1
	SWI 	0xFF
	B 		task2loop
	
	ALIGN 2
	CODE32
Task3
	MOV 	a1,#0x30
	;SWI 	0x000002
task3loop
	ADD 	a1,a1,#1
	SWI 	0xFF
	B 		task3loop

	AREA |DATA|,DATA, READWRITE

task1sp 	DCD 	0x00710000
task2sp 	DCD 	0x00720000
task3sp 	DCD 	0x00730000
Compare 	DCD 	0x0000000F
	
	EXPORT 	ARM_THUMB
ARM_THUMB
	DCD 	0
	
	EXPORT 	SwiStackPointer
SwiStackPointer
	DCD 	0
	
	EXPORT 	CurTask
CurTask
	DCD 	0

	EXPORT 	Counter
Counter
	DCD 	0

	EXPORT  TempStack
TempStack
	DCD 	0x00800000
	EXPORT  task1cb
	EXPORT  task2cb
	EXPORT  task3cb
	EXPORT  taskcb
taskcb 		DCD 	task1cb
task1cb 	DCD 	0x00810000
task2cb 	DCD 	0x00820000
task3cb 	DCD 	0x00830000

	END
