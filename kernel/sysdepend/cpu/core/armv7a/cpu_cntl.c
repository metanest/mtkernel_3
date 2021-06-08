/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.00.05.B0
 *
 *    Copyright (C) 2006-2021 by Ken Sakamura.
 *    This software is distributed under the T-License 2.2.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2021/.
 *
 *----------------------------------------------------------------------
 */

#include <sys/machine.h>
#ifdef CPU_CORE_ARMV7A
/*
 *	cpu_cntl.c (ARMv7-A)
 *	CPU-Dependent Control
 */
#include "kernel.h"
#include "../../../sysdepend.h"

#include "cpu_task.h"


/* Temporal stack used when 'dispatch_to_schedtsk' is called */
Noinit(EXPORT UB knl_tmp_stack[TMP_STACK_SIZE]);

/* Task independent status */
EXPORT	W	knl_taskindp = 0;

/* ------------------------------------------------------------------------ */
/*
 * Set task register contents (Used in tk_set_reg())
 */
EXPORT void knl_set_reg( TCB *tcb, CONST T_REGS *regs, CONST T_EIT *eit, CONST T_CREGS *cregs )
{
	INT	i;
	SStackFrame	*ssp;

	ssp = tcb->tskctxb.ssp;

	if ( cregs != NULL ) {
		ssp = cregs->ssp;
		tcb->tskctxb.ssp  = ssp;
	}

	if ( regs != NULL ) {
		for ( i = 0; i < 4; ++i ) {
			ssp->r[i] = regs->r[i];
		}
		for ( i = 4; i < 12; ++i){
			ssp->r_[i - 4] = regs->r[i];
		}
		ssp->ip = regs->r[12];
		ssp->lr = regs->lr;
	}

	if ( eit != NULL ) {
		ssp->pc       = eit->pc;
		ssp->xpsr = eit->xpsr;
	}

#if USE_FPU
	if (tcb->tskatr & TA_FPU) {
		FPUContext	*fpu = tcb->isstack;
		if (tcb == knl_fpu_ctx) {
			/* save FPU context */
			IMPORT void knl_save_fpuctx( TCB* );
			knl_save_fpuctx(tcb);
			knl_fpu_ctx = NULL;
		}
		if( regs != NULL ){
			for ( i = 0; i < 32; i++ ) {
				fpu->d[i] = regs->d[i];
			}
		}
		if( cregs != NULL ){
			fpu->fpscr = cregs->fpscr;
		}
	}
#endif	// USE_FPU
}

/* ------------------------------------------------------------------------ */
/*
 * Get task register contents (Used in tk_get_reg())
 */
EXPORT void knl_get_reg( TCB *tcb, T_REGS *regs, T_EIT *eit, T_CREGS *cregs )
{
	INT		i;
	SStackFrame	*ssp;

	ssp = tcb->tskctxb.ssp;

	if ( regs != NULL ) {
		for ( i = 0; i < 4; ++i ) {
			regs->r[i] = ssp->r[i];
		}
		for ( i = 4; i < 12; ++i ){
			regs->r[i] = ssp->r_[i - 4];
		}
		regs->r[12] = ssp->ip;
		regs->lr = ssp->lr;
	}

	if ( eit != NULL ) {
		eit->pc       = ssp->pc;
		eit->xpsr     = ssp->xpsr;
		eit->taskmode = 0;
	}

	if ( cregs != NULL ) {
		cregs->ssp   = tcb->tskctxb.ssp;
	}

#if	USE_FPU
	if (tcb->tskatr & TA_FPU) {
		FPUContext	*fpu = tcb->isstack;
		if (tcb == knl_fpu_ctx) {
			/* save FPU context */
			IMPORT void knl_save_fpuctx( TCB* );
			knl_save_fpuctx(tcb);
		}
		if (regs != NULL) {
			for (i = 0; i < 32; i++) {
				regs->d[i] = fpu->d[i];
			}
		}
		if (cregs != NULL){
			cregs->fpscr = fpu->fpscr;
		}
	}
#endif	// USE_FPU
}

#if USE_FPU
#ifdef USE_FUNC_TK_SET_CPR
/* ------------------------------------------------------------------------ */
/*
 * Set task register contents (Used in tk_set_reg())
 */
EXPORT ER knl_set_cpr( TCB *tcb, INT copno, CONST T_COPREGS *copregs)
{
	SStackFrame_wFPU	*ssp;
	INT	i;

	ssp = (SStackFrame_wFPU*)(tcb->tskctxb.ssp);

	if(ssp->ufpu & EXPRN_NO_FPU ) {	/* FPU register is not saved */
		return E_CTX;
	}

	for ( i = 0; i < 16; ++i ) {
		ssp->s[i] = copregs->s[i];
		ssp->s_[i] = copregs->s[i + 16];
	}
	ssp->fpscr = copregs->fpscr;

	return E_OK;
}

#endif /* USE_FUNC_TK_SET_CPR */

#ifdef USE_FUNC_TK_GET_CPR
/* ------------------------------------------------------------------------ */
/*
 * Get task FPU register contents (Used in tk_get_cpr())
 */
EXPORT ER knl_get_cpr( TCB *tcb, INT copno, T_COPREGS *copregs)
{
	SStackFrame_wFPU	*ssp;
	INT	i;

	ssp = (SStackFrame_wFPU*)(tcb->tskctxb.ssp);

	if(ssp->ufpu & EXPRN_NO_FPU ) {	/* FPU register is not saved */
		return E_CTX;
	}

	for ( i = 0; i < 16; ++i ) {
		copregs->s[i] = ssp->s[i];
		copregs->s[i + 16] = ssp->s_[i];
	}
	copregs->fpscr = ssp->fpscr;

	return E_OK;
}
#endif /* USE_FUNC_TK_GET_CPR */
#endif /* USE_FPU */


/* ----------------------------------------------------------------------- */
/*
 *	Task dispatcher startup
 */
EXPORT void knl_force_dispatch( void )
{
	Asm("svc %0"::"i"(SVC_FORCE_DISPATCH):"lr");
}
EXPORT void knl_dispatch( void )
{
	Asm("svc %0"::"i"(SVC_DISPATCH):"lr");
}

#endif /* CPU_CORE_ARMV7M */
