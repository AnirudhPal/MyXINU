#include <xinu.h>

// CPU Like Process
void cpuProc(int loop, int work) {
	// CPU Work
	int i, j;
	for(i = 0; i < loop; i++)
		for(j = 0; j < work; j++);

	// Print (Mutual Exclusion)
	intmask mask = disable();
	kprintf("CPU Done\n");
	kprintf("CLKTIMEMILLI: %d ms\n", clktimemilli);
	kprintf("CPU Gross Time: %d ms \n", getuptime());
	restore(mask);
}
