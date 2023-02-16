/*
 *      tkernel_map.ld
 *	micro T-Kernel linker script for SiFive HiFive1 Rev B
 */

ENTRY(start)

/* Memories definition */
MEMORY
{
  ROM (rx)		: ORIGIN = 0x20010000, LENGTH = 0x6a120
  RAM (rwx)		: ORIGIN = 0x80000000, LENGTH = 16K
}

SECTIONS {
	.text : {
		*(.start)
		*(.vector)
		*(.text)
		*(.text.*)
		*(.rodata)
		*(.rodata.*)
	} >ROM
	. = ALIGN(4);
	.data : {
		__data_org = LOADADDR(.data);
		__data_start = .;
		*(.data)
		*(.data.*)
		. = ALIGN(4);
	} >RAM AT>ROM
	.sdata : {
		__global_pointer$ = . + 0x800;
		*(.sdata)
		*(.sdata.*)
		. = ALIGN(4);
		__data_end = .;
	} >RAM AT>ROM
	.sbss (NOLOAD) : {
		__bss_start = .;
		*(.sbss)
		*(.sbss.*)
	} >RAM
	.bss (NOLOAD) : {
		__noinit_start = .;
		*(.noinit)
		__noinit_end = .;
		*(.bss)
		*(.bss.*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end = .;
		__end = .;
	} >RAM
}
