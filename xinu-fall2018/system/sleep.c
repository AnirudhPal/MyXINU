/* sleep.c - sleep sleepms */

#include <xinu.h>

#define	MAXSECONDS	2147483		/* Max seconds per 32-bit msec	*/

/*------------------------------------------------------------------------
 *  sleep  -  Delay the calling process n seconds
 *------------------------------------------------------------------------
 */
syscall	sleep(
	  int32	delay		/* Time to delay in seconds	*/
	)
{
	if ( (delay < 0) || (delay > MAXSECONDS) ) {
		return SYSERR;
	}
	sleepms(1000*delay);
	return OK;
}

/*------------------------------------------------------------------------
 *  sleepms  -  Delay the calling process n milliseconds
 *------------------------------------------------------------------------
 */
syscall	sleepms(
	  int32	delay			/* Time to delay in msec.	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/

	if (delay < 0) {
		return SYSERR;
	}

	if (delay == 0) {
		yield();
		return OK;
	}

	/* Delay calling process */

	mask = disable();
	if (insertd(currpid, sleepq, delay) == SYSERR) {
		restore(mask);
		return SYSERR;
	}

	proctab[currpid].prstate = PR_SLEEP;
	
	/* Change Priority since it is I/O Bound - pal5, Sep 26 */
	if(XINUSCHED == 1 && proctab[currpid].prprio != 0 && proctab[currpid].prprio != IOPRIO && !(proctab[currpid].prrms)) {
		//kprintf("IOPRIO for PID %d\n", currpid);
		proctab[currpid].prprio = IOPRIO;
	}

	/* Initialize pvirtcpu to min current pvirtcpu - pal5, Oct 15 	*/
	if(XINUSCHED == 2) {
		// Get Entry
		struct procent* prptr = &proctab[currpid];		
		// Set Initial
		prptr->pvirtcpu = MAXPRIO;

		// Get Head and Tail of ReadyList
		qid16 head = queuehead(readylist);
		qid16 tail = queuetail(readylist);

		// Move to Node
		head = queuetab[head].qnext;
		
		// Iterate through List
		while(head != tail) {
			// Get Min
			if(proctab[head].pvirtcpu < prptr->pvirtcpu && head != NULLPROC)
				prptr->pvirtcpu = proctab[head].pvirtcpu;

			// Move to Next Node
			head = queuetab[head].qnext;
		}

		// Fix Lonely Procs
		if(prptr->pvirtcpu == MAXPRIO)
			prptr->pvirtcpu = 0;		
	}

	resched();
	restore(mask);
	return OK;
}
