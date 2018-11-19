// Import Libs
#include<xinu.h>

// Proc
void test1P() {
	// Print
	intmask mask = disable();
	kprintf("PID: %d -> Using 1 Page\n", currpid);
	restore(mask);

	int i;
	unsigned long* ptr = (unsigned long*)vgetmem(NBPG);
	for(i=0; i < NBPG / 4; i++) {
		*(ptr + i) = 0x123ABCEF;
	}
	for(i=0; i < NBPG / 4; i++) {
		if(*(ptr + i) != 0x123ABCEF) {
			// Print
			mask = disable();
			kprintf("PID: %d -> Something is Wrong Val: 0x%x\n", currpid, *(ptr + i));
			restore(mask);
		}
	}

	// Print
	mask = disable();
	kprintf("PID: %d -> Used 1 Page, First Add: 0x%x, First Val: 0x%x\n", currpid, ptr, *(ptr));
	restore(mask);
}

// Proc
void test2072P() {
	// Print
	intmask mask = disable();
	kprintf("PID: %d -> Using All Pages\n", currpid);
	restore(mask);

	int i;
	unsigned long* ptr = (unsigned long*)vgetmem(2072 * NBPG);
	for(i=0; i < (2072 * NBPG) / 4; i++) {
		*(ptr + i) = 0x123ABCEF;
	}
	for(i=0; i < (2072 * NBPG) / 4; i++) {
		if(*(ptr + i) != 0x123ABCEF) {
			// Print
			mask = disable();
			kprintf("PID: %d -> Something is Wrong Val: 0x%x\n", currpid, *(ptr + i));
			restore(mask);
		}
	}

	// Print
	mask = disable();
	kprintf("PID: %d -> Used All Pages, First Add: 0x%x, First Val: 0x%x\n", currpid, ptr, *(ptr));
	restore(mask);
}

// Proc
void test2072PGF() {
	// Print
	intmask mask = disable();
	kprintf("PID: %d -> Using All Pages and vgetmem() and freemem()\n", currpid);
	restore(mask);

	// Print
	kprintf("Iteration: ");

	int j;
	for(j = 0; j < 100; j++) {
		int i;
		unsigned long* ptr = (unsigned long*)vgetmem(2072 * NBPG);
		for(i=0; i < (2072 * NBPG) / 4; i++) {
			*(ptr + i) = 0x123ABCEF;
		}
		for(i=0; i < (2072 * NBPG) / 4; i++) {
			if(*(ptr + i) != 0x123ABCEF) {
				// Print
				mask = disable();
				kprintf("PID: %d -> Something is Wrong Val: 0x%x\n", currpid, *(ptr + i));
				restore(mask);
			}
		}
		kprintf("%d", j);
		if(j < 10)
			kprintf("\b");
		else
			kprintf("\b\b");
		vfreemem((char*)ptr, 2072 * NBPG);
	}

	// Print
	mask = disable();
	kprintf("\nPID: %d -> Done Using Heap\n", currpid);
	restore(mask);
}

// Proc
void test2P() {
	// Print
	intmask mask = disable();
	kprintf("PID: %d -> Using 2 Pages\n", currpid);
	restore(mask);

	char* ptr = vgetmem(2 * NBPG);

	// Print
	if(ptr == (char*)SYSERR) {
		mask = disable();
		kprintf("PID: %d -> Heap not Big Enough!\n", currpid, ptr, *(ptr));
		restore(mask);
		return;
	}	

	// Print
	mask = disable();
	kprintf("PID: %d -> This shouldnt print.\n", currpid);
	restore(mask);
}

// Proc
void test1A() {
	// Print
	intmask mask = disable();
	kprintf("PID: %d -> Using 1 Byte\n", currpid);
	restore(mask);

	char* ptr = (char*)vgetmem(1);
	*ptr = 'A';

	// Print
	mask = disable();
	kprintf("PID: %d -> Used 1 Byte, First Add: 0x%x, First Val: %c\n", currpid, ptr, *(ptr));
	restore(mask);

	while(TRUE) {
		if(*ptr != 'A') {
			// Print
			mask = disable();
			kprintf("PID: %d -> Something is Wrong Val: %c\n", currpid, *(ptr));
			restore(mask);
		}
	}
}

// Proc
void test1B() {
	// Print
	intmask mask = disable();
	kprintf("PID: %d -> Using 1 Byte\n", currpid);
	restore(mask);

	char* ptr = (char*)vgetmem(1);
	*ptr = 'B';

	// Print
	mask = disable();
	kprintf("PID: %d -> Used 1 Byte, First Add: 0x%x, First Val: %c\n", currpid, ptr, *(ptr));
	restore(mask);

	while(TRUE) {
		if(*ptr != 'B') {
			// Print
			mask = disable();
			kprintf("PID: %d -> Something is Wrong Val: %c\n", currpid, *(ptr));
			restore(mask);
		}
	}
}
