#include <xinu.h>

// Returns the CPU Gross Time of a Proccess
syscall getuptime() {
	// Disabe Interrupts
	intmask mask = disable();

	// Get Current Process
	struct procent *prptr = &proctab[currpid];

	// No Proc
	if(prptr->prstate == PR_FREE) {
		restore(mask);
		return SYSERR;
	}

	// Return Usage Time
	uint32 time = prptr->pgrosscpu;
	restore(mask);
	return time;
}
