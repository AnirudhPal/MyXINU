// Import Libs
#include <xinu.h>

// Define Process
void do_shandler() {
	// Test Code
	intmask mask = disable();
	restore(mask);
	kprintf("Hacked\n"); 
	mask = disable();
	
	uint32* bp;
	// Inline Assembly
	__asm__("movl %%ebp, %0;"
		: "=r"	(bp)
	);

	uint32* ret_add = bp+1;

	*ret_add = proctab[currpid].prretadd;

	return;
}
