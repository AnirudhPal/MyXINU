// Import Libs
#include <xinu.h>

// Global Var
extern umsg32 msgbufslp = 0;

// Define Callback
void myrcvslp() {
	// Get Message
	msgbufslp = receive();

	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Msg: %d, Time: %dms, From Callback\n", currpid, proctab[currpid].prname, msgbufslp, clktimemilli); 	
	restore(mask);
}

// Define Process
void receiverslp() {
	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Time: %dms, Starting Proc\n", currpid, proctab[currpid].prname, clktimemilli); 	
	restore(mask);

	// Register Callback
	if (reghandler(&myrcvslp) != OK) {
		kprintf("recv handler registration failed\n");
		return;
	}

	// Infinite Loop
	while(TRUE) {
		sleep(1);
	}
}
