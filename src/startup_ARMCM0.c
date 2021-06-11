#include <stdint.h>
#include <stdlib.h>

/// @brief Linker-defined symbols.
extern void* __StackTop;
extern void* __data_start__;
extern void* __data_end__;
extern void* __bss_start__;
extern void* __bss_end__;

/// @brief Define the exception handler type.
typedef void (*tExceptionHandler)(void);

/// @brief Default exception handler.
static void defaultHandler() 
{
    // Loop forever to allow the debugger to inspect the state of the core.
    for(;;) {}
}

/// @brief Reset handler.
static void resetHandler()
{
    // TODO: implement startup code.
    for(;;)
    {

    }
}

void nmiHandler()       __attribute__((weak, alias("defaultHandler")));
void hardFaultHandler() __attribute__((weak, alias("defaultHandler")));
void svCallHandler()    __attribute__((weak, alias("defaultHandler")));
void pendSVHandler()    __attribute__((weak, alias("defaultHandler")));
void sysTickHandler()   __attribute__((weak, alias("defaultHandler")));

/// @brief Interrupt vector table.
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