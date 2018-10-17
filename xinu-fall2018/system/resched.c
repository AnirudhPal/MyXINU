/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	/* The current process time is added to the gross cpu time and the counter is reset to start counting again - pal5, Sep 23 */
	ptold->pgrosscpu = ptold->pgrosscpu + currproctime;

	// Update Virtual CPU Time and Priority - pal5, Oct 15
	if(XINUSCHED == 2 && currpid != NULLPROC) {
		ptold->pvirtcpu = ptold->pvirtcpu + currproctime;
		ptold->prprio = MAXPRIO - ptold->pvirtcpu;
	}

	currproctime = 0;

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if (ptold->prprio > firstkey(readylist)) {
			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		insert(currpid, readylist, ptold->prprio);
	}

	/* Force context switch to highest priority ready process */
		
	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];

	/* Add wait time since ready to cumulative counter - pal5, Sep 26 */
	ptnew->pwaittime = (ptnew->pwaittime) + (clktimemilli - (ptnew->pstartwait));

	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* Reset time slice for process	*/

	// Quantum for RMS - pal5, Oct 16
	if(ptnew->prrms)
		preempt = RMSQUANTUM;
	
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);
	/* Old process returns here when resumed */

	return;
}

/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
