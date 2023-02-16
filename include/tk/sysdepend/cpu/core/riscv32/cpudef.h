/*
 *	cpudef.h
 *
 *	CPU dependent definition  (RISC-V 32 core depended)
 */

#ifndef __TK_CPUDEF_CORE_H__
#define __TK_CPUDEF_CORE_H__

#include <config.h>

/*
 * Using FPU (depend on CPU)
 *   TA_COP0		FPU ( = TA_FPU)
 */

#if USE_FPU
#define TA_COPS		TA_COP0
#else
#define TA_COPS		0
#endif

#define TA_FPU		TA_COP0		/* dummy. An error occurs when checking API calls. */

/*
 * General purpose register		tk_get_reg tk_set_reg
 */
typedef struct t_regs {
				/* General purpose register */
	VW	a[8];   // a0-a7
	VW	s[12];  // s0-s11
	VW	t[7];   // t0-t6
	void    *ra;		/* Link register */
} T_REGS;

/*
 * Exception-related register		tk_get_reg tk_set_reg
 */
typedef struct t_eit {
	UW	status;		/* status */
} T_EIT;

/*
 * Control register			tk_get_reg tk_set_reg
 */
typedef struct t_cregs {
	void	*ssp;		/* System stack pointer */
} T_CREGS;

#endif /* __TK_CPUDEF_CORE_H__ */
