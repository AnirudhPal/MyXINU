/* initialize.c - nulluser, sysinit, sizmem */

/* Handle system initialization and become the null process */

#include <xinu.h>
#include <string.h>

extern	void	start(void);	/* Start of Xinu code			*/
extern	void	*_end;		/* End of Xinu code			*/

/* Function prototypes */

extern	void main(void);	/* Main is the first process created	*/
extern	void xdone(void);	/* System "shutdown" procedure		*/
static	void sysinit(); 	/* Internal system initialization	*/
extern	void meminit(void);	/* Initializes the free memory list	*/
void initialize_paging();	/* Do Paging Stuff - pal5, Nov 14	*/
void initialize_frames();	/* Create Frame Tab - pal5, Nov 14	*/
void initialize_pd_null();	/* Create PD for Null - pal5, Nov 14	*/
void initialize_pt_null();	/* Create PTs for Null - pal5, Nov 14	*/

/* Declarations of major kernel variables */

struct	procent	proctab[NPROC];	/* Process table			*/
struct	sentry	semtab[NSEM];	/* Semaphore table			*/
struct	memblk	memlist;	/* List of free memory blocks		*/
frame frametab[NFRAMES];	/* Frames table = pal5, Oct 13		*/


/* Active system status */

int	prcount;		/* Total number of live processes	*/
pid32	currpid;		/* ID of currently executing process	*/

bool8   PAGE_SERVER_STATUS;    /* Indicate the status of the page server */
sid32   bs_init_sem;
/*------------------------------------------------------------------------
 * nulluser - initialize the system and become the null process
 *
 * Note: execution begins here after the C run-time environment has been
 * established.  Interrupts are initially DISABLED, and must eventually
 * be enabled explicitly.  The code turns itself into the null process
 * after initialization.  Because it must always remain ready to execute,
 * the null process cannot execute code that might cause it to be
 * suspended, wait for a semaphore, put to sleep, or exit.  In
 * particular, the code must not perform I/O except for polled versions
 * such as kprintf.
 *------------------------------------------------------------------------
 */

void	nulluser()
{	
	struct	memblk	*memptr;	/* Ptr to memory block		*/
	uint32	free_mem;		/* Total amount of free memory	*/
	
	/* Initialize the system */
		
	sysinit();

	initialize_paging();		// Initialize Paging - pal5, Oct 10

	kprintf("\n\r%s\n\n\r", VERSION);
	
	/* Output Xinu memory layout */
	free_mem = 0;
	for (memptr = memlist.mnext; memptr != NULL;
						memptr = memptr->mnext) {
		free_mem += memptr->mlength;
	}
	kprintf("%10d bytes of free memory.  Free list:\n", free_mem);
	for (memptr=memlist.mnext; memptr!=NULL;memptr = memptr->mnext) {
	    kprintf("           [0x%08X to 0x%08X]\r\n",
		(uint32)memptr, ((uint32)memptr) + memptr->mlength - 1);
	}

	kprintf("%10d bytes of Xinu code.\n",
		(uint32)&etext - (uint32)&text);
	kprintf("           [0x%08X to 0x%08X]\n",
		(uint32)&text, (uint32)&etext - 1);
	kprintf("%10d bytes of data.\n",
		(uint32)&ebss - (uint32)&data);
	kprintf("           [0x%08X to 0x%08X]\n\n",
		(uint32)&data, (uint32)&ebss - 1);

	/* Create the RDS process */

	rdstab[0].rd_comproc = create(rdsprocess, RD_STACK, RD_PRIO,
					"rdsproc", 1, &rdstab[0]);
	if(rdstab[0].rd_comproc == SYSERR) {
		panic("Cannot create remote disk process");
	}
	resume(rdstab[0].rd_comproc);

	/* Enable interrupts */

	enable();

	/* Create a process to execute function main() */

	resume (
	   create((void *)main, INITSTK, INITPRIO, "Main process", 0,
           NULL));

	/* Become the Null process (i.e., guarantee that the CPU has	*/
	/*  something to run when no other process is ready to execute)	*/

	while (TRUE) {
		;		/* Do nothing */
	}

}

/*------------------------------------------------------------------------
 *
 * sysinit  -  Initialize all Xinu data structures and devices
 *
 *------------------------------------------------------------------------
 */
static	void	sysinit()
{
	int32	i;
	struct	procent	*prptr;		/* Ptr to process table entry	*/
	struct	sentry	*semptr;	/* Ptr to semaphore table entry	*/

	/* Platform Specific Initialization */

	platinit();

	/* Initialize the interrupt vectors */

	initevec();
	
	/* Initialize free memory list */
	
	meminit();

	/* Initialize system variables */

	/* Count the Null process as the first process in the system */

	prcount = 1;

	/* Scheduling is not currently blocked */

	Defer.ndefers = 0;

	/* Initialize process table entries free */

	for (i = 0; i < NPROC; i++) {
		prptr = &proctab[i];
		prptr->prstate = PR_FREE;
		prptr->prname[0] = NULLCH;
		prptr->prstkbase = NULL;
		prptr->prprio = 0;
	}

	/* Initialize the Null process entry */	

	prptr = &proctab[NULLPROC];
	prptr->prstate = PR_CURR;
	prptr->prprio = 0;
	strncpy(prptr->prname, "prnull", 7);
	prptr->prstkbase = getstk(NULLSTK);
	prptr->prstklen = NULLSTK;
	prptr->prstkptr = 0;
	currpid = NULLPROC;

	/* Initialize the Paging Stuff - pal5, Nov 14 */
	prptr->isVcreated = FALSE;	// Create using create()
	prptr->prpd = FRAME0;		// Shared PD
	prptr->prVpages = 0;		// No Pages requested

	/* Initialize semaphores */

	for (i = 0; i < NSEM; i++) {
		semptr = &semtab[i];
		semptr->sstate = S_FREE;
		semptr->scount = 0;
		semptr->squeue = newqueue();
	}

	/* Initialize buffer pools */

	bufinit();

	/* Create a ready list for processes */

	readylist = newqueue();

	/* Initialize the real time clock */

	clkinit();

	for (i = 0; i < NDEVS; i++) {
		init(i);
	}

        PAGE_SERVER_STATUS = PAGE_SERVER_INACTIVE;
        bs_init_sem = semcreate(1);

	return;
}

/*------------------------------------------------------------------------
 *
 * initialize_paging - Initialize all Xinu Paging System. pal5, Nov 10
 *
 *------------------------------------------------------------------------
 */
void	initialize_paging() {
	// Step 1: Intialize Frame, Page Directory, Page Table and Page Data Structure
	initialize_frames();	 

	// Step 2: Allocate a PD for Null Proc
	initialize_pd_null();

	// Step 3: Make 4 Page Tables that map first 4096 Frames	
	// Step 4: Make 1 Page Table that map 1024 frames from 0x90000000
	initialize_pt_null();
 
	// Step 5: Set PDBR for Null Proc
	setPDBR(FRAME0);

	// Step 6: Set Page Fault ISR

	// Step 7: Turn On Paging
	pagingOn();

	//kprintf("Test PD:")

	// Return Control
	return;
}

/*------------------------------------------------------------------------
 *
 * initialize_frames - Initialize frames after OG Xinu. pal5, Nov 13
 *
 *------------------------------------------------------------------------
 */
void	initialize_frames() {
	// Create Frames
	int i;
	for(i = 0; i < NFRAMES; i++) {
		// Set Unused
		frametab[i].isUsed = FALSE;

		// Set Type
		frametab[i].type = FREE_FRAME;
		
		// Set Location (Pyhsical/Virtual)
		frametab[i].loc = (i + FRAME0) * NBPG;
	}
}


/*------------------------------------------------------------------------
 *
 * initialize_pd_null - Initialize PD for Null Proc pal5, Nov 13
 *
 *------------------------------------------------------------------------
 */
void	initialize_pd_null() {
	// Put PD at FRAME0
	pd_t* nullPD = (pd_t*)frametab[0].loc;
	frametab[0].isUsed = TRUE;
	frametab[0].type = PD_FRAME;

	// Set PDE Bits to 0
	int i;
	for(i = 0; i < FRAME_SIZE; i++) {
		nullPD[i].pd_pres = 0;	
		nullPD[i].pd_write = 0;
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
}

/*------------------------------------------------------------------------
 *
 * initialize_pt_null - Initialize PT for Null Proc pal5, Nov 13
 *
 *------------------------------------------------------------------------
 */
void	initialize_pt_null() {
	// Stage Var
	pt_t* nullPT;
	
	// Set 4 PT for OG XINU
	int i;
	for(i = 0; i < 4; i++) {
		// Put PT at FRAME1 + i
		nullPT = (pd_t*)frametab[i + 1].loc;
		frametab[i + 1].isUsed = TRUE;
		frametab[i + 1].type = PT_FRAME;

		// Set PTE Bits for OG Xinu
		int j;
		for(j = 0; j < FRAME_SIZE; j++) {
			nullPT[j].pt_pres = 1;	
			nullPT[j].pt_write = 1;
			nullPT[j].pt_user = 0;
			nullPT[j].pt_pwt = 0;
			nullPT[j].pt_pcd = 0;
			nullPT[j].pt_acc = 0;
			nullPT[j].pt_dirty = 0;
			nullPT[j].pt_mbz = 0;
			nullPT[j].pt_global = 0;
			nullPT[j].pt_avail = 0;
			nullPT[j].pt_base = i * FRAME_SIZE + j; 
		}										
	}

	// Set Dev PT
	// Put PT at FRAME5
	nullPT = (pd_t*)frametab[5].loc;
	frametab[5].isUsed = TRUE;
	frametab[5].type = PT_FRAME;

	// Set PTE Bits for Dev
	for(i = 0; i < FRAME_SIZE; i++) {
		nullPT[i].pt_pres = 1;	
		nullPT[i].pt_write = 1;
		nullPT[i].pt_user = 0;
		nullPT[i].pt_pwt = 0;
		nullPT[i].pt_pcd = 0;
		nullPT[i].pt_acc = 0;
		nullPT[i].pt_dirty = 0;
		nullPT[i].pt_mbz = 0;
		nullPT[i].pt_global = 0;
		nullPT[i].pt_avail = 0;
		nullPT[i].pt_base = DEV_FRAME + i;
	}
}

void testPrint5Frames() {
	// Print PD
	pd_t* nullPD = (pd_t*)frametab[0].loc;
	kprintf("PD Frame: %d\n", (unsigned long)nullPD/ NBPG);
	int i;
	for(i = 0; i < 1024; i++)
		kprintf("PDE %d: pd_pres = %d, pd_write = %d, pd_base = %d, pde_hex = =x%x\n", i, nullPD[i].pd_pres, nullPD[i].pd_write, nullPD[i].pd_base, nullPD[i]);

	// Print PTs
	pt_t* nullPT;
	for(i = 0; i < 5; i++) {
		nullPT = (pt_t*)frametab[i + 1].loc;
		kprintf("PT Frame: %d\n", (unsigned long)nullPT / NBPG);
		int j;
		for(j = 0; j < 1024; j++)
			kprintf("PTE %d: pt_pres = %d, pt_write = %d, pt_base = %d, pte_hex = =x%x\n", j, nullPT[j].pt_pres, nullPT[j].pt_write, nullPT[j].pt_base, nullPT[j]);
	}

}

int32	stop(char *s)
{
	kprintf("%s\n", s);
	kprintf("looping... press reset\n");
	while(1)
		/* Empty */;
}

int32	delay(int n)
{
	DELAY(n);
	return OK;
}
