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
#if 0
/*
 * Undefined instruction exception handler
 */
WEAK_FUNC EXPORT void UndefinedInst_Handler(void)
{
	EXCEPTION_DBG_MSG("Undef\n");
	while(1);
}

/*
 * Prefetch abort exception handler
 */
WEAK_FUNC EXPORT void PrefetchAbort_Handler(void)
{
	EXCEPTION_DBG_MSG("iabort\n");
	while(1);
}

/*
 * Data abort exception handler
 */
WEAK_FUNC EXPORT void DataAbort_Handler(void)
{
	EXCEPTION_DBG_MSG("dabort\n");
	while(1);
}

/*
 * VFP invalid handler
 */
WEAK_FUNC EXPORT void VFPInvalid_Handler(void)
{
	EXCEPTION_DBG_MSG("VFP invalid\n");
	while(1);
}
#endif
/*
 * Default Handler (Undefine Interrupt)
 */
EXPORT void Default_Handler(void)
{
	EXCEPTION_DBG_MSG("Undefine Interrupt\n");
	while(1);
}
#if 0
/*
 * SVC default Handler (Undefine SVC)
 */
WEAK_FUNC EXPORT void SVC_default_Handler(void)
{
	EXCEPTION_DBG_MSG("Undefine SVC\n");
	while(1);
}
#endif
#endif	/* CPU_CORE_RISCV32 */
