/*
 * sbrk.c
 *
 *  Created on: Oct 23, 2023
 *      Author: lbogdanov
 */
#include <errno.h>
#include <stdio.h>

extern int errno;

caddr_t sbrk(int incr){
	static char *heap_end = 0;
	char *prev_heap_end;
	extern char _heap_start; /* Defined by the linker */
	char *stack_pointer;

	asm("add %0, r0, r1\n" : "=r" (stack_pointer));

	if (heap_end == 0) {
		heap_end = &_heap_start;
	}

	prev_heap_end = heap_end;

	if (heap_end + incr > stack_pointer) {
		/* Heap and stack collision */
		errno = ENOMEM;
		return (caddr_t) -1;
	}

	heap_end += incr;

	return (caddr_t) prev_heap_end;
}

