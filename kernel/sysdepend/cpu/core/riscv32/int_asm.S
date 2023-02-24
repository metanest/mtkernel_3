#include <sys/machine.h>
#ifdef CPU_CORE_RISCV32

/*
 *	int_asm.S  (RISC-V 32)
 *	Interrupt control assembler routine
 */

#define	_in_asm_source_
#include <sys/sysdef.h>
#include <sys/knldef.h>

/* ------------------------------------------------------------------------ */
/*
 * High level programming language routine for interrupt handler
 *	Called by interrupt entry routine.
 *
 *	input :   r0 : Vector number
 *      stack image
 *       Low Address +---------------+
 *             sp -> | R0            |
 *                   | R1            |
 *                   | R2            |
 *                   | R3            |
 *                   | R12(ip)       |
 *                   | R14_svc(lr)   |
 *                   | R14_xxx(lr)   | Return address (pc)
 *                   | SPSR_xxx      |
 *      High Address +---------------+
 */
	.text
	.balign 4
	.globl	Csym(knl_hll_inthdr)
	.type	Csym(knl_hll_inthdr), %function

Csym(knl_hll_inthdr):
	lui	a1, %hi(Csym(knl_taskindp))
	lw	a2, %lo(Csym(knl_taskindp))(a1)
	addi	a3, a2, 1
	sw	a3, %lo(Csym(knl_taskindp))(a1)	// knl_taskindp++

						// 1st interrupt ?
	bnez	a2, not_1st_hllint		//      no => jump

	mv	a1, sp
	lui	a2, %hi(0x80004000)		// INITIAL_SP
	addi	a2, a2, %lo(0x80004000)		// XXX
	mv	sp, a2
#if USE_FPU & INTHDR_DIS_FPU
TODO(FPU)
#endif /* USE_FPU */
	addi	sp, sp, -4
	sw	a1, 0(sp)

not_1st_hllint:
	addi	sp, sp, -4
	sw	ra, 0(sp)

	lui	a1, %hi(Csym(knl_hll_inthdr_tbl))	// call knl_hll_inthdr_tbl[intno]()
	addi	a1, a1, %lo(Csym(knl_hll_inthdr_tbl))
	slli	a0, a0, 2
	add	a0, a0, a1
	lw	a0, (a0)
	jalr	(a0)

	li	a0, 0x8
	csrc	mstatus, a0			// disable interrupt

	lui	a1, %hi(Csym(knl_taskindp))
	lw	a2, %lo(Csym(knl_taskindp))(a1)
	addi	a2, a2, -1
	sw	a2, %lo(Csym(knl_taskindp))(a1)	// knl_taskindp--

	lw	ra, 0(sp)
	addi	sp, sp, 4

	bnez	a2, return_inthdr_end		// 1st interrupt ?
						//      no => jump

	lw	sp, 0(sp)			// restore task SP

#if USE_FPU & INTHDR_DIS_FPU
TODO(FPU)
#endif /* USE_FPU */

	// Dispatch disabled?
	lui	a0, %hi(Csym(knl_dispatch_disabled))
	lw	a0, %lo(Csym(knl_dispatch_disabled))(a0)
	bnez	a0, return_inthdr_end

	// dispatch necessary?
	lui	a0, %hi(Csym(knl_ctxtsk))
	lw	a0, %lo(Csym(knl_ctxtsk))(a0)
	lui	a1, %hi(Csym(knl_schedtsk))
	lw	a1, %lo(Csym(knl_schedtsk))(a1)
	beq	a0, a1, return_inthdr_end
	j	knl_dispatch_entry		// goto dispatch processing
return_inthdr_end:
	ret

#endif	/* CPU_CORE_RISCV32 */
