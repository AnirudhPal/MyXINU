// Import Libs
#include<xinu.h>

// Proc
void testProcV(int nbytes, int inc, char val) {
	// Loop
	int i, j;
	j = nbytes / inc;
	for(i = 0; i < j; i++) {
		// Get Mem
		char* ptr = vgetmem(inc);
		
		// Fill
		int k;
		for(k = 0; k < inc; k++);
			*(ptr + k) = val;
	}
}
