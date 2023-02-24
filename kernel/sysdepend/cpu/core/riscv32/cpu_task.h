/*
 *	cpu_task.h (RISC-V 32)
 *	CPU-Dependent Task Start Processing
 */

#ifndef _SYSDEPEND_CPU_CORE_CPUTASK_
#define _SYSDEPEND_CPU_CORE_CPUTASK_

/*
 * System stack configuration at task startup
 */
typedef struct {
	VW	s[12];  // s0-s11
	VW	a[8];   // a0-a7
	VW	t[7];   // t0-t6
	void	*ra;
	void	*epc;
	VW	status;
	VW	workspace0;
	VW	workspace1;
} SStackFrame;

/*
 * Size of system stack area destroyed by 'make_dormant()'
 * In other words, the size of area required to write by 'knl_setup_context().'
 */
//#define DORMANT_STACK_SIZE

#if USE_FPU
//TODO(FPU)
#endif /* USE_FPU */

/*
 * Create stack frame for task startup
 *	Call from 'make_dormant()'
 */
Inline void knl_setup_context( TCB *tcb )
{
	SStackFrame	*ssp;

	ssp = tcb->isstack;

#if USE_FPU
//TODO(FPU)
#endif /* USE_FPU */

	ssp--;

	/* CPU context initialization */
	ssp->ra = NULL;
	ssp->epc = tcb->task;		/* Task startup address */
	ssp->status = 0x00001880;	/* Initial status */
					/* MPP=11, MPIE=1 */
	tcb->tskctxb.ssp = ssp;		/* System stack */
}

/*
 * Set task startup code
 *	Called by 'tk_sta_tsk()' processing.
 */
Inline void knl_setup_stacd( TCB *tcb, INT stacd )
{
	SStackFrame	*ssp = tcb->tskctxb.ssp;

	ssp->a[0] = stacd;
	ssp->a[1] = (VW)tcb->exinf;
}

/*
 * Delete task contexts
 */
Inline void knl_cleanup_context( TCB *tcb )
{
#if	USE_FPU
//TODO(FPU)
#endif	// USE_FPU
}

#endif /* _SYSDEPEND_CPU_CORE_CPUTASK_ */
