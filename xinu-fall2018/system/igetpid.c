#include <xinu.h>

// Trap Get PID - pal5, Sep 26
int igetpid(void) {
	// Save Regs
	__asm__("pushal;");

	// Interrupt and Get Value
	int ret;
	int id = 3;
	__asm__("int $33;"
		: "=a"	(ret)
		: "a"	(id)
	);

	// Restore Regs
	__asm__("popal;");

	// Get Return Value
	return ret;
}
