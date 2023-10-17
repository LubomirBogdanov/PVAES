
.text

.global asm_rms

divider: .float 4.00

	/*r5 - first (leftmost) parameter*/
	/*r6 - second parameter*/
	/*r7 - third parameter*/
	/*r8 - fourth (rightmost) parameter*/
	/*r3 - return value*/
	/*r0 - always zero*/

asm_rms:
	...Place assembly for calculating the square of the first parameter...
	...Place assembly for calculating the square of the second parameter...
	...Place assembly for calculating the square of the third parameter...
	...Place assembly for calculating the square of the fourth parameter...
	...Place assembly for calculating the sum of all the registers r5 through r8...
	lwi	r10,r0,divider
	fdiv	r9,r10,r9
	fsqrt	r9,r9
	add	r3,r0,r9
	rtsd 	r15,8 		/*Return to main*/
	

