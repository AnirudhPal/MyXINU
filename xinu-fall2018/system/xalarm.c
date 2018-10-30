// Import Libs
#include <xinu.h>

// Define Macro
#define	MAXSECONDS	2147483		/* Max seconds per 32-bit msec	*/

// SysCall
syscall	xalarm(int32 time) {
	// Interrupt Mask
	intmask	mask;

	// Handle Error			
	if (time < clktimemilli) {
		return SYSERR;
	}

	// Delay
	int32 delay = time - clktimemilli;

	// Disable Intterupts
	mask = disable();


	// Insert to Delta Queue
	if (insertda(currpid + (NPROC / 2), alarmq, delay) == SYSERR) {
		restore(mask);
		return SYSERR;
	}


	// Restore Interrupts and Return
	restore(mask);
	return OK;
}
