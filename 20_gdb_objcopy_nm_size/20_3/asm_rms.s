
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
	fmul	r5,r5,r5
	fmul	r6,r6,r6
	fmul	r7,r7,r7
	fmul	r8,r8,r8
	fadd	r9,r5,r6
	fadd	r9,r9,r7
	fadd	r9,r9,r8
	lwi	r10,r0,divider
	fdiv	r9,r10,r9
	fsqrt	r9,r9
	add	r3,r0,r9
	rtsd 	r15,8 		/*Return to main*/
	

