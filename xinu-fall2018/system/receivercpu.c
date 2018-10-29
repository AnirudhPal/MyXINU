// Import Libs
#include <xinu.h>

// Define Callback
int myrcvcpu() {
	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Time: %dms, CPU: %dms From Callback\n", currpid, proctab[currpid].prname, clktimemilli, getuptime()); 	
	restore(mask);

	// Return
	return OK;
}

// Define Process
void receivercpu() {
	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Time: %dms, CPU: %dms Starting Proc\n", currpid, proctab[currpid].prname, clktimemilli, getuptime()); 	
	restore(mask);

	// Register Callback
	if (signalreg(SIGXCPU, &myrcvcpu, 500) != OK) {
		kprintf("handler registration failed\n");
		return;
	}

	// Infinite Loop
	while(TRUE) {
	}
}
