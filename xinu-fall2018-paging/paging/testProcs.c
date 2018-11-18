// Import Libs
#include<xinu.h>

// Proc
void test1P() {
	int i;
	unsigned long* ptr = (unsigned long*)vgetmem(NBPG);
	for(i=0; i < NBPG / 4; i++) {
		*(ptr + i) = 0x123ABC;
	}
}

// Proc
void test2072P() {
	int i;
	unsigned long* ptr = (unsigned long*)vgetmem(2072 * NBPG);
	for(i=0; i < (2072 * NBPG) / 4; i++) {
		*(ptr + i) = 0x123ABC;
	}
}
