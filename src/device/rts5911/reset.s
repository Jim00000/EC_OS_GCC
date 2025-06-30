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
                .global Reset_Handler
                .thumb
                .thumb_func
                .type   Reset_Handler, %function
Reset_Handler:
                /* Disable interrupts */
                cpsid i

                /* Setup stack & stack limit */
                ldr     sp, =__StackTop
                ldr     r0, =__StackLimit
                msr     msplim, r0

                /* crt0 initialization */
                bl      crt0_init

                /* Initialize ARM system */
                bl      arm_system_init

                /* Enable interrupts */
                cpsie i

                /* Jump to main function */
                bl      main

                /* context switch to first task */
                svc     0
                .size   Reset_Handler, . - Reset_Handler
