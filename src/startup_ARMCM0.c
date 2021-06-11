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

//----------------------------------------------------------------------------------
/// @brief Interrupt vector table.
///
/// @details The interrupt vector table contains the initial value of the stack
///          pointer, and the start addresses for all exception handlers. The
///          vector table is placed in a special ELF section which is fixed at
///          address 0x0000.0000 (start of addressable memory).
//
static const tExceptionHandler isrVectorTable[] __attribute__((section(".boot_isr_vector"))) =
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
};

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

    // TODO: initialize system

    // TODO: call bootloader main function

    for(;;) {}
}
