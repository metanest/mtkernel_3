#include <sys/machine.h>
#ifdef CPU_CORE_RISCV32

/*
 *	exc_hdr.c (RISC-V 32)
 *	Exception handler
 */

#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include <kernel.h>
#include "../../../sysdepend.h"

#if USE_EXCEPTION_DBG_MSG
	#define EXCEPTION_DBG_MSG(a)	tm_printf((UB*)a)
#else
	#define EXCEPTION_DBG_MSG(a)
#endif

/*
 * Undefined instruction exception handler
 */
WEAK_FUNC EXPORT void Exception_Handler(void)
{
	EXCEPTION_DBG_MSG("Exception\n");
	while(1);
}

/*
 * Default Handler (Undefine Interrupt)
 */
EXPORT void Default_Handler(void)
{
	EXCEPTION_DBG_MSG("Undefine Interrupt\n");
	while(1);
}

#endif	/* CPU_CORE_RISCV32 */
