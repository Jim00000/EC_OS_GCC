MEMORY
{
  TEXT_DATA (rwx) : ORIGIN = 0x20000100, LENGTH = 0x5FC00
  STACK   (rw)  : ORIGIN = 0x2005FD00,  LENGTH = 0x002F0
}

REGION_ALIAS("SRAM_TEXT", TEXT_DATA);
REGION_ALIAS("SRAM_DATA", TEXT_DATA);
REGION_ALIAS("SRAM_BSS", TEXT_DATA);

ENTRY(Reset_Handler)

SECTIONS
{   
    .text :
    {
        KEEP(*(.vectors))
        . = ALIGN(4);
        *(.text*)
    } > SRAM_TEXT

    . = ALIGN (4);
    __etext = ABSOLUTE(.);
    
    .data : AT (__etext)
    {
        . = ALIGN(4);
        __data_start__ = .;        
        *(.data*)
        
        . = ALIGN(4);
        *(.rodata*)

        . = ALIGN(4);
        KEEP(*(.version*))

        . = ALIGN(4);
        __data_end__ = .;
    } > SRAM_DATA

    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        . = ALIGN(4);
        __bss_end__ = .;
    } > SRAM_BSS

    /* Heap (including inside DATA section) */
    . = ALIGN(256);
    __heap_start__ = .;
    end = __heap_start__;
    PROVIDE(__HeapLimit = ORIGIN(STACK) - 8);

    __StackLimit = ORIGIN(STACK);
    __StackTop = ORIGIN(STACK) + LENGTH(STACK);

    /DISCARD/ :
    {
        *(.ARM.attributes .glue_7* .vfp11_veneer .v4_bx .igot.plt .iplt .rel.*)
    }

    HIDDEN(__text_length__ = __etext - ORIGIN(TEXT_DATA));
    HIDDEN(__data_length__ = __data_end__ - __data_start__);
    HIDDEN(__bss_length__ = __bss_end__ - __bss_start__);
    HIDDEN(__bin_size__ = __text_length__ + __data_length__ + __bss_length__);
}