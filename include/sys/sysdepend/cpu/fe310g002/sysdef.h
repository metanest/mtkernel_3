/*
 *	sysdef.h
 *
 *	System dependencies definition (FE310-G002 CPU depended)
 *	Included also from assembler program.
 */

#ifndef __TK_SYSDEF_DEPEND_CPU_H__
#define __TK_SYSDEF_DEPEND_CPU_H__


/* CPU Core-dependent definition */
#include "../core/riscv32/sysdef.h"

/* ------------------------------------------------------------------------ */
/*
 * Internal Memorie (Main RAM)  0x00000000 - 0x00003FFF
 */
#define INTERNAL_RAM_SIZE	0x00004000

#define INTERNAL_RAM_START	0x80000000
#define INTERNAL_RAM_END	(INTERNAL_RAM_START+INTERNAL_RAM_SIZE)

/* ------------------------------------------------------------------------ */
/*
 * Initial Stack pointer (Used in initialization process)
 */
#define	INITIAL_SP		INTERNAL_RAM_END

/* ------------------------------------------------------------------------ */
/*
 * System Timer Clock
 */

/* Settable interval range (millisecond) */
#define MIN_TIMER_PERIOD	1
#define MAX_TIMER_PERIOD	50

/* ------------------------------------------------------------------------ */
/*
 * Platform-Level Interrupt Controller (PLIC)
 */
#define PLIC_BASE		0x0C000000

/*
 * Interrupt Priority Levels
 */
#define INTPRI_HIGHEST		7
#define INTPRI_LOWEST		0


/* ------------------------------------------------------------------------ */
/*
 * Number of Interrupt vectors
 */
#define N_INTVEC	53	/* 1 + Number of Interrupt vectors */
				/* 0 didn't used */


/* ------------------------------------------------------------------------ */
/*
 * machine timer
 */
#define MTIMECMP	0x02004000U
#define MTIMECMP_LO	(MTIMECMP+0U)
#define MTIMECMP_HI	(MTIMECMP+4U)
#define MTIME		0x0200BFF8U
#define MTIME_LO	(MTIME+0U)
#define MTIME_HI	(MTIME+4U)


/* ------------------------------------------------------------------------ */
/*
 * UART
 */
#define UART0BASE	0x10013000
#define UART1BASE	0x10023000

#define UART0_TXDATA	(UART0BASE+0x00)
#define UART0_RXDATA	(UART0BASE+0x04)
#define UART0_TXCTRL	(UART0BASE+0x08)
#define UART0_RXCTRL	(UART0BASE+0x0c)
#define UART0_DIV	(UART0BASE+0x18)

#define TXCTRL_TXEN	(1)
#define TXCTRL_NSTOP	(1<<1)
#define RXCTRL_RXEN	(1)


/* ------------------------------------------------------------------------ */
/*
 * Physical timer (for FE310-G002)
 */
#define CPU_HAS_PTMR    (0)


/* ------------------------------------------------------------------------ */
/*
 * Coprocessor
 */
#define CPU_HAS_FPU		0
#define CPU_HAS_DSP		0

/*
 *  Number of coprocessors to use. Depends on user configuration
 */
#define	NUM_COPROCESSOR		0

#endif /* __TK_SYSDEF_DEPEND_CPU_H__ */
