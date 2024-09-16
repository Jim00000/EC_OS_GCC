/* Linker script to configure memory regions. */
MEMORY
{
  TEXT    (rx)  : ORIGIN = 0x20000100, LENGTH = 0x3FF00
  DATA    (rw)  : ORIGIN = 0x20040000, LENGTH = 0x1E000
  STACK   (rw)  : ORIGIN = 0x2005E000, LENGTH = 0x01FF0
}

REGION_ALIAS("SRAM_TEXT", TEXT);
REGION_ALIAS("SRAM_ARM", TEXT);
REGION_ALIAS("SRAM_DATA", DATA);
REGION_ALIAS("SRAM_BSS", DATA);
REGION_ALIAS("SRAM_HEAP", STACK);

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
        /* All data end */
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
            
    .heap (NOLOAD) : 
    {
        __heap_start__ = .;
        end = __heap_start__;
        _end = end;
        __end = end;
        KEEP(*(.heap))
        __heap_end__ = .;
        __HeapLimit = __heap_end__;
    } > SRAM_HEAP

    . = ALIGN(4);
    __StackLimit = .;
    __StackTop = ORIGIN(STACK) + LENGTH(STACK);
    PROVIDE(__stack = __StackTop);

    /DISCARD/ :
    {
        *(.ARM.attributes .glue_7* .vfp11_veneer .v4_bx .igot.plt .iplt .rel.*)
    }

    HIDDEN(__text_length__ = __etext - ORIGIN(TEXT));
    HIDDEN(__data_length__ = __data_end__ - __data_start__);
    HIDDEN(__bss_length__ = __bss_end__ - __bss_start__);
    HIDDEN(__bin_size__ = __text_length__ + __data_length__ + __bss_length__);

    ASSERT(__data_start__ >= __etext,   "region TEXT overlaped with DATA")
    ASSERT(__heap_end__ < __StackTop,  "region HEAP overlaped with STACK")
    ASSERT(__heap_start__ >= __bss_end__, "region DATA overlaped with STACK")
    ASSERT(__bin_size__ < (ORIGIN(DATA) - ORIGIN(TEXT)), "binary file is oversized because the whole image overlaps data segment")
}