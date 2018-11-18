// Import Libs
#include <xinu.h>

// Staging Vars for Regs
unsigned long newValStage;
unsigned long oldValStage;

// Turn On Paging
syscall pagingOn() {
	// Disable Interrupts
	intmask mask;
  	mask = disable();

	// Get CR0 
	asm("pushl %eax;"
	    "movl %cr0, %eax;"
	    "movl %eax, oldValStage;"
	    "popl %eax;");

	// Mask Value
	newValStage = oldValStage | 0x80000000;

	// Set CR0
	asm("pushl %eax;"
	    "movl newValStage, %eax;"
	    "movl %eax, %cr0;"
	    "popl %eax;");

	// Test Print
	if(VERBOSE)
		kprintf("\npagingOn(): CR0 -> %u for PID %d\n", newValStage >> 31, currpid);

	// Enable Interrupts
	restore(mask);

	// Return
	return OK;
}

 
// Set PDBR
syscall setPDBR(unsigned long frameNum) {
	// Disable Interrupts
	intmask mask;
  	mask = disable();

	// Error Handeling
	if(frameNum < FRAME0 || frameNum > (FRAME0 + NFRAMES)) {
		// Enable Interrupts
		restore(mask);

		// Kill Proc
		kprintf("setPDBR(): Invalid PD %d for PID %d\nKilling Proc!! \n", frameNum, currpid);
		kill(currpid);

		// Return
		return SYSERR;
	}

	// Right Shift
	newValStage = frameNum << 12;

	// Set CR3
	asm("pushl %eax;"
	    "movl newValStage, %eax;"
	    "movl %eax, %cr3;"
	    "popl %eax;");

	// Test Print
	if(VERBOSE)
		kprintf("setPDBR(): CR3 -> %d for PID %d\n", newValStage >> 12, currpid);

	// Enable Interrupts
	restore(mask);

	// Return
	return OK;
}


// Get CR2
unsigned long getCR2() {
	// Disable Interrupts
	intmask mask;
  	mask = disable();

	// Get CR2 
	asm("pushl %eax;"
	    "movl %cr2, %eax;"
	    "movl %eax, oldValStage;"
	    "popl %eax;");

	// Test Print
	if(VERBOSE)
		kprintf("getCR2(): CR2 -> %d for PID %d\n", oldValStage >> 12, currpid);

	// Enable Interrupts
	restore(mask);

	// Return
	return oldValStage;
}
