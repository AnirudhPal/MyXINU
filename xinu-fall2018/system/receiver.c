// Import Libs
#include <xinu.h>

// Global Var
volatile umsg32 msgbuf = 0;

// Define Callback
void myrcv() {
	// Get Message
	msgbuf = receive();

	// Print Message
	intmask mask = disable();
	kprintf("PID: %d Receiver CallBack (CALLBACK) <- %d @ %dms\n", currpid, msgbuf, clktimemilli); 	
	restore(mask);

	// Return
	return;
}

// Define Process
void receiver() {
	// Register Callback
	if (reghandler(&myrcv) != OK) {
		kprintf("recv handler registration failed\n");
		return;
	}

	// Infinite Loop
	while(TRUE) {
		// Print Message
		intmask mask = disable();
		kprintf("PID: %d Receiver (CALLBACK) <- %d @ %dms\n", currpid, msgbuf, clktimemilli); 
		restore(mask);
	}
}
