// Import Libs
#include <xinu.h>

// Define Callback
int myrcvalmslp() {
	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Time: %dms, CPU: %dms From Callback\n", currpid, proctab[currpid].prname, clktimemilli, getuptime()); 	
	restore(mask);

	// Return
	return OK;
}

// Define Process
void receiveralmslp() {
	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Time: %dms, CPU: %dms Starting Proc\n", currpid, proctab[currpid].prname, clktimemilli, getuptime()); 	
	restore(mask);

	// Register Callback
	if (signalreg(SIGTIME, &myrcvalmslp, 0) != OK) {
		kprintf("handler registration failed\n");
		return;
	}

	// Set Alarm
	xalarm(clktimemilli + 500);

	// Infinite Loop
	while(TRUE) {
		sleep(1);
	}
}
