// Import Libs
#include <xinu.h>

// Global Var
volatile umsg32 msgbuf2 = 0;

// Define Callback
void myrcv2() {
	// Get Message
	msgbuf2 = receive();

	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, Msg: %d, Time: %dms, From Callback\n", currpid, msgbuf2, clktimemilli); 	
	restore(mask);
}

// Define Process
void receiver2() {
	// Register Callback
	if (reghandler(&myrcv2) != OK) {
		kprintf("recv handler registration failed\n");
		return;
	}

	// Infinite Loop
	while(TRUE) {
		// Print Message
		intmask mask = disable();
		kprintf("PID: %d, Msg: %d, Time: %dms, From Callback\n", currpid, msgbuf2, clktimemilli); 	
		restore(mask);
	}
}
