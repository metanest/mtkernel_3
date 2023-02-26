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

	.extern Csym(knl_dispatch_entry)
	.extern Csym(knl_dispatch_to_schedtsk)
	.extern Csym(Exception_Handler)
	.extern Csym(Default_Handler)
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
	addi	sp, sp, -4*20
	sw	a0, 0*4(sp)
	sw	a1, 1*4(sp)
	sw	a2, 2*4(sp)
	sw	a3, 3*4(sp)
	sw	a4, 4*4(sp)
	sw	a5, 5*4(sp)
	sw	a6, 6*4(sp)
	sw	a7, 7*4(sp)
	sw	t0, 8*4(sp)
	sw	t1, 9*4(sp)
	sw	t2, 10*4(sp)
	sw	t3, 11*4(sp)
	sw	t4, 12*4(sp)
	sw	t5, 13*4(sp)
	sw	t6, 14*4(sp)
	sw	ra, 15*4(sp)

	csrr	t0, mepc
	sw	t0, 16*4(sp)
	csrr	t0, mstatus
	sw	t0, 17*4(sp)

	csrr	t0, mcause		// exceptionの原因が
	li	t1, 11			// ecallか?
	bne	t0, t1, 2f		// ecall以外ならジャンプ

	lw	t0, 16*4(sp)
	addi	t0, t0, 4		// 戻りアドレス(mepc)をecallの次へ
	sw	t0, 16*4(sp)

	addi	a0, a0, -1
	bnez	a0, 1f
	call	Csym(knl_dispatch_entry)
	j	3f
1:	addi	a0, a0, -1
	bnez	a0, 2f
	call	Csym(knl_dispatch_to_schedtsk)
	j	3f
2:
	call	Csym(Exception_Handler)
3:
	lw	t0, 16*4(sp)
	csrw	mepc, t0
	lw	t0, 17*4(sp)
	csrw	mstatus, t0

	lw	a0, 0*4(sp)
	lw	a1, 1*4(sp)
	lw	a2, 2*4(sp)
	lw	a3, 3*4(sp)
	lw	a4, 4*4(sp)
	lw	a5, 5*4(sp)
	lw	a6, 6*4(sp)
	lw	a7, 7*4(sp)
	lw	t0, 8*4(sp)
	lw	t1, 9*4(sp)
	lw	t2, 10*4(sp)
	lw	t3, 11*4(sp)
	lw	t4, 12*4(sp)
	lw	t5, 13*4(sp)
	lw	t6, 14*4(sp)
	lw	ra, 15*4(sp)
	addi	sp, sp, 4*20
	mret

	.balign 4
undefined_handler:
	addi	sp, sp, -4*20
	sw	a0, 0*4(sp)
	sw	a1, 1*4(sp)
	sw	a2, 2*4(sp)
	sw	a3, 3*4(sp)
	sw	a4, 4*4(sp)
	sw	a5, 5*4(sp)
	sw	a6, 6*4(sp)
	sw	a7, 7*4(sp)
	sw	t0, 8*4(sp)
	sw	t1, 9*4(sp)
	sw	t2, 10*4(sp)
	sw	t3, 11*4(sp)
	sw	t4, 12*4(sp)
	sw	t5, 13*4(sp)
	sw	t6, 14*4(sp)
	sw	ra, 15*4(sp)

	csrr	t0, mepc
	sw	t0, 16*4(sp)
	csrr	t0, mstatus
	sw	t0, 17*4(sp)

	call	Csym(Default_Handler)

	lw	t0, 16*4(sp)
	csrw	mepc, t0
	lw	t0, 17*4(sp)
	csrw	mstatus, t0

	lw	a0, 0*4(sp)
	lw	a1, 1*4(sp)
	lw	a2, 2*4(sp)
	lw	a3, 3*4(sp)
	lw	a4, 4*4(sp)
	lw	a5, 5*4(sp)
	lw	a6, 6*4(sp)
	lw	a7, 7*4(sp)
	lw	t0, 8*4(sp)
	lw	t1, 9*4(sp)
	lw	t2, 10*4(sp)
	lw	t3, 11*4(sp)
	lw	t4, 12*4(sp)
	lw	t5, 13*4(sp)
	lw	t6, 14*4(sp)
	lw	ra, 15*4(sp)
	addi	sp, sp, 4*20
	mret

	.balign 4
timer_handler:
	addi	sp, sp, -4*20
	sw	a0, 0*4(sp)
	sw	a1, 1*4(sp)
	sw	a2, 2*4(sp)
	sw	a3, 3*4(sp)
	sw	a4, 4*4(sp)
	sw	a5, 5*4(sp)
	sw	a6, 6*4(sp)
	sw	a7, 7*4(sp)
	sw	t0, 8*4(sp)
	sw	t1, 9*4(sp)
	sw	t2, 10*4(sp)
	sw	t3, 11*4(sp)
	sw	t4, 12*4(sp)
	sw	t5, 13*4(sp)
	sw	t6, 14*4(sp)
	sw	ra, 15*4(sp)

	csrr	t0, mepc
	sw	t0, 16*4(sp)
	csrr	t0, mstatus
	sw	t0, 17*4(sp)

	mv	a0, zero
	call	Csym(knl_hll_inthdr)

	lw	t0, 16*4(sp)
	csrw	mepc, t0
	lw	t0, 17*4(sp)
	csrw	mstatus, t0

	lw	a0, 0*4(sp)
	lw	a1, 1*4(sp)
	lw	a2, 2*4(sp)
	lw	a3, 3*4(sp)
	lw	a4, 4*4(sp)
	lw	a5, 5*4(sp)
	lw	a6, 6*4(sp)
	lw	a7, 7*4(sp)
	lw	t0, 8*4(sp)
	lw	t1, 9*4(sp)
	lw	t2, 10*4(sp)
	lw	t3, 11*4(sp)
	lw	t4, 12*4(sp)
	lw	t5, 13*4(sp)
	lw	t6, 14*4(sp)
	lw	ra, 15*4(sp)
	addi	sp, sp, 4*20
	mret

	.balign 4
external_handler:
	addi	sp, sp, -4*20
	sw	a0, 0*4(sp)
	sw	a1, 1*4(sp)
	sw	a2, 2*4(sp)
	sw	a3, 3*4(sp)
	sw	a4, 4*4(sp)
	sw	a5, 5*4(sp)
	sw	a6, 6*4(sp)
	sw	a7, 7*4(sp)
	sw	t0, 8*4(sp)
	sw	t1, 9*4(sp)
	sw	t2, 10*4(sp)
	sw	t3, 11*4(sp)
	sw	t4, 12*4(sp)
	sw	t5, 13*4(sp)
	sw	t6, 14*4(sp)
	sw	ra, 15*4(sp)

	csrr	t0, mepc
	sw	t0, 16*4(sp)
	csrr	t0, mstatus
	sw	t0, 17*4(sp)

	lui	a0, %hi(PLIC_CLAIM_COMPLETE)
	lw	a0, %lo(PLIC_CLAIM_COMPLETE)(a0)
	beqz	a0, 2f

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
	lw	t0, 16*4(sp)
	csrw	mepc, t0
	lw	t0, 17*4(sp)
	csrw	mstatus, t0

	lw	a0, 0*4(sp)
	lw	a1, 1*4(sp)
	lw	a2, 2*4(sp)
	lw	a3, 3*4(sp)
	lw	a4, 4*4(sp)
	lw	a5, 5*4(sp)
	lw	a6, 6*4(sp)
	lw	a7, 7*4(sp)
	lw	t0, 8*4(sp)
	lw	t1, 9*4(sp)
	lw	t2, 10*4(sp)
	lw	t3, 11*4(sp)
	lw	t4, 12*4(sp)
	lw	t5, 13*4(sp)
	lw	t6, 14*4(sp)
	lw	ra, 15*4(sp)
	addi	sp, sp, 4*20
	mret

#endif	/* CPU_CORE_RISCV32 */
