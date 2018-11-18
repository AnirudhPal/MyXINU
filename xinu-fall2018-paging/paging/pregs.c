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
	//kprintf("Old CR0: 0x%x\n", oldValStage);
	newValStage = oldValStage | 0x80000000;
	//kprintf("New CR0: 0x%x\n", newValStage);

	// Set CR0
	asm("pushl %eax;"
	    "movl newValStage, %eax;"
	    "movl %eax, %cr0;"
	    "popl %eax;");

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

	// Get CR3 
	asm("pushl %eax;"
	    "movl %cr3, %eax;"
	    "movl %eax, oldValStage;"
	    "popl %eax;");

	// Right Shift & Change
	//kprintf("Frame: %d\n", frameNum);
	//kprintf("Old CR3: 0x%x\n", oldValStage);
	newValStage = frameNum << 12;
	//kprintf("New CR3: 0x%x\n", newValStage);

	// Set CR3
	asm("pushl %eax;"
	    "movl newValStage, %eax;"
	    "movl %eax, %cr3;"
	    "popl %eax;");

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

	// Get CR3 
	asm("pushl %eax;"
	    "movl %cr2, %eax;"
	    "movl %eax, oldValStage;"
	    "popl %eax;");
	
	// Enable Interrupts
	restore(mask);

	// Return
	return oldValStage;
}
