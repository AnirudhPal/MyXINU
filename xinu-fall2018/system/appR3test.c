#include <xinu.h>

void appR3test(int proctype) {
	int i, j;
	for (i=0; i<LOOP1; i++) { // Affects overall run-time of app.
		for (j=0; j<LOOP2; j++) {
			// LOOP2 dictates CPU cycles consumed by the inner loop.
			int a = 10;
			a = a - 10;
		}
		if(proctype == 1) // I/O-bound process: IOSLEEP determines blocking to computation ratio.
			sleepms(IOSLEEP);
	}
	// Print PID, proctype, clktimemilli, gross CPU usage, and average time before terminating.
	intmask mask = disable();
	kprintf("PID: %d, ", currpid);
	kprintf("proctype: %d, ", proctype);
	kprintf("CLKTIMEMILLI: %dms, ", clktimemilli);
	kprintf("CPU Gross Time: %dms, ", getuptime());
	kprintf("CPU Wait Time: %dms, ", getdowntime());
	kprintf("CPU Wait Count: %d, ", getdowncount());
	kprintf("CPU Avg Wait Time: %dms, ", getdowntime()/getdowncount());
	kprintf("pvirtcpu: %dms, ", proctab[currpid].prprio);
	kprintf("Prio: %d\n", proctab[currpid].prprio);
	restore(mask);
}
