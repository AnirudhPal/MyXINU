// Import Libs
#include <xinu.h>

// High Level Page Fault Handler
void pfhandler() {
	kprintf("Page Fault: %d\n", err_code);	

	// Step 1: Find the Faulting Address
	unsigned long fadd = getCR2();

	// Step 2: Compute PD
	pd_t* procPD = (pd_t*)frametab[proctab[currpid].prpd - FRAME0].loc;

	// Step 3: Check if PD has PDE
	int PDEInd = fadd >> 22;
	kprintf("PDE: %u, FADD: %u\n", PDEInd, fadd);
	if(procPD[PDEInd].pd_pres == 0) {
		procPD[PDEInd].pd_pres = 1;
		procPD[PDEInd].pd_write = 1;
		procPD[PDEInd].pd_base = getPT();
	}

	// Step 4: Compute PT
	pt_t* procPT = (pt_t*)frametab[procPD[PDEInd].pd_base - FRAME0].loc;

	// Step 5: Check if PT has PTE
	int PTEInd = fadd << 10;
	PTEInd = PTEInd >> (10 + 12);
	kprintf("PTE: %u, FADD: %u\n", PTEInd, fadd);
	if(procPT[PTEInd].pt_pres == 0) {
		procPT[PTEInd].pt_pres = 1;
		procPT[PTEInd].pt_write = 1; 
		procPT[PTEInd].pt_base = getPFrame();
	}	
}
