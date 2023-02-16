/*
 *	ser_mode_sysdep.h
 *	Serial communication device driver
 *	Communication mode definition for FE310-G002
 */

#ifndef	__DEV_SER_MODE_FE310G002_H__
#define	__DEV_SER_MODE_FE310G002_H__

#define	DEV_SER_MODE_7BIT	(0x00000040)	/* Word length 7bit */
#define	DEV_SER_MODE_8BIT	(0x00000000)	/* Word length 8bit */

#define	DEV_SER_MODE_1STOP	(0x00000000)	/* Stop-bit 1bit */
#define	DEV_SER_MODE_2STOP	(0x00000008)	/* Stop-bit 2bit */

#define DEV_SER_MODE_PODD	(0x00000030)	/* parity Odd */
#define DEV_SER_MODE_PEVEN	(0x00000020)	/* parity Even */
#define DEV_SER_MODE_PNON	(0x00000000)	/* parity None */

#define	DEV_SER_MODE_CTSEN	(0x00008000)	/* CTS Hard flow control enable */
#define	DEV_SER_MODE_RTSEN	(0x00004000)	/* RTS Hard flow control enable */

/* Communication Error */
//TODO
#define	DEV_SER_ERR_PE		(1<<3)	/* Parity Error */
#define	DEV_SER_ERR_FE		(1<<4)	/* Framing Error */
#define	DEV_SER_ERR_OE		(1<<5)	/* Overrun Error */


#endif /* __DEV_SER_MODE_FE310G002_H__ */
