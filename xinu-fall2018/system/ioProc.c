#include <xinu.h>

// I/O Like Process
void ioProc(int loop, int delay) {
	// I/O Work
	int i;
	for(i = 0; i < loop; i++)
		sleepms(delay);

	// Print (Mutual Exclusion)
	intmask mask = disable();
	kprintf("I/O Done\n");
	kprintf("CLKTIMEMILLI: %d ms\n", clktimemilli);
	kprintf("CPU Gross Time: %d ms \n", getuptime());
	restore(mask);
}
