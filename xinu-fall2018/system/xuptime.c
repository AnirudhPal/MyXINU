#include <xinu.h>

syscall xuptime(xminsec_t * p) {
	// Disabe Interrupts
	intmask mask = disable();

	// Return Error
	if(p == NULL) {
		restore(mask);
		return SYSERR;
	}

	// Assign Secs
	p->upsec = clktime;

	// Assign Mins
	uint32 secs = clktime;
	while(secs >= 60) {
		secs -= 60;
		p->upmin += 1;
	}

	// Return True
	restore(mask);
	return 1;
}
