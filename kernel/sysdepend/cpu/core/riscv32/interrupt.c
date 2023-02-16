#include <sys/machine.h>
#ifdef CPU_CORE_RISCV32

/*
 *	interrupt.c  (RISC-V 32)
 *	Interrupt control
 */

#include <kernel.h>
#include "../../../sysdepend.h"

/* Interrupt vector table */
Noinit(EXPORT FP knl_intvec_tbl[N_INTVEC]);

/* High level programming language interrupt handler table */
Noinit(EXPORT FP knl_hll_inthdr_tbl[N_INTVEC]);

/* ----------------------------------------------------------------------- */
/*
 * Set interrupt handler (Used in tk_def_int())
 */
EXPORT ER knl_define_inthdr( INT intno, ATR intatr, FP inthdr )
{
	if ((inthdr != NULL) && (intatr & TA_HLNG)) {
		knl_hll_inthdr_tbl[intno] = inthdr;
		inthdr = knl_hll_inthdr;
	}
	knl_intvec_tbl[intno] = inthdr;

	return E_OK;
}

/* ----------------------------------------------------------------------- */
/*
 * Return interrupt handler (Used in tk_ret_int())
 */
EXPORT void knl_return_inthdr(void)
{
	/* XXX didn't support tk_ret_int XXX */
	return;
}

/* ------------------------------------------------------------------------ */
/*
 * Interrupt initialize
 */
Inline ULONG knl_read_and_set_mie(ULONG mask)
{
	ULONG rtn;
	asm("csrrs %0, mie, %1":"=r"(rtn):"r"(mask));
	return rtn;
}
Inline void SetTrapVectors(unsigned long addr)
{
	Asm("csrw mtvec, %0" : : "r"(addr));
}
EXPORT ER knl_init_interrupt( void )
{
	knl_intvec_tbl[0] = NULL;
	knl_hll_inthdr_tbl[0] = NULL;
	for (INT intno = 1; intno < N_INTVEC; ++intno) {
		knl_intvec_tbl[intno] = NULL;
		knl_hll_inthdr_tbl[intno] = NULL;
		DisableInt(intno);
	}

	/* Register exception handler used on OS */
	// RISC-V の PLIC では 0 番は使われないのでそれをタイマハンドラ用に使う
	knl_define_inthdr(0, TA_HLNG, (FP)&knl_timer_handler);	/* System Timer Interruput */

	SetTrapVectors((unsigned long)vector_table + 1);

	knl_read_and_set_mie(MIE_MEIE);

	return E_OK;
}

#endif /* CPU_CORE_RISCV32 */
