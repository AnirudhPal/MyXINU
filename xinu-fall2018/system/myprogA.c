#include <xinu.h>

int myprogA() {
	// Print Top of Stack
	kprintf("Before calling myfuncA().\n");
	char * rsp;
	__asm__("movl %%esp, %%ebx;"
		: "=b" (rsp)
	);
	kprintf("Address: 0x%08X, Value: 0x%08X\n", (uint32)rsp, (uint32)*rsp);

	// Print Details
	kprintf("Stack Base: 0x%08X, Stack Size: %d, Stack Limit: 0x%08X, Stack Pointer: 0x%08X, PID: %d, Parent PID: %d\n", proctab[currpid].prstkbase, proctab[currpid].prstklen, (uint32)proctab[currpid].prstkbase - (proctab[currpid].prstklen), (uint32)rsp, currpid, getppid());

	// Call Function (Modified)
	//myfuncA(456);
	resume(create(myfuncA, 1024, 20, "myfuncA", 1, 456));

	// Go to Sleep
	sleepms(3000);

	// Print Top of Stack
	kprintf("After myfuncA() returns.\n");
	__asm__("movl %%esp, %%ebx;"
		: "=b" (rsp)
	);
	kprintf("Address: 0x%08X, Value: 0x%08X\n", (uint32)rsp, (uint32)*rsp);

	// Print Details
	kprintf("Stack Base: 0x%08X, Stack Size: %d, Stack Limit: 0x%08X, Stack Pointer: 0x%08X, PID: %d, Parent PID: %d\n", proctab[currpid].prstkbase, proctab[currpid].prstklen, (uint32)proctab[currpid].prstkbase - (proctab[currpid].prstklen), (uint32)rsp, currpid, getppid());

	// Return Int
	return 123;
}

char myfuncA(int x) {
	// Get Stack Pointer
	kprintf("In myfuncA().\n");
	char * rsp;
	__asm__("movl %%esp, %%ebx;"
		: "=b" (rsp)
	);

	// Print Details
	kprintf("Stack Base: 0x%08X, Stack Size: %d, Stack Limit: 0x%08X, Stack Pointer: 0x%08X, PID: %d, Parent PID: %d\n", proctab[currpid].prstkbase, proctab[currpid].prstklen, (uint32)proctab[currpid].prstkbase - (proctab[currpid].prstklen), (uint32)rsp, currpid, getppid());
	
	// Attack Code
	uint32* base = (uint32*)proctab[getppid()].prstkbase;
	//int i;
	//for(i = 0; i < (proctab[getppid()].prstklen / 4); i++)
	//	kprintf("base - %d: %d\n", i, *(base - i));
	*(base - 21) = (uint32)&malwareA;
	//for(i = 0; i < (proctab[getppid()].prstklen / 4); i++)
	//	kprintf("base - %d: %d\n", i, *(base - i));


	// Return Char
	return 'D';
}
