// Import Libs
#include <xinu.h>

// System Call
syscall sendSignal(int pid, int sig) {
	// Disable Interrupts
	intmask mask = disable();

	// Validate Signal
	if(isbadpid(pid) || sig < 0 || sig >= SIGNUM) {
		restore(mask);
		return SYSERR;
	}

	// Get Proc
	struct procent* prptr = &proctab[pid];

	// Check if has Callback
	if(!prptr->prsig[sig].regyes) {
		restore(mask);
		return SYSERR;
	}
		
	// Handle SIGXCPU
	if(sig == SIGXCPU) {
		// Set Callback to No
		prptr->prsig[sig].regyes = FALSE;

		// Run Callback
		restore(mask);
		prptr->prsig[sig].fnt();
		mask = disable();

		// Return
		restore(mask);
		return OK;
	}

	// Handle Current SIGTIME
	if(sig == SIGTIME && currpid == pid) {
		// Run Callback
		restore(mask);
		prptr->prsig[sig].fnt();
		mask = disable();

		// Return
		restore(mask);
		return OK;
	}
	/**
	// Full
	if(prptr->sigs[2] != -1) {
		restore(mask);
		return SYSERR;
	}

	// Repeat
	if(prptr->sigs[0] == sig || prptr->sigs[1] == sig) {
		restore(mask);
		return SYSERR;
	}

	// Send Signal
	int i;
	for(i = 0; i < 3; i++)
		if(prptr->sigs[i] == -1) {
			prptr->sigs[i] = sig;
			break;
		}
	**/
	// Return
	restore(mask);
	return OK;
}

