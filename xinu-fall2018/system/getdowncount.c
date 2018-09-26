#include <xinu.h>

// Returns the CPU Wait Count of a Proccess
syscall getdowncount() {
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
	uint32 count = prptr->pwaitcount;
	restore(mask);
	return count;
}
