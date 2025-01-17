/* clkhandler.c - clkhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/

	/* Decrement the ms counter, and see if a second has passed */

	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}

	/* Higher granularity system time and current process cpu time counter, both of which increment at 1ms intervals - pal5, Sep23 */	
	clktimemilli++;
	currproctime++;

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			wakeup();
		}
	}

	/* Handle if SIGXCPU - pal5, Oct 29 */
	if(!isempty(alarmq)) {
		if((--queuetab[firstid(alarmq)].qkey) <= 0) {
			int id = dequeue(alarmq) - (NPROC / 2);
			sendSignal(id, SIGTIME);
		}
	}

	/* Handle if SIGXCPU - pal5, Oct 29 */
	// Check if Callback
	if(proctab[currpid].prsig[SIGXCPU].regyes)
		// Check if Time Limit Reached
		if(proctab[currpid].prsig[SIGXCPU].optarg < getuptime())
			// Send Signal
			sendSignal(currpid, SIGXCPU);

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
		/* Change Priority since it is CPU Bound - pal5, Sep 26 */
		if(XINUSCHED == 1 && proctab[currpid].prprio != 0 && proctab[currpid].prprio != INITPRIO && !(proctab[currpid].prrms)) {
			//kprintf("INITPRIO for PID %d\n", currpid);
			proctab[currpid].prprio = INITPRIO;
		}

		preempt = QUANTUM;
		resched();
	}
}
