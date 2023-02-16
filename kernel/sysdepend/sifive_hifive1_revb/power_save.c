#include <tk/tkernel.h>
#include <kernel.h>

#ifdef SIFIVE_HIFIVE_REVB

/*
 *	power_save.c (SiFive HiFive1 Rev B)
 *	Power-Saving Function
 */

#include "sysdepend.h"

/*
 * Switch to power-saving mode
 */
EXPORT void low_pow( void )
{
}

/*
 * Move to suspend mode
 */
EXPORT void off_pow( void )
{
}


#endif /* SIFIVE_HIFIVE_REVB */
