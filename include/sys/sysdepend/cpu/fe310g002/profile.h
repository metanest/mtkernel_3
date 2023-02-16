/*
 *	profile.h
 *
 *	Service Profile (FE310-G002 depended)
 */

#ifndef __SYS_DEPEND_PROFILE_CPU_H__
#define __SYS_DEPEND_PROFILE_CPU_H__

/*
 **** CPU core-depeneded profile (RISC-V 32)
 */
#include "../core/riscv32/profile.h"

/*
 **** CPU-depeneded profile (FE310-G002)
 */

/*
 * Device Support
 */
#define TK_SUPPORT_IOPORT	TRUE		/* Support of I/O port access */

/*
 * Physical timer
 */
#define TK_SUPPORT_PTIMER	FALSE		/* Support of physical timer */
#define TK_MAX_PTIMER		0		/* Maximum number of physical timers. */


#endif /* __SYS_DEPEND_PROFILE_CPU_H__ */
