// Import Libs
#include <xinu.h>

// Global Var
extern umsg32 msgbufsigslp = 0;

// Define Callback
int myrcvsigslp() {
	// Get Message
	msgbufsigslp = receive();

	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Msg: %d, Time: %dms, From Callback\n", currpid, proctab[currpid].prname,msgbufsigslp, clktimemilli); 	
	restore(mask);

	// Return
	return OK;
}

// Define Process
void receiversigslp() {
	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Time: %dms, Starting Proc\n", currpid, proctab[currpid].prname, clktimemilli); 	
	restore(mask);

	// Register Callback
	if (signalreg(SIGRECV, &myrcvsigslp, 0) != OK) {
		kprintf("handler registration failed\n");
		return;
	}

	// Infinite Loop
	while(TRUE) {
		sleep(1);
	}
}
