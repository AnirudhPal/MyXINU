#include <xinu.h>

// CPU Like Process
void cpuProc(int loop, int work, int id) {
	// CPU Work
	int i, j;
	for(i = 0; i < loop; i++)
		for(j = 0; j < work; j++);

	// Print (Mutual Exclusion)
	intmask mask = disable();
	kprintf("CPU Done %d\n", id);
	kprintf("CLKTIMEMILLI: %d ms\n", clktimemilli);
	kprintf("CPU Gross Time: %d ms \n", getuptime());
	kprintf("CPU Wait Time: %d\n", getdowntime());
	kprintf("CPU Wait Count: %d\n", getdowncount());
	restore(mask);
}
