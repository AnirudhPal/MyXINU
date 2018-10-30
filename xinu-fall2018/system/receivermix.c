// Import Libs
#include <xinu.h>

// Global Var
extern umsg32 msgbufmix = 0;

// Define Callback
int myrcvmix() {
	// Get Message
	msgbufmix = receive();

	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Msg: %d, Time: %dms, From Callback for SIGRECV\n", currpid, proctab[currpid].prname,msgbufmix, clktimemilli); 	
	restore(mask);

	// Return
	return OK;
}

int mycpu() {
	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Time: %dms, CPU: %dms From Callback for SIGXCPU\n", currpid, proctab[currpid].prname, clktimemilli, getuptime()); 	
	restore(mask);

	// Return
	return OK;
}

int myalm() {
	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Time: %dms, CPU: %dms From Callback for SIGTIME\n", currpid, proctab[currpid].prname, clktimemilli, getuptime()); 	
	restore(mask);

	// Return
	return OK;
}

// Define Process
void receivermix() {
	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Time: %dms, Starting Proc\n", currpid, proctab[currpid].prname, clktimemilli); 	
	restore(mask);

	// Register Callback
	if (signalreg(SIGRECV, &myrcvmix, 0) != OK) {
		kprintf("handler registration failed\n");
		return;
	}
	if (signalreg(SIGXCPU, &mycpu, 5) != OK) {
		kprintf("handler registration failed\n");
		return;
	}
	if (signalreg(SIGTIME, &myalm, 0) != OK) {
		kprintf("handler registration failed\n");
		return;
	}
	
	// Set Alarm
	xalarm(clktimemilli + 500);

	// Infinite Loop
	while(TRUE) {
		// Loop
		int i;
		for(i = 0; i < 1000000; i++) {

		}

		// Sleep
		sleep(1);
	}
}
