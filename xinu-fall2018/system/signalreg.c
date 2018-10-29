// Import Libs
#include <xinu.h>

// Define System Call
syscall	signalreg(uint16 nsig, int(*func) (void), uint32 oarg) {
	// Local Vars
	intmask	mask;			
	struct	procent *rprptr;

	// Disable Interrupts
	mask = disable();

	// Get Process Entry
	rprptr = &proctab[currpid];

	// If Invalid Signal or Pointer or Already Reg
	if(nsig < 0 || nsig >= SIGNUM || func == NULL || rprptr->prsig[nsig].regyes) {
		// Enable Interrupts
		restore(mask);

		// Return
		return SYSERR;
	}

	// Add Handler
	rprptr->prsig[nsig].regyes = TRUE;
	rprptr->prsig[nsig].fnt = func;
	rprptr->prsig[nsig].optarg = oarg;

	// Enable Interrupts
	restore(mask);

	// Return
	return OK;
}

