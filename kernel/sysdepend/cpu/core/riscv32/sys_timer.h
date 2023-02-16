/*
 *	sys_timer.h (RISC-V 32)
 *	Hardware-Dependent System Timer (SysTick) Processing
 */

#ifndef _SYSDEPEND_CPU_CORE_SYSTIMER_
#define _SYSDEPEND_CPU_CORE_SYSTIMER_

Inline ULONG knl_read_and_clear_mie(ULONG mask)
{
	ULONG rtn;
	asm("csrrc %0, mie, %1":"=r"(rtn):"r"(mask));
	return rtn;
}

Inline ULONG knl_read_and_set_mie(ULONG mask)
{
	ULONG rtn;
	asm("csrrs %0, mie, %1":"=r"(rtn):"r"(mask));
	return rtn;
}

Inline unsigned long long get_mtime(void)
{
	const unsigned hi0 = in_w(MTIME_HI);
	unsigned lo = in_w(MTIME_LO);
	const unsigned hi1 = in_w(MTIME_HI);
	if (hi1 != hi0) {
		lo = in_w(MTIME_LO);
	}
	return ((unsigned long long)hi1 << 32) + (unsigned long long)lo;
}

/*
 * Timer start processing
 *	Initialize the timer and start the periodical timer interrupt.
 */
Inline void knl_start_hw_timer( void )
{
	ULONG imask;

	DI(imask);

	unsigned long long now = get_mtime();
	unsigned long long set_time = now +
		(unsigned long long)TIMER_PERIOD * LFCLK / 1000;

	// 一時的に mtimecmp が小さな値になることを防ぐ。The RISC-V Instruction Set Manual
	// Volume II: Privileged Architecture (Ver. 20211203) pp. 45-46 を参照
	out_w(MTIMECMP_LO, ~0U);

	out_w(MTIMECMP_HI, (unsigned)(set_time >> 32));
	out_w(MTIMECMP_LO, (unsigned)set_time);

	knl_read_and_set_mie(MIE_MTIE);

	EI(imask);
}

/*
 * Clear timer interrupt
 *	Clear the timer interrupt request. Depending on the type of
 *	hardware, there are two timings for clearing: at the beginning
 *	and the end of the interrupt handler.
 *	'clear_hw_timer_interrupt()' is called at the beginning of the
 *	timer interrupt handler.
 *	'end_of_hw_timer_interrupt()' is called at the end of the timer
 *	interrupt handler.
 *	Use either or both according to hardware.
 */
Inline void knl_clear_hw_timer_interrupt( void )
{
	static unsigned reminder = 0;
	unsigned offset = reminder + TIMER_PERIOD * LFCLK;
	reminder = offset % 1000;
 	offset /= 1000;
	unsigned lo = in_w(MTIMECMP_LO);
	unsigned hi = in_w(MTIMECMP_HI);
	unsigned long long previous = ((unsigned long long)hi << 32) + lo;
	unsigned long long set_time = previous + (unsigned long long)offset;

	out_w(MTIMECMP_LO, ~0U);

	out_w(MTIMECMP_HI, (unsigned)(set_time >> 32));
	out_w(MTIMECMP_LO, (unsigned)set_time);
}

Inline void knl_end_of_hw_timer_interrupt( void )
{
	/* Nothing required to do at this point */
}

/*
 * Timer stop processing
 *	Stop the timer operation.
 *	Called when system stops.
 */
Inline void knl_terminate_hw_timer( void )
{
	knl_read_and_clear_mie(MIE_MTIE);
}

/*
 * Get processing time from the previous timer interrupt to the
 * current (nanosecond)
 *	Consider the possibility that the timer interrupt occurred
 *	during the interrupt disable and calculate the processing time
 *	within the following
 *	range: 0 <= Processing time < TIMER_PERIOD * 2
 */
Inline UW knl_get_hw_timer_nsec( void )
{
	//TODO
	return 0;
}

#endif /* _SYSDEPEND_CPU_CORE_SYSTIMER_ */
