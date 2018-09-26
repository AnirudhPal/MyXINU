#include <xinu.h>

// I/O Like Process
void ioProc(int loop, int delay, int id) {
	// I/O Work
	int i;
	for(i = 0; i < loop; i++)
		sleepms(delay);

	// Print (Mutual Exclusion)
	intmask mask = disable();
	kprintf("I/O Done %d\n", id);
	kprintf("CLKTIMEMILLI: %d ms\n", clktimemilli);
	kprintf("CPU Gross Time: %d ms \n", getuptime());
	kprintf("CPU Wait Time: %d ms \n", getdowntime());
	kprintf("CPU Wait Count: %d\n", getdowncount());
	restore(mask);
}
