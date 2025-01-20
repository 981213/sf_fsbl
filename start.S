#include <asm/csr.h>

.section .text
.globl _start
_start:
	add 	s1, a0, zero
	add 	s2, a1, zero
	add 	s3, a2, zero

	lla	a0, __data_start__
	lla	a1, __data_end__
	bgeu	a0, a1, 2f
	lla	a2, __erodata
1:	ldia	t0, (a2), 8, 0
	sdia	t0, (a0), 8, 0
	bltu	a0, a1, 1b
2:

	lla	a0, __bss_start__
	lla	a1, __bss_end__
	bgeu	a0, a1, 2f
1:	sdia	zero, (a0), 8, 0
	bltu	a0, a1, 1b
2:
	csrwi	msmpr, 1
	li	t0, (1 << 13)
	csrs	mstatus, t0

	lla	sp, __stack
	add 	a0, s2, zero
	call	main
loop:
	j	loop