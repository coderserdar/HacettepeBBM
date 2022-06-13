SECTIONS
{
    . = 0x4000;

    .text :
    {
        *(.text)
    }

    .rdata ALIGN (0x1000) :
    {
        *(.rdata)
    }

    .rodata ALIGN (0x1000) :
    {
        *(.rodata)
    }

    .data ALIGN (0x1000) :
    {
        *(.data)
    }

    .bss :
    {
        *(COMMON)
        *(.bss)
    }

}
