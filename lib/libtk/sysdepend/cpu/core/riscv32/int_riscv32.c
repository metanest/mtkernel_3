#include <sys/machine.h>
#ifdef CPU_CORE_RISCV32

/*
 *	int_riscv32.c
 *
 *	Interrupt controller (RISC-V 32)
 */

#include <tk/tkernel.h>

/*----------------------------------------------------------------------*/
/*
 * CPU Interrupt Control for RISC-V 32.
 *
 */

Inline ULONG knl_read_and_clear_mstatus(ULONG mask)
{
        ULONG rtn;
        asm("csrrc %0, mstatus, %1":"=r"(rtn):"r"(mask));
        return rtn;
}

Inline ULONG knl_read_and_set_mstatus(ULONG mask)
{
        ULONG rtn;
        asm("csrrs %0, mstatus, %1":"=r"(rtn):"r"(mask));
        return rtn;
}

/*
 * Disable interrupt
 *	Set mstatus.MIE value to 0. And return the invert of original mstatus.MIE value.
 */
EXPORT ULONG disint(void)
{
	const ULONG	mask = STATUS_MIE;
	ULONG 	intsts;

	intsts = knl_read_and_clear_mstatus(mask);

	return (intsts & mask) ^ mask;
	// EI(0)で割込み許可のため(仕様より)、1で割込み許可に
	// なるRISC-Vでは該当ビットを反転する必要がある
}

/*
 * Enable interrupt
 *	Sets the mstatus.MIE value to the specified value..
 */
EXPORT void enaint( ULONG intsts )
{
	const ULONG     mask = STATUS_MIE;

	if (intsts & mask) {
		knl_read_and_clear_mstatus(mask);	/* Disable */
	} else {
		knl_read_and_set_mstatus(mask);		/* Enable */
	}
	return;
}

/*----------------------------------------------------------------------*/
/*
 * RISC-V Platform-Level Interrupt Controller (PLIC)
 *
 */

/*
 * Set Interrupt Mask Level in Interrupt Controller
 */
EXPORT void SetCtrlIntLevel( INT level )
{
	if (level < INTPRI_LOWEST || level > INTPRI_HIGHEST) return;	/* Error */

	out_w(PLIC_THRESHOLD, level);

	return;
}

/*
 * Get Interrupt Mask Level in Interrupt Controller
 */
EXPORT INT GetCtrlIntLevel( void )
{
	UW level;

	level = in_w(PLIC_THRESHOLD);

	return (INT)level;
}

/*
 * Enable interrupt
 *	Enables the interrupt specified in intno.
 *	External Interrupt can be specified.
 */
EXPORT void EnableInt( UINT intno, INT level )
{
	if ((intno >= N_INTVEC)
		|| (level < INTPRI_LOWEST) || (level > INTPRI_HIGHEST)) return;	/* Error */

	/* Set priority */
	out_w(PLIC_PRIORITY(intno), level);

	/* Enable Interrupt */
	UW *addr = (UW *)PLIC_ENABLE + intno / 32;
	UW mask = 1 << (intno % 32);
	or_w((UW)addr, mask);
}

/*
 * Disable interrupt
 *	Disables the interrupt specified in intno.
 *	External Interrupt can be specified.
 */
EXPORT void DisableInt( UINT intno )
{
	if (intno >= N_INTVEC) return;		/* Error */

	/* Disable Interrupt */
	UW *addr = (UW *)PLIC_ENABLE + intno / 32;
	UW mask = 1 << (intno % 32);
	and_w((UW)addr, ~mask);
}

#if TK_SUPPORT_INTMODE
/*
 * Set interrupt mode
 *	Set the interrupt mode specified by `intvec' to the mode given
 *  	by `mode'. If an illegal mode is given, subsequent correct behavior
 *      of the system is not guaranteed.
 */
EXPORT void SetIntMode(  UINT intno, UINT mode )
{
#error not implemented
}
#endif /* TK_SUPPORT_INTMODE */

/*
 * Clear Interrupt
 *	Un-pends the associated interrupt under software control.
 *	External Interrupt can be specified.
 */
EXPORT void ClearInt( UINT intno )
{
	if (intno >= N_INTVEC) return;		/* Error */

	out_w(PLIC_CLAIM_COMPLETE, intno);
}

/*
 * Check active state
 *	Current active state for the associated interrupt
 *	External Interrupt can be specified.
 */
EXPORT BOOL CheckInt( UINT intno )
{
	if (intno >= N_INTVEC) return FALSE;	/* Error */

	UW *addr = (UW *)PLIC_PENDING + intno / 32;
	UW data = in_w((UW)addr);
	UW mask = 1 << (intno % 32);
	return (data & mask) ? TRUE : FALSE;
}

EXPORT void EndOfInt( UINT intno )
{
	if (intno >= N_INTVEC) return;		/* Error */

	out_w(PLIC_CLAIM_COMPLETE, intno);
}


#endif /* CPU_CORE_RISCV32 */
