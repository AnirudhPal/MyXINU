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
	kprintf("Old CR0: 0x%x\n", oldValStage);
	newValStage = oldValStage | 0x80000000;
	kprintf("New CR0: 0x%x\n", newValStage);

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
syscall setPDBR(unsigned long add) {
	// Disable Interrupts
	intmask mask;
  	mask = disable();

	// Get CR3 
	asm("pushl %eax;"
	    "movl %cr3, %eax;"
	    "movl %eax, oldValStage;"
	    "popl %eax;");

	// Mask Value
	kprintf("Add: 0x%x\n", add);
	kprintf("Old CR3: 0x%x\n", oldValStage);
	newValStage = add << 12;
	kprintf("New CR3: 0x%x\n", newValStage);

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
