/*
 *	sysdef.h
 *
 *	System dependencies definition (RISC-V 32 core depended)
 *	Included also from assembler program.
 */

#ifndef __SYS_SYSDEF_DEPEND_CORE_H__
#define __SYS_SYSDEF_DEPEND_CORE_H__

/* ------------------------------------------------------------------------ */
/*
 * (m)status CSR
 */
#define STATUS_MIE	0x00000008UL

#define MIE_MTIE	0x00000080UL
#define MIE_MEIE	0x00000800UL


/* ------------------------------------------------------------------------ */
/*
 * PLIC(Platform-Level Interrupt Controller) register
 */
#define PLIC_PRIORITY(n)	(PLIC_BASE + 4 * (n))
#define PLIC_PENDING		(PLIC_BASE + 0x00001000)
#define PLIC_ENABLE		(PLIC_BASE + 0x00002000)
#define PLIC_THRESHOLD		(PLIC_BASE + 0x00200000)
#define PLIC_CLAIM_COMPLETE	(PLIC_BASE + 0x00200004)


/* ------------------------------------------------------------------------ */
/*
 * Definition of minimum system stack size
 *	Minimum system stack size when setting the system stack size
 *	per task by 'tk_cre_tsk().'
 *  this size must be larger than the size of SStackFrame
 */
#define MIN_SYS_STACK_SIZE	128

/*
 * Default task system stack
 */

#define DEFAULT_SYS_STKSZ	MIN_SYS_STACK_SIZE

/* ------------------------------------------------------------------------ */

#endif /* __SYS_SYSDEF_DEPEND_CORE_H__ */
