/*
 *	dbgspt_depend.h
 *
 *	micro T-Kernel Debugger Support  Definition (RISC-V 32 core depended)
 */

#ifndef __TK_DBGSPT_DEPEND_CORE_H__
#define __TK_DBGSPT_DEPEND_CORE_H__

/*
 * System call/extension SVC caller information
 */
#if 0
typedef struct td_calinf {
	void	*sp;		/* stack pointer when calling */
	void	*pc;		/* program counter when calling */
} TD_CALINF;
#endif

#endif /* __TK_DBGSPT_DEPEND_CORE_H__ */
