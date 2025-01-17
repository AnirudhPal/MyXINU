// Import Libs
#include <xinu.h>

// Define System Call
syscall	reghandler(void(*func) (void)) {
	// Local Vars
	intmask	mask;			
	struct	procent *rprptr;

	// Disable Interrupts
	mask = disable();

	// Get Process Entry
	rprptr = &proctab[currpid];

	// If Already Set or NULL Pointer
	if(rprptr->funcptr != NULL || func == NULL) {
		// Enable Interrupts
		restore(mask);

		// Return
		return SYSERR;
	}

	// Set Function Pointer
	rprptr->funcptr = func;

	// Enable Interrupts
	restore(mask);

	// Return
	return OK;
}

