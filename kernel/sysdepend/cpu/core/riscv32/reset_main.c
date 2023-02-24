#include <sys/machine.h>
#ifdef CPU_CORE_RISCV32

/*
 *	reset_main.c (RISC-V 32)
 *	jumped from start
 */

#include "kernel.h"
#include "../../../sysdepend.h"

#include <tm/tmonitor.h>

#if USE_IMALLOC
/* Low level memory manager information */
EXPORT	void	*knl_lowmem_top;		// Head of area (Low address)
EXPORT	void	*knl_lowmem_limit;		// End of area (High address)
#endif

IMPORT	const void *__data_org;
IMPORT	const void *__data_start;
IMPORT	const void *__data_end;
IMPORT	const void *__bss_start;
IMPORT	const void *__bss_end;

IMPORT const void (*vector_tbl[])();

EXPORT void reset_main(void)
{
	UW	*src, *top, *end;
	INT	i;

	/* Startup Hardware */
	knl_startup_hw();

	/* Load .data to ram */
	src = (UW*)&__data_org;
	top = (UW*)&__data_start;
	end = (UW*)&__data_end;
	while(top != end) {
		*top++ = *src++;
	}

	/* Initialize .bss */
	top = (UW*)&__bss_start;
	for(i = ((INT)&__bss_end - (INT)top)/sizeof(UW); i > 0 ; i--) {
		*top++ = 0;
	}

#if USE_IMALLOC
	/* Set System memory area */
	if (INTERNAL_RAM_START > SYSTEMAREA_TOP) {
		knl_lowmem_top = (UW*)INTERNAL_RAM_START;
	} else {
		knl_lowmem_top = (UW*)SYSTEMAREA_TOP;
	}
	if ((UW)knl_lowmem_top < (UW)&__bss_end) {
		knl_lowmem_top = (UW*)&__bss_end;
	}

	if ((SYSTEMAREA_END != 0) && (INTERNAL_RAM_END > CNF_SYSTEMAREA_END)) {
		knl_lowmem_limit = (UW*)(SYSTEMAREA_END - EXC_STACK_SIZE);
	} else {
		knl_lowmem_limit = (UW*)(INTERNAL_RAM_END - EXC_STACK_SIZE);
	}
#endif

#if USE_FPU
	/* Enable FPU */
	//TODO(FPU)
#endif /* USE_FPU */

	/* Startup Kernel */
	main();		/**** No return ****/
	while(1);	/* guard - infinite loops */
}

#endif	/* CPU_CORE_RISCV32 */
