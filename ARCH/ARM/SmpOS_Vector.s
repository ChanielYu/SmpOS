;********************************************************************************************************
;*                                               SmpOS
;*                                        The Real-Time Kernel
;*
;*                         (c) Copyright 2013-2083, Changzhi Yu
;*                                          All Rights Reserved
;*
;* File         : SmpOS_Vector.s
;********************************************************************************************************

	; IMPORT vectors
	IMPORT VextRst
	IMPORT VectUnd
	IMPORT VectSvc
	IMPORT VectPre
	IMPORT VectAbt
	IMPORT ImgLen
	IMPORT VectIrq

	GLOBAL INT_Vectors
 	
 	AREA VECT, CODE, READONLY

	ENTRY
INT_Vectors
	LDR 	PC,[PC,#0x00000018]
	LDR 	PC,[PC,#0x00000018]
	LDR 	PC,[PC,#0x00000018]
	LDR 	PC,[PC,#0x00000018]
	LDR 	PC,[PC,#0x00000018]
	DCD 	ImgLen
	LDR 	PC,[PC,#0x00000018]
	LDR 	PC,[PC,#0x00000018]

INT_Table
	DCD 	VextRst
	DCD 	VectUnd
	DCD 	VectSvc
	DCD 	VectPre
	DCD 	VectAbt
	DCD 	ImgLen
	DCD 	VectIrq
	DCD 	VectFiq

VectFiq
	STMFD 	SP!,{R0-R12,LR}
	LDMFD 	SP!,{R0-R12,LR}
	SUBS 	PC,LR,#4

	END

