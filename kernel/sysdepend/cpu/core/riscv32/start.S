#include <sys/machine.h>

	.section .start,"ax",@progbits
	.option norelax
	.global start
start:
	la gp, __global_pointer$
	li sp, 0x80004000  /* INITIAL_SP */ //XXX
	j Csym(reset_main)
