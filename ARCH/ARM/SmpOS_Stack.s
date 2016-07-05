;********************************************************************************************************
;*                                               SmpOS
;*                                        The Real-Time Kernel
;*
;*                         (c) Copyright 2013-2083, Changzhi Yu
;*                                          All Rights Reserved
;*
;* File         : SmpOS_Stack.s
;********************************************************************************************************
;;; Copyright ARM Ltd 2001. All rights reserved.

        AREA    Stacks, DATA, NOINIT

        EXPORT top_of_stacks

; Create dummy variable used to locate stacks in memory

top_of_stacks    SPACE   1

        END
