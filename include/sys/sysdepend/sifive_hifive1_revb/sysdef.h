/*
 *	sysdef.h
 *
 *	System dependencies definition (SiFive HiFive1 Rev B depended)
 *	Included also from assembler program.
 */

#ifndef __SYS_SYSDEF_DEPEND_H__
#define __SYS_SYSDEF_DEPEND_H__


/* CPU-dependent definition */
#include "../cpu/fe310g002/sysdef.h"

/* ------------------------------------------------------------------------ */
/*
 * Clock control definition
 */

/* Clock frequency 　*/

#define HFCLK		16000000	// 16MHz
#define LFCLK		32768		// 32KiHz

/* ------------------------------------------------------------------------ */
/*
 * Maximum value of Power-saving mode switching prohibition request.
 * Use in tk_set_pow API.
 */
#define LOWPOW_LIMIT	0x7fff		/* Maximum number for disabling */

#endif /* __TK_SYSDEF_DEPEND_H__ */
