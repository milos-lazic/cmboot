#include <stdint.h>
#include <stdlib.h>
#include "arch_ARMCM0.h"

//-----------------------------------------------------------------------------
/// @brief Linker-defined symbols.
//
extern void* __StackTop;
extern void* __etext;
extern void* __data_start__;
extern void* __data_end__;
extern void* __bss_start__;
extern void* __bss_end__;
extern void* __boot_isr_vector_table_start;

//-----------------------------------------------------------------------------
/// @brief Local function declarations.
//
static void reset_handler(void) __attribute__((interrupt("IRQ")));
static void irq_forward_handler(void) __attribute__((interrupt("IRQ")));

//-----------------------------------------------------------------------------
/// @brief Virtual vector table offset register.
//
static void (**g_vtor)(void) __attribute__((section(".pseudo_vtor")));

//-----------------------------------------------------------------------------
/// @brief Main interrupt service routine vector table.
//
static void (*g_isr_vector_table[])(void) __attribute__((section(".isr_vector_table"))) =
{
    // 0
    (void(*)(void))&__StackTop,
    reset_handler,
    irq_forward_handler,
    irq_forward_handler,
    NULL,
    // 5
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    // 10
    NULL,
    irq_forward_handler,
    NULL,
    NULL,
    irq_forward_handler,
    // 15
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler,
    // 20
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler,
    // 25
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler,
    // 30
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler,
    // 35
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler,
    // 40
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler,
    // 45
    irq_forward_handler,
    irq_forward_handler,
    irq_forward_handler
};

//-----------------------------------------------------------------------------
/// @brief Reset handler.
//
static void reset_handler(void)
{
    const char* p_src;
    char*       p_dst;

    arch_disableInterrupts();

    // Copy .data LMA initializers to .data VMA
    for (p_src = (const char*)&__etext, p_dst = (char*)&__data_start__;
         p_dst < (char*)&__data_end__;
         p_src++, p_dst++)
    {
        *p_dst = *p_src;
    }

    // Zero out .bss
    for (p_dst = (char*)&__bss_start__;
         p_dst < (char*)&__bss_end__;
         p_dst++)
    {
        *p_dst = 0x00;
    }

    // Initialize the virtual VTOR so that it points to the start of the
    // bootloader's ISR vector table.
    g_vtor = (void(**)(void))&__boot_isr_vector_table_start;

    arch_enableInterrupts();

    // TODO: Jump to the bootloader

    // TODO: for now..
    for (;;) {}
}

//-----------------------------------------------------------------------------
/// @brief Generic IRQ handler used to forward interrupt requests to the
///        vector table currently being pointed to by the virtual VTOR.
//
static void irq_forward_handler(void)
{
    // Forward the interrupt request to the active vector table.
    g_vtor[arch_getIPSR()]();
}
