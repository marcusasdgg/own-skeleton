ENTRY(_start)

SECTIONS {
    . = 1M;

    /* Our entry point which is 32 bit  */
    .boot.text BLOCK(4K) : ALIGN(4K)
    {
        KEEP(*(.multiboot2))
        *(.boot.text*)
    }


	/* Read-only data. */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
        *(.paging) /* a section assigned for the initial paging setup. */
	}

}