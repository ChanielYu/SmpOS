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

typedef unsigned char  BOOLEAN;                 /* ��������                                 */
typedef unsigned char  INT8U;                   /* �޷���8λ���ͱ���                        */
typedef signed   char  INT8S;                   /* �з���8λ���ͱ���                        */
typedef unsigned short INT16U;                  /* �޷���16λ���ͱ���                       */
typedef signed   short INT16S;                  /* �з���16λ���ͱ���                       */
typedef unsigned int   INT32U;                  /* �޷���32λ���ͱ���                       */
typedef signed   int   INT32S;                  /* �з���32λ���ͱ���                       */

#else /* UCOSII_COMPATIBLE */

typedef enum
{
	FALSE = 0,
	TRUE
} BOOL; 									/* ��������                                 */
typedef unsigned char 	BYTE,*PBYTE; 		/* �޷���8λ���ͱ���                        */
typedef char 			CHAR,*PCHAR; 		/* �޷����ַ�����                           */

typedef unsigned char 	UINT8,*PUINT8; 		/* �޷���8λ���ͱ���                        */
typedef signed char 	INT8,*PINT8; 		/* �з���8λ���ͱ���                        */
typedef unsigned short 	UINT16,*PUINT16; 	/* �޷���16λ���ͱ���                       */
typedef signed short 	INT16,*PINT16; 		/* �з���16λ���ͱ���                       */
typedef unsigned int 	UINT32,*PUINT32; 	/* �޷���32λ���ͱ���                       */
typedef signed int 		INT32,*PINT32; 		/* �з���32λ���ͱ���                       */

#endif /* UCOSII_COMPATIBLE */

typedef float 			FP32; 		/* �����ȸ�������32λ���ȣ�                 */
typedef double 			FP64; 		/* ˫���ȸ�������64λ���ȣ�                 */

typedef void 			VOID;
#define STATIC 			static
#define SMPOSEXT 		extern

typedef void (*THREADPROC)(VOID*);

typedef VOID* SMPOSHANDLE;

#define NULL 0

#if (defined ARCH_ARM) || defined (__TARGET_ARCH_5TE)

typedef UINT32 			SMPOS_STK; 	/* ��ջ��32λ���                           */
typedef UINT32 			SMPOS_CPU_SR;

#else /* ARCH_ARM */
#error Configure an ARCH!
#endif /* ARCH_ARM */

#endif /* __SMPOS_TYPE_H__ */

