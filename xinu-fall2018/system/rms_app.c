#include <xinu.h>
#define L1	10

void rms_app(uint32 x, uint32 y) {
	uint32 period_start, grosscpu_start, comp_received;
	int i;
	// Outer Loop
	for (i=0; i<L1; i++) {
		// Set Period Start
		period_start = clktimemilli;

		// Set CPU Usage Start
		grosscpu_start = getuptime();

		// CPU Time Recieved
		comp_received = 0;

		// Inner Loop 
		while(TRUE) {
			// Store Compute Time
			comp_received = getuptime() - grosscpu_start;
			// Break Condition
			if((clktimemilli - period_start < y) && (comp_received >= x))
				break;

			// Terminate Condition
			if(clktimemilli - period_start > y) {
				intmask mask = disable();
				kprintf("PID: %d, deadline violation\n", currpid);
				restore(mask);
				return;
			} 
		}

		// Print Before Sleep
		intmask mask = disable();
		kprintf("PID: %d, ", currpid);
		kprintf("x: %d, ", x);
		kprintf("y: %d, ", y);
		kprintf("Period Number: %d, ", i);
		kprintf("Remaining Period: %d\n", y - (clktimemilli - period_start));	
		restore(mask);

		// Sleep for Rest of the Period
		sleepms(y - (clktimemilli - period_start));
	}
	// Print PID, proctype, clktimemilli, gross CPU usage, and average time before terminating.
	intmask mask = disable();
	kprintf("PID: %d, ", currpid);
	kprintf("CLKTIMEMILLI: %dms, ", clktimemilli);
	kprintf("CPU Gross Time: %dms, ", getuptime());
	kprintf("CPU Wait Time: %dms, ", getdowntime());
	kprintf("CPU Wait Count: %d, ", getdowncount());
	kprintf("CPU Avg Wait Time: %dms, ", getdowntime()/getdowncount());
	kprintf("Prio: %u\n", (uint16)proctab[currpid].prprio);
	restore(mask);
}
