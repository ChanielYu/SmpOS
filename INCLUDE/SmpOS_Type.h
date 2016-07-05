/*
*********************************************************************************************************
*                                               SmpOS
*                                        The Real-Time Kernel
*
*                         (c) Copyright 2013-2083, Changzhi Yu
*                                          All Rights Reserved
*
* File         : SmpOS_Type.h
*********************************************************************************************************
*/

#if !defined __SMPOS_TYPE_H__
#define __SMPOS_TYPE_H__

#ifdef UCOSII_COMPATIBLE

typedef unsigned char  BOOLEAN;                 /* 布尔变量                                 */
typedef unsigned char  INT8U;                   /* 无符号8位整型变量                        */
typedef signed   char  INT8S;                   /* 有符号8位整型变量                        */
typedef unsigned short INT16U;                  /* 无符号16位整型变量                       */
typedef signed   short INT16S;                  /* 有符号16位整型变量                       */
typedef unsigned int   INT32U;                  /* 无符号32位整型变量                       */
typedef signed   int   INT32S;                  /* 有符号32位整型变量                       */

#else /* UCOSII_COMPATIBLE */

typedef enum
{
	FALSE = 0,
	TRUE
} BOOL; 									/* 布尔变量                                 */
typedef unsigned char 	BYTE,*PBYTE; 		/* 无符号8位整型变量                        */
typedef char 			CHAR,*PCHAR; 		/* 无符号字符变量                           */

typedef unsigned char 	UINT8,*PUINT8; 		/* 无符号8位整型变量                        */
typedef signed char 	INT8,*PINT8; 		/* 有符号8位整型变量                        */
typedef unsigned short 	UINT16,*PUINT16; 	/* 无符号16位整型变量                       */
typedef signed short 	INT16,*PINT16; 		/* 有符号16位整型变量                       */
typedef unsigned int 	UINT32,*PUINT32; 	/* 无符号32位整型变量                       */
typedef signed int 		INT32,*PINT32; 		/* 有符号32位整型变量                       */

#endif /* UCOSII_COMPATIBLE */

typedef float 			FP32; 		/* 单精度浮点数（32位长度）                 */
typedef double 			FP64; 		/* 双精度浮点数（64位长度）                 */

typedef void 			VOID;
#define STATIC 			static
#define SMPOSEXT 		extern

typedef void (*THREADPROC)(VOID*);

typedef VOID* SMPOSHANDLE;

#define NULL 0

#if (defined ARCH_ARM) || defined (__TARGET_ARCH_5TE)

typedef UINT32 			SMPOS_STK; 	/* 堆栈是32位宽度                           */
typedef UINT32 			SMPOS_CPU_SR;

#else /* ARCH_ARM */
#error Configure an ARCH!
#endif /* ARCH_ARM */

#endif /* __SMPOS_TYPE_H__ */

