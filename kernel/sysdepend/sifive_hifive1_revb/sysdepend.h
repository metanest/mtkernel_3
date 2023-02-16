/*
 *	sysdepend.h (SiFive HiFive1 Rev B)
 *	System-Dependent local defined
 */

#ifndef _SYSDEPEND_TARGET_SYSDEPEND_
#define _SYSDEPEND_TARGET_SYSDEPEND_


#include "../cpu/fe310g002/sysdepend.h"

/*
 *    Clock Setting (cpu_clock.c)
 */
IMPORT void startup_clock(void);
IMPORT void shutdown_clock(void);

#endif /* _SYSDEPEND_TARGET_SYSDEPEND_ */
