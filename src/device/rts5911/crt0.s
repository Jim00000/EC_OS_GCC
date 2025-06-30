// --------------------------------------------------------------------
// @file         reset.s
// @brief        Reset Handler definition for Realtek RTS5911 Device
// @copyright    Copyright (c) 2024
// --------------------------------------------------------------------
                .syntax unified
                .arch   armv8-m.main
                .cpu    real-m300
                .fpu    fpv5-sp-d16

                .text
                .align  1
                .global crt0_init
                .thumb
                .thumb_func
                .type   crt0_init, %function
crt0_init:
                /* initialize data section */
                ldr     r0, =__etext
                ldr     r1, =__data_start__
                ldr     r2, =__data_end__
                subs    r2, r1

.crt0_copy_data:
                subs    r2, #4
                ldr     r3, [r0, r2]
                str     r3, [r1, r2]
                bgt     .crt0_copy_data

                /* initialize bss section */
                ldr     r0, =__bss_start__
                ldr     r1, =__bss_end__
                eor     r2, r2
                subs    r1, r0

.crt0_clear_bss:
                subs    r1, #4
                str     r2, [r0, r1]
                bgt     .crt0_clear_bss

                bx      lr
                .size   crt0_init, . - crt0_init
