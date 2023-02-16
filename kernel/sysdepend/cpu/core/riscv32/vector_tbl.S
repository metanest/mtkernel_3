#include <sys/machine.h>
#ifdef CPU_CORE_RISCV32

/*
 *	vector_tbl.S  (RISC-V 32)
 *	Interrupt Vector Table
 */
	.equ	PLIC_CLAIM_COMPLETE, 0x0C200004

	.section .vector, "ax"

/* ---------------------------------------------------------------------------------
 *	Exception Vector Table
 */
	.global Csym(vector_table)

	.extern Csym(Exception_Handler)
	.extern Csym(Default_Handler)
	.extern Csym(knl_systim_inthdr)
	.extern Csym(knl_intvec_tbl)

	.balign 128
Csym(vector_table):
	j exception_handler  //  0 - exception
	.balign 4
	j undefined_handler  //  1
	.balign 4
	j undefined_handler  //  2
	.balign 4
	j undefined_handler  //  3
	.balign 4
	j undefined_handler  //  4
	.balign 4
	j undefined_handler  //  5
	.balign 4
	j undefined_handler  //  6
	.balign 4
	j timer_handler      //  7 - timer interrupt
	.balign 4
	j undefined_handler  //  8
	.balign 4
	j undefined_handler  //  9
	.balign 4
	j undefined_handler  // 10
	.balign 4
	j external_handler   // 11 - external interrupt
	.balign 4
	j undefined_handler  // 12
	.balign 4
	j undefined_handler  // 13
	.balign 4
	j undefined_handler  // 14
	.balign 4
	j undefined_handler  // 15

	.balign 4
exception_handler:
	addi	sp, sp, -4*16
	sw	ra, 0*4(sp)
	sw	a0, 1*4(sp)
	sw	a1, 2*4(sp)
	sw	a2, 3*4(sp)
	sw	a3, 4*4(sp)
	sw	a4, 5*4(sp)
	sw	a5, 6*4(sp)
	sw	a6, 7*4(sp)
	sw	a7, 8*4(sp)
	sw	t0, 9*4(sp)
	sw	t1, 10*4(sp)
	sw	t2, 11*4(sp)
	sw	t3, 12*4(sp)
	sw	t4, 13*4(sp)
	sw	t5, 14*4(sp)
	sw	t6, 15*4(sp)
	call	Csym(Exception_Handler)
	lw	ra, 0*4(sp)
	lw	a0, 1*4(sp)
	lw	a1, 2*4(sp)
	lw	a2, 3*4(sp)
	lw	a3, 4*4(sp)
	lw	a4, 5*4(sp)
	lw	a5, 6*4(sp)
	lw	a6, 7*4(sp)
	lw	a7, 8*4(sp)
	lw	t0, 9*4(sp)
	lw	t1, 10*4(sp)
	lw	t2, 11*4(sp)
	lw	t3, 12*4(sp)
	lw	t4, 13*4(sp)
	lw	t5, 14*4(sp)
	lw	t6, 15*4(sp)
	addi	sp, sp, 4*16
	mret

	.balign 4
undefined_handler:
	addi	sp, sp, -4*16
	sw	ra, 0*4(sp)
	sw	a0, 1*4(sp)
	sw	a1, 2*4(sp)
	sw	a2, 3*4(sp)
	sw	a3, 4*4(sp)
	sw	a4, 5*4(sp)
	sw	a5, 6*4(sp)
	sw	a6, 7*4(sp)
	sw	a7, 8*4(sp)
	sw	t0, 9*4(sp)
	sw	t1, 10*4(sp)
	sw	t2, 11*4(sp)
	sw	t3, 12*4(sp)
	sw	t4, 13*4(sp)
	sw	t5, 14*4(sp)
	sw	t6, 15*4(sp)
	call	Csym(Default_Handler)
	lw	ra, 0*4(sp)
	lw	a0, 1*4(sp)
	lw	a1, 2*4(sp)
	lw	a2, 3*4(sp)
	lw	a3, 4*4(sp)
	lw	a4, 5*4(sp)
	lw	a5, 6*4(sp)
	lw	a6, 7*4(sp)
	lw	a7, 8*4(sp)
	lw	t0, 9*4(sp)
	lw	t1, 10*4(sp)
	lw	t2, 11*4(sp)
	lw	t3, 12*4(sp)
	lw	t4, 13*4(sp)
	lw	t5, 14*4(sp)
	lw	t6, 15*4(sp)
	addi	sp, sp, 4*16
	mret

	.balign 4
timer_handler:
	addi	sp, sp, -4*16
	sw	ra, 0*4(sp)
	sw	a0, 1*4(sp)
	sw	a1, 2*4(sp)
	sw	a2, 3*4(sp)
	sw	a3, 4*4(sp)
	sw	a4, 5*4(sp)
	sw	a5, 6*4(sp)
	sw	a6, 7*4(sp)
	sw	a7, 8*4(sp)
	sw	t0, 9*4(sp)
	sw	t1, 10*4(sp)
	sw	t2, 11*4(sp)
	sw	t3, 12*4(sp)
	sw	t4, 13*4(sp)
	sw	t5, 14*4(sp)
	sw	t6, 15*4(sp)
	mv	a0, zero
	call	Csym(knl_hll_inthdr)
	lw	ra, 0*4(sp)
	lw	a0, 1*4(sp)
	lw	a1, 2*4(sp)
	lw	a2, 3*4(sp)
	lw	a3, 4*4(sp)
	lw	a4, 5*4(sp)
	lw	a5, 6*4(sp)
	lw	a6, 7*4(sp)
	lw	a7, 8*4(sp)
	lw	t0, 9*4(sp)
	lw	t1, 10*4(sp)
	lw	t2, 11*4(sp)
	lw	t3, 12*4(sp)
	lw	t4, 13*4(sp)
	lw	t5, 14*4(sp)
	lw	t6, 15*4(sp)
	addi	sp, sp, 4*16
	mret

	.balign 4
external_handler:
	addi	sp, sp, -4*17
	sw	ra, 0*4(sp)
	sw	a0, 1*4(sp)
	sw	a1, 2*4(sp)
	sw	a2, 3*4(sp)
	sw	a3, 4*4(sp)
	sw	a4, 5*4(sp)
	sw	a5, 6*4(sp)
	sw	a6, 7*4(sp)
	sw	a7, 8*4(sp)
	sw	t0, 9*4(sp)
	sw	t1, 10*4(sp)
	sw	t2, 11*4(sp)
	sw	t3, 12*4(sp)
	sw	t4, 13*4(sp)
	sw	t5, 14*4(sp)
	sw	t6, 15*4(sp)

	lui	a0, %hi(PLIC_CLAIM_COMPLETE)
	lw	a0, %lo(PLIC_CLAIM_COMPLETE)(a0)
	beqz	a0, 3f
	sw	a0, 16*4(sp)

	lui	a1, %hi(Csym(knl_intvec_tbl))
	addi	a1, a1, %lo(Csym(knl_intvec_tbl))
	slli	a0, a0, 2
	add	a1, a1, a0
	srli	a0, a0, 2
	lw	a1, (a1)
	beqz	a1, 1f
	jalr	(a1)
	j	2f
1:
	call	Csym(Default_Handler)
2:
	lw	a1, 16*4(sp)
	lui	a0, %hi(PLIC_CLAIM_COMPLETE)
	sw	a1, %lo(PLIC_CLAIM_COMPLETE)(a0)
3:
	lw	ra, 0*4(sp)
	lw	a0, 1*4(sp)
	lw	a1, 2*4(sp)
	lw	a2, 3*4(sp)
	lw	a3, 4*4(sp)
	lw	a4, 5*4(sp)
	lw	a5, 6*4(sp)
	lw	a6, 7*4(sp)
	lw	a7, 8*4(sp)
	lw	t0, 9*4(sp)
	lw	t1, 10*4(sp)
	lw	t2, 11*4(sp)
	lw	t3, 12*4(sp)
	lw	t4, 13*4(sp)
	lw	t5, 14*4(sp)
	lw	t6, 15*4(sp)
	addi	sp, sp, 4*17
	mret

#endif	/* CPU_CORE_RISCV32 */
