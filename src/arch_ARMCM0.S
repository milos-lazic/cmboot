    .syntax unified
    .arch   armv6-m

@--------------------------------------
    .section .text
    .thumb
    .global  arch_enableInterrupts

arch_enableInterrupts:
    cpsie i
    bx    lr

@--------------------------------------
    .section .text
    .thumb
    .global  arch_disableInterrupts

arch_disableInterrupts:
    cpsid i
    bx    lr

@--------------------------------------
    .section .text
    .thumb
    .global  arch_getIPSR

arch_getIPSR:
    mrs r0, ipsr
    bx  lr
