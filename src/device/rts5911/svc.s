                .syntax unified
                .arch   armv8-m.main
                .cpu    real-m300
                .fpu    fpv5-sp-d16
                .text
                .align  1
                .thumb

                .equ    TCB_SP_OFFSET,  0
                .equ    TCB_FRAME_OFFSET,  4

                .thumb_func
                .global  SVCall_Handler
                .type    SVCall_Handler, %function
SVCall_Handler:
                tst     lr, 4
                ite     eq
                mrseq   r0, msp
                mrsne   r0, psp

                ldr     r3, =g_running_info
                ldm     r3, {r1, r2} // r1: curr, r2: next

                cmp     r1, r2
                it      eq
                bxeq    lr
                str     r2, [r3]     // curr <- next

                cbz     r1, SVC_ContextRestore // check curr thread null ?

SVC_ContextSave:
                stmdb  r0!,  {r4-r11}
                str    r0,   [r1, #TCB_SP_OFFSET]
                strb   lr,   [r1, #TCB_FRAME_OFFSET]

SVC_ContextRestore:
                ldr     r0,  [r2, #TCB_SP_OFFSET]
                ldrsb   lr,  [r2, #TCB_FRAME_OFFSET]
                ldmia   r0!, {r4-r11}
                msr     psp, r0
                bx      lr
                .size    SVCall_Handler, . - SVCall_Handler
