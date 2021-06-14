#include <stdint.h>
#include <stdlib.h>

//----------------------------------------------------------------------------------
/// @brief Linker-defined symbols.
//
extern void* __etext;
extern void* __data_start__;
extern void* __data_end__;
extern void* __bss_start__;
extern void* __bss_end__;
extern void* __StackTop;

//----------------------------------------------------------------------------------
/// @brief Exception handler type.
//
typedef void (*tExceptionHandler)(void);

//----------------------------------------------------------------------------------
/// @brief Exception handler declarations.
///
/// @details Declarations for the handlers of execptions implemented on the
///          system. Those declarations with \b alias attribute may be overridden,
///          if required. Otherwise they are emitted as aliases for the default
///          exception handler, \b defaultHandler .
//
static void defaultHandler();
static void resetHandler();
extern void nmiHandler()       __attribute__((weak, alias("defaultHandler")));
extern void hardFaultHandler() __attribute__((weak, alias("defaultHandler")));
extern void svCallHandler()    __attribute__((weak, alias("defaultHandler")));
extern void pendSVHandler()    __attribute__((weak, alias("defaultHandler")));
extern void sysTickHandler()   __attribute__((weak, alias("defaultHandler")));
extern void irq0Handler()      __attribute__((weak, alias("defaultHandler")));
extern void irq1Handler()      __attribute__((weak, alias("defaultHandler")));
extern void irq2Handler()      __attribute__((weak, alias("defaultHandler")));
extern void irq3Handler()      __attribute__((weak, alias("defaultHandler")));
extern void irq4Handler()      __attribute__((weak, alias("defaultHandler")));
extern void irq5Handler()      __attribute__((weak, alias("defaultHandler")));
extern void irq6Handler()      __attribute__((weak, alias("defaultHandler")));
extern void irq7Handler()      __attribute__((weak, alias("defaultHandler")));
extern void irq8Handler()      __attribute__((weak, alias("defaultHandler")));
extern void irq9Handler()      __attribute__((weak, alias("defaultHandler")));
extern void irq10Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq11Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq12Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq13Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq14Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq15Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq16Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq17Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq18Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq19Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq20Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq21Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq22Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq23Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq24Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq25Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq26Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq27Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq28Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq29Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq30Handler()     __attribute__((weak, alias("defaultHandler")));
extern void irq31Handler()     __attribute__((weak, alias("defaultHandler")));

extern void systemInit() __attribute__((weak, alias("defaultSystemInit")));

//----------------------------------------------------------------------------------
/// @brief Interrupt vector table.
///
/// @details The interrupt vector table contains the initial value of the stack
///          pointer, and the start addresses for all exception handlers. The
///          vector table is placed in a special ELF section which is fixed at
///          address 0x0000.0000 (start of addressable memory).
//
static const tExceptionHandler isrVectorTable[] __attribute__((section(".boot_isr_vector_table"))) =
{
    (tExceptionHandler)&__StackTop, // Initial Stack Pointer
    resetHandler,                   // Reset Handler
    nmiHandler,                     // NMI Handler
    hardFaultHandler,               // HardFault Handler
    NULL,                           // Reserved
    NULL,                           // Reserved
    NULL,                           // Reserved
    NULL,                           // Reserved
    NULL,                           // Reserved
    NULL,                           // Reserved
    NULL,                           // Reserved
    svCallHandler,                  // SV Call Handler
    NULL,                           // Reserved
    NULL,                           // Reserved
    pendSVHandler,                  // Pend SV Handler
    sysTickHandler,                 // SysTick Handler
    // Interrupts (IRQs)
    irq0Handler,                    // IRQ 0
    irq1Handler,                    // IRQ 1
    irq2Handler,                    // IRQ 2
    irq3Handler,                    // IRQ 3
    irq4Handler,                    // IRQ 4
    irq5Handler,                    // IRQ 5
    irq6Handler,                    // IRQ 6
    irq7Handler,                    // IRQ 7
    irq8Handler,                    // IRQ 8
    irq9Handler,                    // IRQ 9
    irq10Handler,                   // IRQ 10
    irq11Handler,                   // IRQ 11
    irq12Handler,                   // IRQ 12
    irq13Handler,                   // IRQ 13
    irq14Handler,                   // IRQ 14
    irq15Handler,                   // IRQ 15
    irq16Handler,                   // IRQ 16
    irq17Handler,                   // IRQ 17
    irq18Handler,                   // IRQ 18
    irq19Handler,                   // IRQ 19
    irq20Handler,                   // IRQ 20
    irq21Handler,                   // IRQ 21
    irq22Handler,                   // IRQ 22
    irq23Handler,                   // IRQ 23
    irq24Handler,                   // IRQ 24
    irq25Handler,                   // IRQ 25
    irq26Handler,                   // IRQ 26
    irq27Handler,                   // IRQ 27
    irq28Handler,                   // IRQ 28
    irq29Handler,                   // IRQ 29
    irq30Handler,                   // IRQ 30
    irq31Handler                    // IRQ 31
};

//----------------------------------------------------------------------------------
/// @brief Default system initialization routine.
//
static void defaultSystemInit()
{

}

//----------------------------------------------------------------------------------
/// @brief Default exception handler.
///
/// @details This routine is the default exception handler invoked where no
///          meaningful exception handling is required, or possible. Its main
///          purpose is to serve as an alias target for excelption handlers
///          declared using \b __attribute__((alias("target"))).
//
static void defaultHandler() 
{
    // Loop forever to allow the debugger to inspect the state of the core.
    for(;;) {}
}

//----------------------------------------------------------------------------------
/// @brief Reset handler.
///
/// @details This routine is the entry point of the program. On reset, the
///          Program Counter (PC) is loaded with the value of the reset
///          vector, which is loaded at address 0x0000.0004.
//
static void resetHandler()
{
    uint8_t* src;
    uint8_t* dst;
    uint8_t* data_lma_start = (uint8_t*)&__etext;
    uint8_t* data_lma_end   = ((uint8_t*)&__etext) + (&__data_end__ - &__data_start__);

    // Copy the data section initializers from the .data LMA to the .data VMA.
    for (src = data_lma_start, dst = (uint8_t*)&__data_start__; src < data_lma_end; src++, dst++)
    {
        *dst = *src;
    }

    // Zero out .bss.
    for (dst = (uint8_t*)&__bss_start__; dst < (uint8_t*)&__bss_end__; dst++)
    {
        *dst = 0x00;
    }

    // Initialize board.
    systemInit();

    // TODO: call bootloader main function

    for(;;) {}
}
