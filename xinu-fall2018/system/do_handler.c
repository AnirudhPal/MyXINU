// Import Libs
#include <xinu.h>

// Define Process
void do_handler() {
	// Get Mask
	intmask mask = disable();
	
	// Enable Interrupts
	restore(mask);

	// Run Callback
	proctab[currpid].funcptr();

	// Fix Return
	uint32* bp;
	__asm__("movl %%ebp, %0;"
		: "=r"	(bp)
	);
	uint32* ret_add = bp+1;
	*ret_add = proctab[currpid].prretadd;

	// Disable Interrupts
	disable();

	// Return
	return;
}
