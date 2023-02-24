/*
 *----------------------------------------------------------------------
 *    micro T-Kernel 3.00.06
 *
 *    Copyright (C) 2006-2022 by Ken Sakamura.
 *    This software is distributed under the T-License 2.2.
 *----------------------------------------------------------------------
 *
 *    Released by TRON Forum(http://www.tron.org) at 2022/10.
 *
 *----------------------------------------------------------------------
 */

#include <tk/tkernel.h>
#include <tm/tmonitor.h>


LOCAL ID disp_tsk_id;
LOCAL char buf[16];

LOCAL unsigned buf_head = 0;
LOCAL unsigned buf_last = 0;

LOCAL void disp_tsk(void)
{
	char tmp[16];
	for (;;) {
		unsigned i;
		tk_slp_tsk(TMO_FEVR);
		for (i = 0; buf_last != buf_head; ++i) {
			tmp[i] = buf[buf_last];
			buf_last = (buf_last + 1) % 16;
		}
		if (i > 0) {
			tmp[i] = '\0';
			tm_printf((UB*)"%s", tmp);
		}
	}
}

LOCAL void idle_tsk(void)
{
	for (;;) {
		tm_printf(" hello");
		for (int i=0;i<1000000;++i) {
		}
	}
}
LOCAL void tsk2(void)
{
	for (;;) {
		tm_printf(" world");
		tk_dly_tsk(10000);
	}
}

LOCAL void rx_hdr(void)
{
	buf[buf_head] = tm_getchar(0);
	buf_head = (buf_head + 1) % 16;
	tk_wup_tsk(disp_tsk_id);
	EndOfInt(3);
}

/* usermain関数 */
EXPORT INT usermain(void)
{
	T_RVER	rver;
	T_CTSK pk_ctsk = {
		.tskatr = TA_HLNG|TA_RNG0,
		.task = disp_tsk,
		.itskpri = 1,
		.stksz = 512,
	};
	T_CTSK pk_ctsk_idle = {
		.tskatr = TA_HLNG|TA_RNG0,
		.task = idle_tsk,
		.itskpri = TK_MAX_TSKPRI,
		.stksz = 512,
	};
	T_CTSK pk_ctsk2 = {
		.tskatr = TA_HLNG|TA_RNG0,
		.task = tsk2,
		.itskpri = 2,
		.stksz = 512,
	};
	T_DINT pk_dint = {
		.intatr = TA_HLNG,
		.inthdr = rx_hdr,
	};

	tm_putstring((UB*)"Start User-main program.\n");

	tk_ref_ver(&rver);		/* Get the OS Version. */

	tm_printf((UB*)"Make Code: %04x  Product ID: %04x\n", rver.maker, rver.prid);
	tm_printf((UB*)"Product Ver. %04x\nProduct Num. %04x %04x %04x %04x\n", 
			rver.prver, rver.prno[0],rver.prno[1],rver.prno[2],rver.prno[3]);

	disp_tsk_id = tk_cre_tsk(&pk_ctsk);
	tm_printf((UB*)"%d\n", disp_tsk_id);
	tk_sta_tsk(disp_tsk_id, 0);

	ID id = tk_cre_tsk(&pk_ctsk_idle);
	tm_printf((UB*)"%d\n", id);
	tk_sta_tsk(id, 0);

	id = tk_cre_tsk(&pk_ctsk2);
	tm_printf((UB*)"%d\n", id);
	tk_sta_tsk(id, 0);

	tk_def_int(3, &pk_dint);
	out_w(0x10013000+0x10, 2);
	EnableInt(3, 7);

	tk_ext_tsk();

	return 0;
}
