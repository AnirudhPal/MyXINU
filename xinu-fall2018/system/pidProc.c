#include <xinu.h>

// Prints PID from different places - pal5, Sep25
void pidProc() {
	// Print (Mutual Exclusion)
	intmask mask = disable();
	kprintf("currpid: %d, ", currpid);
	kprintf("getpid(): %d, ", getpid());
	kprintf("igetpid(): %d \n", igetpid());
	restore(mask);
}
