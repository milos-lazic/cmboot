    .syntax unified
    .arch   armv6-m

@--------------------------------------
    .text
    .thumb
    .global  arch_enableExceptions

arch_enableExceptions:
    cpsie i
    bx    lr

@--------------------------------------
    .text
    .thumb
    .global  arch_disableExceptions

arch_disableExceptions:
    cpsid i
    bx    lr