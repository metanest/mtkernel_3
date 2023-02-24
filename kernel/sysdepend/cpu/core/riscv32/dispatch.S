#include <sys/machine.h>
#ifdef CPU_CORE_RISCV32
/*
 *	dispatch.S (RISC-V 32)
 *	Dispatcher
 */

#define	_in_asm_source_
#include "offset.h"

	.equ	STATUS_MIE, 0x8

/* ------------------------------------------------------------------------ */
/*
 * Dispatcher
 *	knl_dispatch_entry:
 *		Normal dispatch processing.
 *	knl_dispatch_to_schedtsk:
 *		force dispatch processing.
 *
 *	Contexts to save
 *	Save registers except for sp to a stack. Save 'sp' to TCB.
 *
 *       Low Address +---------------+
 *             sp -> | R4            |
 *                   | R5            |
 *                   | R6            |
 *                   | R7            |
 *                   | R8            |
 *                   | R9            |
 *                   | R10           |
 *                   | R11           |
 *                   +---------------+
 *                   | R0            |
 *                   | R1            |
 *                   | R2            |
 *                   | R3            |
 *                   | R12(ip)       |
 *                   | R14_svc(lr)   |
 *                   | R14_xxx(lr)   | Return address (pc)
 *                   | SPSR_xxx      |
 *      High Address +---------------+
 */

/* ----------------------------------------
 *     force dispatch
 * ---------------------------------------- */
	.text
	.balign 4
	.globl	Csym(knl_dispatch_to_schedtsk)
	.type	Csym(knl_dispatch_to_schedtsk), %function
Csym(knl_dispatch_to_schedtsk):
	li	a1, 1
	lui	a0, %hi(Csym(knl_dispatch_disabled))
	sw	a1, %lo(Csym(knl_dispatch_disabled))(a0)	// Dispatch disable

	lui	s4, %hi(Csym(knl_ctxtsk))
	addi	s4, s4, %lo(Csym(knl_ctxtsk))		// S4: &ctxtsk

	lw	s7, (s4)				// S7: ctxtsk
	sw	zero, (s4)				// ctxtsk = NULL

	j	l_dispatch0
/* ----------------------------------------
 *     normal dispatch
 * ---------------------------------------- */
	.text
	.balign 4
	.globl	Csym(knl_dispatch_entry)
	.type	Csym(knl_dispatch_entry), %function
Csym(knl_dispatch_entry):
	// Context save
	addi    sp, sp, -4*12
	sw	s0, 0*4(sp)
	sw	s1, 1*4(sp)
	sw	s2, 2*4(sp)
	sw	s3, 3*4(sp)
	sw	s4, 4*4(sp)
	sw	s5, 5*4(sp)
	sw	s6, 6*4(sp)
	sw	s7, 7*4(sp)
	sw	s8, 8*4(sp)
	sw	s9, 9*4(sp)
	sw	s10, 10*4(sp)
	sw	s11, 11*4(sp)

	li	a1, 1
	lui	a0, %hi(Csym(knl_dispatch_disabled))
	sw	a1, %lo(Csym(knl_dispatch_disabled))(a0)	// Dispatch disable

	lui	s4, %hi(Csym(knl_ctxtsk))
	addi	s4, s4, %lo(Csym(knl_ctxtsk))		// S4: &ctxtsk
	lw	a7, (s4)				// A7: ctxtsk
	beqz	a7, 1f					// ctxtsk == NULL ?
	sw	sp, (TCB_tskctxb + CTXB_ssp)(a7)	// Save 'sp' to TCB
	sw	zero, (s4)				// ctxtsk = NULL
1:
l_dispatch0:
	lui	s5, %hi(Csym(knl_schedtsk))
	addi	s5, s5, %lo(Csym(knl_schedtsk))		// S5: &schedtsk
	lui	s6, %hi(Csym(knl_lowpow_discnt))
	addi	s6, s6, %lo(Csym(knl_lowpow_discnt))	// S6: &lowpow_discnt
l_dispatch1:
	li	a0, STATUS_MIE
	csrc	mstatus, a0				// disable interrupt

	lw	s7, (s5)				// S7: schedtsk
	bnez	s7, l_dispatch2				// 'schedtsk' exist?
							// yes -> jump
	/* Because there is no task that should be executed, move to the power-saving mode */
	lw	a0, (s6)				// Is 'low_pow' disabled?
	bnez	a0, 1f
	mv	s0, ra
	call	Csym(low_pow)				// call low_pow()
	mv	ra, s0
1:
	li      a0, STATUS_MIE
	csrs	mstatus, a0				// enable interrupt
	j	l_dispatch1

l_dispatch2:						// Switch to 'schedtsk'
	sw	s7, (s4)				// s4: &ctxtsk, s7: schedtsk

	// restore context
	lw	sp, (TCB_tskctxb + CTXB_ssp)(s7)	// Restore 'sp' from TCB
#if USE_FPU
TODO(FPU)
#endif /* USE_FPU */
	lui	a0, %hi(Csym(knl_dispatch_disabled))
	sw	zero, %lo(Csym(knl_dispatch_disabled))(a0)	// Dispatch enable

	lw	s0, 0*4(sp)	// restore registers
	lw	s1, 1*4(sp)
	lw	s2, 2*4(sp)
	lw	s3, 3*4(sp)
	lw	s4, 4*4(sp)
	lw	s5, 5*4(sp)
	lw	s6, 6*4(sp)
	lw	s7, 7*4(sp)
	lw	s8, 8*4(sp)
	lw	s9, 9*4(sp)
	lw	s10, 10*4(sp)
	lw	s11, 11*4(sp)
	addi    sp, sp, 4*12

	ret

#endif /* CPU_CORE_RISCV32 */
