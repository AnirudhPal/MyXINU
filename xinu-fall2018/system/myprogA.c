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

	// Call Function
	myfuncA(456);

	// Print Top of Stack
	kprintf("After myfuncA() returns.\n");
	__asm__("movl %%esp, %%ebx;"
		: "=b" (rsp)
	);
	kprintf("Address: 0x%08X, Value: 0x%08X\n", (uint32)rsp, (uint32)*rsp);

	// Return Int
	return 123;
}

char myfuncA(int x) {
	// Get Stack Pointer
	char * rsp;
	__asm__("movl %%esp, %%ebx;"
		: "=b" (rsp)
	);

	// Print Details
	kprintf("Stack Base: 0x%08X, Stack Size: %d, Stack Limit: 0x%08X, Stack Pointer: 0x%08X, PID: %d, Parent PID: %d\n", proctab[currpid].prstkbase, proctab[currpid].prstklen, (uint32)proctab[currpid].prstkbase - (proctab[currpid].prstklen), (uint32)rsp, currpid, getppid());

	// Return Char
	return 'D';
}
