// Import Libs
#include <xinu.h>

// Define Callback
int myrcvalm() {
	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Time: %dms, CPU: %dms From Callback\n", currpid, proctab[currpid].prname, clktimemilli, getuptime()); 	
	restore(mask);

	// Return
	return OK;
}

// Define Process
void receiveralm() {
	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Time: %dms, CPU: %dms Starting Proc\n", currpid, proctab[currpid].prname, clktimemilli, getuptime()); 	
	restore(mask);

	// Register Callback
	if (signalreg(SIGTIME, &myrcvalm, 0) != OK) {
		kprintf("handler registration failed\n");
		return;
	}

	// Set Alarm
	xalarm(clktimemilli + 500);

	// Infinite Loop
	while(TRUE) {
	}
}
