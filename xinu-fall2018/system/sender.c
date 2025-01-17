// Import Libs
#include <xinu.h>

// Define Process
void sender(pid32 pid, umsg32 msg) {
	// Print Message
	intmask mask = disable();
	kprintf("PID: %d, PName: %s, Msg: %d, To PID: %d, Time: %dms, Start Sending\n", currpid, proctab[currpid].prname, msg, pid, clktimemilli); 	
	restore(mask);

	// Send Message
	send(pid, msg);
	/*
	int xyz;
	for(xyz = 8; xyz < 10; xyz++) {
		mask = disable();
	kprintf("at %d\n", xyz);
	send(pid, xyz);
	restore(mask);	
	}*/

	// Print Message
	mask = disable();
	kprintf("PID: %d, PName: %s, Msg: %d, To PID: %d, Time: %dms, Start Done\n", currpid, proctab[currpid].prname, msg, pid, clktimemilli); 	
	restore(mask);	 
}

