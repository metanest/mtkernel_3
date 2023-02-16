/*
 *	machine.h
 *
 *	Machine type definition (SiFive HiFive1 Rev B depended)
 */

#ifndef __SYS_SYSDEPEND_MACHINE_H__
#define __SYS_SYSDEPEND_MACHINE_H__

/*
 * [TYPE]_[CPU]		TARGET SYSTEM
 * CPU_xxxx		CPU type
 * CPU_CORE_xxx		CPU core type
 */

/* ----- SiFive HiFive1 Rev B depended (CPU: FE310-G002) definition ----- */

#define SIFIVE_HIFIVE_REVB	1				/* Target system : SiFive HiFive1 Rev B */
#define CPU_FE310G002		1				/* Target CPU : FE310-G002 */
#define CPU_CORE_RISCV32	1				/* Target CPU-Core : RISC-V 32 */

#define TARGET_DIR		sifive_hifive1_revb		/* Sysdepend-Directory name */

/*
 **** CPU-depeneded profile (FE310-G002)
 */
#include "../cpu/fe310g002/machine.h"


#endif /* __SYS_SYSDEPEND_MACHINE_H__ */
