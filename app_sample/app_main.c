#include <tk/tkernel.h>
#include <tm/tmonitor.h>

#include "../device/include/dev_ser.h"
#include "../device/ser/ser_cnf.h"

#define SER_MAX_UNIT	2

typedef struct {
	UINT	no;
	UW	data;
} T_ATR_DATA;

T_ATR_DATA iatr_tbl[] = {
	{TDN_EVENT, 0},
	{TDN_SER_MODE, DEVCNF_SER_MODE},
	{TDN_SER_SPEED, DEVCNF_SER_SPEED},
	{TDN_SER_SNDTMO, DEVCNF_SER_SND_TMO},
	{TDN_SER_RCVTMO, DEVCNF_SER_RCV_TMO},
	{0,0}
};

T_ATR_DATA rwatr_tbl[] = {
	{TDN_EVENT, 1},
	{TDN_SER_MODE, DEV_SER_MODE_7BIT | DEV_SER_MODE_2STOP | DEV_SER_MODE_PEVEN},
	{TDN_SER_SPEED, 9600},
	{TDN_SER_SNDTMO, 5000},
	{TDN_SER_RCVTMO, 5000},
	{0,0}	
};

LOCAL void read_atr(ID dd, T_ATR_DATA *p_tbl)
{
	UW	data;
	SZ	asize;
	ER	err;

	while(p_tbl->no != 0) {
		err = tk_srea_dev(dd, p_tbl->no, &data, sizeof(data), &asize);
		if(err < E_OK || asize != sizeof(UW) || data != p_tbl->data) {
			tm_printf((UB*)"!!ERR Read Atr no %d  ercd %d  asize %d  data %d\n", p_tbl->no, err, asize, data);
			return;
		}
		p_tbl++;
	}
	tm_printf((UB*)"ATR Read Test OK\n");
}

LOCAL void write_atr(D dd, T_ATR_DATA *p_tbl)
{
	UW	data;
	SZ	asize;
	ER	err;

	while(p_tbl->no != 0) {
		data = p_tbl->data;
		err = tk_swri_dev(dd, p_tbl->no, &data, sizeof(UW), &asize);
		if(err < E_OK || asize != sizeof(UW)) {
			tm_printf((UB*)"!!ERR Write Atr no %d  ercd %d  asize %d\n", p_tbl->no, err, asize);
			return;
		}
		p_tbl++;
	}
	tm_printf((UB*)"ATR Write test OK\n");
}

const char str1[] = "0123456789 0123456789 0123456789 0123456789 0123456789\n\r";
const char str2[] = "abcdefg hijklmn opqrstu vwxyz\n\r";

LOCAL void com_test(ID dd)
{
	SZ	asize;
	UB	data;
	ER	err;

	tk_swri_dev(dd, 0, str1, sizeof(str1), &asize);
	for(INT i = 0; i < sizeof(str2)-1; i++) {
		tk_swri_dev(dd, 0, &str2[i], 1, &asize);
	}
	tk_dly_tsk(100);

	while(1) {
		err = tk_srea_dev(dd, 0, &data, sizeof(data), &asize);
		if(err < E_OK || asize != sizeof(data)) {
			tm_printf((UB*)"##ERR send char err %d asize %d\n", err, asize);
			break;
		}
		err = tk_swri_dev(dd, 0, &data, sizeof(data), &asize);
		if(err < E_OK || asize != sizeof(data)) {
			tm_printf((UB*)"##ERR send char err %d asize %d\n", err, asize);
			break;
		}

		if(data == '\r') break;
	}

}

EXPORT ER test_ser(UINT	unitno)
{
	
	ID	dd;
	ER	err;

	UB	devnm[] = "ser ";

	tm_printf((UB*)"==== SER Unit %d TEST\n", unitno);
	
	if(unitno != 4) {
		err = dev_init_ser(unitno);
		if(err < E_OK) {
			tm_printf((UB*)"!!ERR Init-%d err %d\n", unitno, err);
			return err;
		}
	}

	devnm[3] = 'a'+unitno;
	err = tk_opn_dev(devnm, TD_UPDATE);
	if(err < E_OK) {
		tm_printf((UB*)"!!ERR Open-%d err %d\n", unitno, err);
		return err;
	}
	dd = (ID)err;

	read_atr(dd, iatr_tbl);
	write_atr(dd, rwatr_tbl);
	read_atr(dd, rwatr_tbl);

	err = tk_cls_dev(dd, 0);
	if(err < E_OK) {
		tm_printf((UB*)"!!ERR Close-%d err %d\n", unitno, err);
		return err;
	}
	tm_printf((UB*)"==== Unit %d End\n", unitno);

	tm_printf((UB*)"==== SER Unit %d TEST\n", unitno);
	
	err = dev_init_ser(unitno);
	devnm[3] = 'a'+unitno;
	err = tk_opn_dev(devnm, TD_UPDATE);
	dd = (ID)err;

	com_test(dd);

	tm_printf((UB*)"==== Unit %d End\n", unitno);
	err = tk_cls_dev(dd, 0);
	return err;
}

EXPORT INT usermain(void)
{
	ER	err;

	err = test_ser(4);
	tm_printf((UB*)"test end %d\n", err);
	return 0;
}