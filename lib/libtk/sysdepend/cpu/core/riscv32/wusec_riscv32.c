#include <sys/machine.h>
#ifdef CPU_CORE_RISCV32

/*
 *	waitusec_armv7m.c
 *
 *	Micro Wait: Busy loop wait time in micro-sec (ARMv7M)
 */

#include <tk/tkernel.h>
#include <config.h>

LOCAL unsigned long long get_mtime(void)
{
	const unsigned hi0 = in_w(MTIME_HI);
	unsigned lo = in_w(MTIME_LO);
	const unsigned hi1 = in_w(MTIME_HI);
	if (hi1 != hi0) {
		lo = in_w(MTIME_LO);
	}
	return ((unsigned long long)hi1 << 32) + (unsigned long long)lo;
}

LOCAL void wait_us( UW usec )
{
	const unsigned long long offset = usec * LFCLK / 1000000;
	const unsigned long long start = get_mtime();
	const unsigned long long final = start + offset;

	for (;;) {
		unsigned long long now = get_mtime();
		if (now > final)
			break;
	}
}

/* maximum time (in microseconds) that wait_us() can handle at a time */
#define WAIT_US_STEP 10000

EXPORT void WaitUsec( UW usec )
{
	for ( ; usec >= WAIT_US_STEP; usec -= WAIT_US_STEP ) {
		wait_us(WAIT_US_STEP);
	}
	wait_us(usec);
}

EXPORT void WaitNsec( UW nsec )
{
	for ( ; nsec >= (WAIT_US_STEP * 1000); nsec -= (WAIT_US_STEP * 1000) ) {
		wait_us(WAIT_US_STEP);
	}
	wait_us(nsec / 1000 + 1);
}

#endif /* CPU_CORE_RISCV32 */
