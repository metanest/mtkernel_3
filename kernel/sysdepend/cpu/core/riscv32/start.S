#include <sys/machine.h>
#define _in_asm_source_
#include <sys/sysdef.h>

	.section .start,"ax",@progbits
	.option norelax
	.global start
start:
	la gp, __global_pointer$
	li sp, INITIAL_SP
	j Csym(reset_main)
