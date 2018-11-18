// Modified getmem() to support Virtual Heap - pal5, Nov 16
#include <xinu.h>

char* vgetmem(uint32 nbytes) {
	// Local Vars
	intmask	mask;
	struct	heapblk	*prev, *curr, *leftover;

	// Disable Interrupts
	mask = disable();

	// Error
	if (!proctab[currpid].isVcreated || nbytes == 0) {
		restore(mask);
		return (char *)SYSERR;
	}

	// Round to Nearest Multiple of Struct
	nbytes = (uint32) roundmb(nbytes);

	// Get Proc VHeap
	prev = &(proctab[currpid].prVheap);
	curr = proctab[currpid].prVheap.hnext;

	// Intialize first Node
	if(!proctab[currpid].hasHeap) {
		proctab[currpid].hasHeap = TRUE;
		curr->hnext = NULL;
		curr->hlength = prev->hlength;	
	}

	// Parse Heap
	while (curr != NULL) {
		// Exact Match
		if (curr->hlength == nbytes) {	/* Block is exact match	*/
			prev->hnext = curr->hnext;
			proctab[currpid].prVheap.hlength -= nbytes;
			restore(mask);
			return (char *)(curr);

		} 

		// Bigger
		else if (curr->hlength > nbytes) { /* Split big block	*/
			leftover = (struct heapblk *)((uint32) curr +
					nbytes);
			prev->hnext = leftover;
			leftover->hnext = curr->hnext;
			leftover->hlength = curr->hlength - nbytes;
			proctab[currpid].prVheap.hlength -= nbytes;
			restore(mask);
			return (char *)(curr);
		} 

		// Look for Next
		else {			/* Move to next block	*/
			prev = curr;
			curr = curr->hnext;
		}
	}

	// Error
	restore(mask);
	return (char *)SYSERR;
}
