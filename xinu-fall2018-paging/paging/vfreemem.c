// Modified freemem() to support Virtual Heap - pal5, Nov 18
#include <xinu.h>

syscall vfreemem(char *blkaddr, uint32 nbytes) {
	// Local Vars
	intmask	mask;
	struct	heapblk	*next, *prev, *block;
	uint32	top;

	// Disable Interrupts
	mask = disable();

	// Error
	if (!proctab[currpid].isVcreated || (nbytes == 0) || ((uint32) blkaddr < (uint32) (VHEAP_FRAME * NBPG))
			  || ((uint32) blkaddr > (uint32) (VHEAP_FRAME + proctab[currpid].prVRpages) * NBPG)) {
		restore(mask);
		return SYSERR;
	}

	// Round to Nearest Multiple of Struct
	nbytes = (uint32) roundmb(nbytes);

	// Get Proc VHeap
	block = (struct heapblk *)blkaddr;
	prev = &(proctab[currpid].prVheap);
	next = proctab[currpid].prVheap.hnext;
	
	// Parse Heap
	while ((next != NULL) && (next < block)) {
		prev = next;
		next = next->hnext;
	}

	// Parse Heap
	if (prev == &(proctab[currpid].prVheap)) {
		top = (uint32) NULL;
	} 
	else {
		top = (uint32) prev + prev->hlength;
	}

	// Parse Heap
	if (((prev != &(proctab[currpid].prVheap)) && (uint32) block < top)
	    || ((next != NULL)	&& (uint32) block+nbytes>(uint32)next)) {
		restore(mask);
		return SYSERR;
	}

	// Parse Heap
	proctab[currpid].prVheap.hlength += nbytes;

	// Parse Heap
	if (top == (uint32) block) {
		prev->hlength += nbytes;
		block = prev;
	} 
	else {	
		block->hnext = next;
		block->hlength = nbytes;
		prev->hnext = block;
	}

	// Parse Heap
	if (((uint32) block + block->hlength) == (uint32) next) {
		block->hlength += next->hlength;
		block->hnext = next->hnext;
	}

	// Return	
	restore(mask);
	return OK;
}
