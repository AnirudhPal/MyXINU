#include <xinu.h>

/* R3 Testing variables - pal5, Sep 26 */
#define	IOSLEEP		50
#define	LOOP1		300
#define	LOOP2		100000


void appR3test(int proctype) {
	int i, j;
	// Modified according to TA notes to give I/O Less CPU Usage
	for (i=0; i<LOOP1; i++) { // Affects overall run-time of app.
		if(proctype == 1) // I/O-bound process: IOSLEEP determines blocking to computation ratio.
			sleepms(IOSLEEP);
		else
			for (j=0; j<LOOP2; j++) {
				// LOOP2 dictates CPU cycles consumed by the inner loop.
				int a = 10;
				a = a - 10;
			}
			
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
	kprintf("pvirtcpu: %dms, ", proctab[currpid].pvirtcpu);
	kprintf("Prio: %u\n", (uint16)proctab[currpid].prprio);
	restore(mask);
}
