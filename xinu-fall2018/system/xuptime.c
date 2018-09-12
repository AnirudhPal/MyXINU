#include <xinu.h>

syscall xuptime(xminsec_t * p) {
	// Disabe Interrupts
	intmask mask = disable();

	// Return Error
	if(p == NULL) {
		restore(mask);
		return SYSERR;
	}

	// Get CLKTIME
	uint32 secs = clktime;

	// Assign Mins
	p->upmin = 0;
	while(secs >= 60) {
		secs -= 60;
		p->upmin += 1;
	}

	// Assign Secs
	p->upsec = secs;

	// Return True
	restore(mask);
	return 1;
}
