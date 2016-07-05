/*
*********************************************************************************************************
*                                               SmpOS
*                                        The Real-Time Kernel
*
*                         (c) Copyright 2013-2083, Changzhi Yu
*                                          All Rights Reserved
*
* File         : SmpOS_Error.h
*********************************************************************************************************
*/

#if !defined __SMPOS_ERROR_H__
#define __SMPOS_ERROR_H__

typedef enum smperror
{
	SMPOS_SUCCESS = 0,
	SMPOS_ERROR,
	/* Error of Kernel module */
	/* Error of Croe module */
	SMPOS_CORE_NOOSTCBLIST,
	/* Error of maximum */
	SMPOS_CORE_NONEEDTOSWITCH,
	SMPOS_UNKNOWN
} SMPOSERR;

SMPOSERR SmpOS_ErrorInit(VOID);
SMPOSERR SmpOS_GetLastError(VOID);
VOID SmpOS_SetLastError(SMPOSERR error);

#endif /* __SMPOS_ERROR_H__ */

