/*
 * Define size and location of memory blocks of memory in the target.
 */
MEMORY
{
    BOOT_FLASH (RX)  : ORIGIN = 0x00000000, LENGTH = 0x4000 /* 16K */
    BOOT_RAM   (RWX) : ORIGIN = 0x20000000, LENGTH = 0x8000 /* 32K */
}

/*
 * Heap size in bytes.
 */
__HEAP_SIZE__ = 0x2000; /* 8K */

/*
 * Describe how input sections are mapped into output sections.
 */
SECTIONS
{
    .boot.text : {
        KEEP(*(.boot_isr_vector))
        *(.text*)
        *(.rodata*)
    } > BOOT_FLASH

    __etext = ALIGN(4);

    .boot.data : AT(__etext) {
        __data_start__ = .;
        *(.data*)
        __data_end__ = .;
    } > BOOT_RAM

    .boot.bss : {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        __bss_end__ = .;
    } > BOOT_RAM

    .boot.heap : {
        . = ALIGN(4);
        __end__ = .;
        PROVIDE(end = .);
        . = . + __HEAP_SIZE__;
        __HeapLimit = .;
    } > BOOT_RAM

    .boot.stack : {
        . = ALIGN(4);
        __StackLimit = .;
        . = ORIGIN(BOOT_RAM) + LENGTH(BOOT_RAM);
        __StackTop = .;
        PROVIDE(__stack = __StackTop);
    } > BOOT_RAM
}