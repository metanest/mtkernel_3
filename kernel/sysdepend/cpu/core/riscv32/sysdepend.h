/*
 *	sysdepend.h (RISC-V 32)
 *	System-Dependent local defined
 */

#ifndef _SYSDEPEND_CPU_CORE_SYSDEPEND_
#define _SYSDEPEND_CPU_CORE_SYSDEPEND_

/*
 *    Exception Handler (exc_hdr.c)
 */
//IMPORT void UndefinedInst_Handler(void);	/* Undefined instruction exception handler */
//IMPORT void PrefetchAbort_Handler(void);	/* Prefetch abort exception handler */
//IMPORT void DataAbort_Handler(void);		/* Data abort exception handler */
//IMPORT void VFPInvalid_Handler(void);		/* VFP invalid handler */

IMPORT void Default_Handler(void);		/* Default Handler (Undefine Interrupt) */
//IMPORT void SVC_default_Handler(void);	/* SVC default Handler (Undefine SVC) */

/*
 * Dispatcher (dispatch.S)
 */
IMPORT void knl_dispatch_entry(void);		/* dispatch entry */
IMPORT void knl_dispatch_to_schedtsk(void);	/* force dispatch */

/*
 * Interrupt Control (interrupt.c)
 */
IMPORT FP knl_intvec_tbl[N_INTVEC];		/* Interrupt vector table */
IMPORT FP knl_hll_inthdr_tbl[N_INTVEC];		/* High level programming language interrupt handler table */
//IMPORT const FP knl_svcvec_tbl[N_SVCHDR];	/* SVC handler table */
IMPORT void knl_systim_inthdr(void);		/* System-timer Interrupt handler */

/*
 * Interrupt Control (int_asm.S)
 */
IMPORT void knl_hll_inthdr(void);		/* High level programming language routine for interrupt handler */

/*
 * Interrupt vector (vector_tbl.S)
 */
IMPORT void *vector_table[];

/*
 * Task context block
 */
typedef struct {
	void	*ssp;		/* System stack pointer */
} CTXB;


#endif /* _SYSDEPEND_CPU_CORE_SYSDEPEND_ */
