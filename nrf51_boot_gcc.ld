INCLUDE ../../nrf51_mem_layout_gcc.ld

__HEAP_SIZE__ = 0x2000; /* 8K */

SECTIONS
{
    .boot_text : {
        KEEP(*(.isr_vector_table))
        . = ALIGN(4);
        __boot_isr_vector_table_start = .;
        KEEP(*(.boot_isr_vector_table))
        *(.text*)
        *(.rodata*)
    } > BOOT_ROM

    __etext = ALIGN(4);

    .pseudo_vtor : {
        KEEP(*(.pseudo_vtor))
    } > RSVD_RAM

    .boot_data : AT(__etext) {
        . = ALIGN(4);
        __data_start__ = .;
        *(.data*)
        __data_end__ = .;
    } > RAM

    .boot_bss : {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        __bss_end__ = .;
    } > RAM

    .boot_heap : {
        . = ALIGN(4);
        __end__ = .;
        PROVIDE(end = .);
        . = . + __HEAP_SIZE__;
        __HeapLimit = .;
    } > RAM

    .boot_stack : {
        . = ALIGN(4);
        __StackLimit = .;
        . = ORIGIN(RAM) + LENGTH(RAM);
        __StackTop = .;
        PROVIDE(__stack = __StackTop);
    } > RAM
}