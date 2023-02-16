/*
 *	machine.h
 *
 *	Machine type definition (RISC-V 32 depended)
 */

#ifndef __SYS_MACHINE_CORE_H__
#define __SYS_MACHINE_CORE_H__

/*
 * CPU_xxxx		CPU type
 * ALLOW_MISALIGN	1 if access to misalignment data is allowed
 * INT_BITWIDTH		Integer bit width
 * BIGENDIAN		1 if big endian
 */

/* ----- RISC-V 32 definition ----- */

#define ALLOW_MISALIGN		0
#define INT_BITWIDTH		32

/*
 * Endianness
 */
#define BIGENDIAN		0	/* Default (Little Endian) */

#endif /* __SYS_MACHINE_CORE_H__ */
