// Import Libs
#include <xinu.h>

// High Level Page Fault Handler
void pfhandler() {
	// Step 1: Find the Faulting Address
	unsigned long fadd = getCR2();

	// Hook
	//hook_pfault(fadd);

	// Increment Count
	pf_count++;

	// Step 0: Error Code Handeling ()
	/**
	if((err_code & 0x2) == 0x2) {
		return;
	}**/

	// Step 2: Compute PD
	pd_t* procPD = (pd_t*)frametab[proctab[currpid].prpd - FRAME0].loc;

	// Step 3: Check if PD has PDE
	int PDEInd = fadd >> 22;
	if(procPD[PDEInd].pd_pres == 0) {
		procPD[PDEInd].pd_pres = 1;
		procPD[PDEInd].pd_write = 1;
		procPD[PDEInd].pd_base = getPT();

		// Hook
		//hook_ptable_create(PDEInd);
	}

	// Step 4: Compute PT
	pt_t* procPT = (pt_t*)frametab[procPD[PDEInd].pd_base - FRAME0].loc;

	// Step 5: Check if PT has PTE
	unsigned long fadd2 = fadd << 10;
	int PTEInd = fadd2 >> (10 + 12);
	if(procPT[PTEInd].pt_pres == 0) {
		procPT[PTEInd].pt_pres = 1;
		procPT[PTEInd].pt_write = 1; 
		procPT[PTEInd].pt_base = getPFrame();
	}	
}
