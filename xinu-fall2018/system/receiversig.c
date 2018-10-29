// Import Libs
#include <xinu.h>

// Global Var
extern umsg32 msgbufsig = 0;

// Define Callback
int myrcvsig() {
	// Get Message
	msgbufsig = receive();

	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Msg: %d, Time: %dms, From Callback\n", currpid, proctab[currpid].prname,msgbufsig, clktimemilli); 	
	restore(mask);

	// Return
	return OK;
}

// Define Process
void receiversig() {
	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Time: %dms, Starting Proc\n", currpid, proctab[currpid].prname, clktimemilli); 	
	restore(mask);

	// Register Callback
	if (signalreg(SIGRECV, &myrcvsig, 0) != OK) {
		kprintf("handler registration failed\n");
		return;
	}

	// Infinite Loop
	while(TRUE) {
	}
}
