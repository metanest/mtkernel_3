/*
 *    tm_com.c
 *    T-Monitor Communication low-level device driver (RZ/A2M IoT-Engine)
 */

#include <tk/tkernel.h>

#if USE_TMONITOR
#include "../../libtm.h"

#ifdef SIFIVE_HIFIVE_REVB
#if TM_COM_SERIAL_DEV

EXPORT	void	tm_snd_dat( const UB* buf, INT size )
{
	while (size--) {
		while (in_w(UART0_TXDATA) & 0x80000000)
			;
		out_w(UART0_TXDATA, (UW)*buf++);
	}
}

EXPORT	void	tm_rcv_dat( UB* buf, INT size )
{
	while (size--) {
		UW c;
		while ((c = in_w(UART0_RXDATA)) & 0x80000000)
			;
		*buf++ = (UB)c;
	}
}

EXPORT	void	tm_com_init(void)
{
	const unsigned div = HFCLK / 115200 - 1;
	out_w(UART0_DIV, div);
	out_w(UART0_TXCTRL, TXCTRL_NSTOP|TXCTRL_TXEN);
	out_w(UART0_RXCTRL, RXCTRL_RXEN);
}

#endif /* TM_COM_SERIAL_DEV */
#endif /* SIFIVE_HIFIVE_REVB */
#endif /* USE_TMONITOR */
