// Import Libs
#include <xinu.h>

// Global Var
extern umsg32 msgbuf = 0;

// Define Callback
void myrcv() {
	// Get Message
	msgbuf = receive();

	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Msg: %d, Time: %dms, From Callback\n", currpid, proctab[currpid].prname,msgbuf, clktimemilli); 	
	restore(mask);
}

// Define Process
void receiver() {
	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Time: %dms, Starting Proc\n", currpid, proctab[currpid].prname, clktimemilli); 	
	restore(mask);

	// Register Callback
	if (reghandler(&myrcv) != OK) {
		kprintf("recv handler registration failed\n");
		return;
	}

	// Infinite Loop
	while(TRUE) {
	}
}
