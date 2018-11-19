// Import Libs
#include<xinu.h>

// Create PD and get Frame
uint16 getPD() {
	// Disable Interrupts
	intmask mask = disable();

	// Get Frame (Return FRAME0 + i)
	uint16 frame = getDSFrame();

	// Error Handeling
	if(frame == SYSERR) {
		// Enable Interrupts
		restore(mask);

		// Error
		kprintf("getPD(): Invalid PD %d\n", frame);

		// Return
		return SYSERR;	
	}

	// Put PD at Frame
	pd_t* nullPD = (pd_t*)frametab[frame - FRAME0].loc;
	frametab[frame - FRAME0].type = PD_FRAME;
	frametab[frame - FRAME0].pid = currpid;

	// Set PDE Bits to 0
	int i;
	for(i = 0; i < FRAME_SIZE; i++) {
		nullPD[i].pd_pres = 0;	
		nullPD[i].pd_write = 1;
		nullPD[i].pd_user = 0;
		nullPD[i].pd_pwt = 0;
		nullPD[i].pd_pcd = 0;
		nullPD[i].pd_acc = 0;
		nullPD[i].pd_mbz = 0;
		nullPD[i].pd_fmb = 0;
		nullPD[i].pd_global = 0;
		nullPD[i].pd_avail = 0;
		nullPD[i].pd_base = 0;	
	}

	// Set 4 PDE
	for(i = 0; i < 4; i++) {
		nullPD[i].pd_pres = 1;	
		nullPD[i].pd_write = 1;
		nullPD[i].pd_base = FRAME0 + 1 + i;						}

	// Set Dev PDE
	nullPD[DEV_PDE].pd_pres = 1;	
	nullPD[DEV_PDE].pd_write = 1;
	nullPD[DEV_PDE].pd_base = FRAME0 + 5;

	// Test Print
	if(VERBOSE)
		kprintf("\ngetPD(): Frame -> %d\n", frame);

	// Return PD Frame
	restore(mask);
	return frame;
}

// Create PT and get Frame
uint16 getPT() {
	// Disable Interrupts
	intmask mask = disable();

	// Get Frame (Return FRAME0 + i)
	uint16 frame = getDSFrame();

	// Error Handeling
	if(frame == SYSERR) {
		// Enable Interrupts
		restore(mask);

		// Kill Proc
		kprintf("getPT(): Invalid PT %d for PID %d\nKilling Proc!! \n", frame, currpid);
		kill(currpid);

		// Return
		return SYSERR;	
	}
	
	// Put PT at FRAME
	pt_t* nullPT = (pt_t*)frametab[frame - FRAME0].loc;
	frametab[frame - FRAME0].type = PT_FRAME;
	frametab[frame - FRAME0].pid = currpid;

	// Set PTE Bits to 0
	int i;
	for(i = 0; i < FRAME_SIZE; i++) {
		nullPT[i].pt_pres = 0;	
		nullPT[i].pt_write = 1;
		nullPT[i].pt_user = 0;
		nullPT[i].pt_pwt = 0;
		nullPT[i].pt_pcd = 0;
		nullPT[i].pt_acc = 0;
		nullPT[i].pt_dirty = 0;
		nullPT[i].pt_mbz = 0;
		nullPT[i].pt_global = 0;
		nullPT[i].pt_avail = 0;
		nullPT[i].pt_base = 0;
	}

	// Return PD Frame
	restore(mask);
	return frame;
}

// Get Frame for PD and PT
uint16 getDSFrame() {
	// Disable Interrupts
	intmask mask = disable();

	// Get Frame from First 1000
	int i;
	for(i = 0; i < NDSFRAMES; i++) {
		if(frametab[i].type == FREE_FRAME) {
			// Restore Interrupts and Return
			restore(mask);
			return i + FRAME0;
		}
	}

	// Return ERROR
	restore(mask);
	return SYSERR;
}

// Get Frame for Page
uint16 getPFrame() {
	// Disable Interrupts
	intmask mask = disable();

	// Error Handeling
	if(proctab[currpid].prVpages <= 0) {
		// Restore
		restore(mask);

		// Kill Proc
		kprintf("getPFrame(): No Pages for PID %d\nKilling Proc!! \n", currpid);
		kill(currpid);

		// Return
		return SYSERR;
	}

	// Get Frame from First 1000
	int i;
	for(i = NDSFRAMES; i < NFRAMES; i++)
		if(frametab[i].type == FREE_FRAME) {
			// Reduce Page Counts
			proctab[currpid].prVpages--;

			// Set Table
			frametab[i].type = PG_FRAME;
			frametab[i].pid = currpid;

			// Test Print
			if(VERBOSE)
				kprintf("\ngetPFrame(): Frame -> %d for PID %d\n", i + FRAME0, currpid);

			// Restore Interrupts and Return
			restore(mask);
			return i + FRAME0;
		}

	// Restore
	restore(mask);

	// Kill Proc
	kprintf("getPFrame(): No Frames for PID %d\nKilling Proc!! \n", currpid);
	kill(currpid);
	
	// Return
	return SYSERR;
}

syscall freeFrames(int pid) {
	// Disable Interrupts
	intmask mask = disable();
	
	// Loop (Reverse)
	int i;
	for(i = 0; i < NFRAMES; i++) {
		if(frametab[i].pid == pid) {
			// If PT
			if(frametab[i].type == PT_FRAME) {
				// Hook
				#ifdef TALK
				hook_ptable_delete((unsigned int)frametab[i].loc);
				#endif
			}

			// Delete Frame
			frametab[i].pid = -1;
			frametab[i].type = FREE_FRAME;
		}
	}
	
	// Restore
	restore(mask);
	
	// Return
	return SYSERR;
}

// Print FrameTAB
void printFrames() {
	int i;
	for(i = 0; i < NFRAMES; i++) {
		if(frametab[i].type != FREE_FRAME) {
			kprintf("FRAME%d Type:%d PID:%d\n", i+FRAME0, frametab[i].type, frametab[i].pid);
		}
	}
}

/**
// Print PT
void printPT() {

}

// Print PD
void printPD() {

}
**/
