// Import Libs
#include <xinu.h>

// Define Process
void do_shandler() {
	// Get Mask
	intmask mask = disable();
	
	// Enable Interrupts
	restore(mask);

	// Get Process
	struct procent* prptr = &proctab[currpid];

	// SIGRECV
	if(prptr->sigs[0] == SIGRECV) {
		// Move Signals
		prptr->sigs[0] = prptr->sigs[1];
		prptr->sigs[1] = -1;
		
		// Run Call Back
		restore(mask);
		prptr->prsig[SIGRECV].fnt();
		mask = disable();	
	}

	// SIGTIME
	if(prptr->sigs[0] == SIGTIME) {
		// Move Signals
		prptr->sigs[0] = prptr->sigs[1];
		prptr->sigs[1] = -1;	

		// Run Call Back
		restore(mask);
		prptr->prsig[SIGTIME].fnt();
		mask = disable();	
	}

	// SIGRECV for Different Order
	if(prptr->sigs[0] == SIGRECV) {
		// Move Signals
		prptr->sigs[0] = prptr->sigs[1];
		prptr->sigs[1] = -1;
		
		// Run Call Back
		restore(mask);
		prptr->prsig[SIGRECV].fnt();
		mask = disable();	
	}

	// Disable Interrupts
	disable();

	// Fix Return
	uint32* bp;
	__asm__("movl %%ebp, %0;"
		: "=r"	(bp)
	);
	uint32* ret_add = bp+1;
	*ret_add = prptr->prretadd;
	
	// Return
	return;
}
