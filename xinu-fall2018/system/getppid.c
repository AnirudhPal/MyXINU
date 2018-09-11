#include <xinu.h>

syscall getppid() {
	// Disabe Interrupts
	intmask mask = disable();

	// Get Current Process
	struct procent *prptr = &proctab[currpid];

	// Get Parent Process
	struct procent *pprptr = &proctab[prptr->prparent];

	// No Parent
	if(pprptr->prstate == PR_FREE) {
		restore(mask);
		return SYSERR;
	}

	// Return Parent PID
	pid32 ppid = prptr->prparent;
	restore(mask);
	return ppid;
}
