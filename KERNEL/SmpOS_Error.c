/*
*********************************************************************************************************
*                                               SmpOS
*                                        The Real-Time Kernel
*
*                         (c) Copyright 2013-2083, Changzhi Yu
*                                          All Rights Reserved
*
* File         : SmpOS_Error.c
*********************************************************************************************************
*/


#include <SmpOS.h>

STATIC SMPOSERR SmpOS_LastError;

/*
*********************************************************************************************************
*                                   SmpOS_InitLastError
*
* Description: This function is called by SmpOS_Init() to initial the last error of the system.
*
* Arguments  : none.
*
* Returns    : Last system error.
*********************************************************************************************************
*/

SMPOSERR SmpOS_ErrorInit(VOID)
{
	SmpOS_LastError = SMPOS_UNKNOWN;
	return SMPOS_SUCCESS;
}

/*
*********************************************************************************************************
*                                   SmpOS_GetLastError
*
* Description: This function can be called by user or kernel function to get last error of the system.
*
* Arguments  : none.
*
* Returns    : Last system error.
*********************************************************************************************************
*/

SMPOSERR SmpOS_GetLastError(VOID)
{
	return SmpOS_LastError;
}

/*
*********************************************************************************************************
*                                   SmpOS_SetLastError
*
* Description: This function can be called by user or kernel function to get last error of the system.
*
* Arguments  : Last system error.
*
* Returns    : none.
*********************************************************************************************************
*/

VOID SmpOS_SetLastError(SMPOSERR error)
{
	SmpOS_LastError = error;
}

