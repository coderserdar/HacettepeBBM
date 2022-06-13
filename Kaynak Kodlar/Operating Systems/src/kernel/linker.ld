ENTRY (KernelStart)

SECTIONS
{
    . = 0x00100000;
    __image_begin = .;

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

    __image_end = .;
}
