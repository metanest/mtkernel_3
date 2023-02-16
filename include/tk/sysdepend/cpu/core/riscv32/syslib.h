/*
 *	syslib.h
 *
 *	micro T-Kernel System Library  (RISC-V 32 core depended)
 */

#ifndef __TK_SYSLIB_DEPEND_CORE_H__
#define __TK_SYSLIB_DEPEND_CORE_H__

#include <tk/errno.h>
#include <sys/sysdef.h>

/*----------------------------------------------------------------------*/
/*
 * CPU interrupt control for RISC-V.
 *	'intsts' is the value of mstatus.MIE.
 *	disint()  Disable interrupt.
 *	enaint()  Enable interrupt.
 */

IMPORT ULONG disint( void );
IMPORT void enaint( ULONG intsts );

#define DI(intsts)	( (intsts) = (UINT)disint() )
#define EI(intsts)	( enaint((UW)intsts) )
#define isDI(intsts)	( (intsts) != 0 )

#endif /* __TK_SYSLIB_DEPEND_CORE_H__ */
