/* send.c - send */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  send  -  Pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */
syscall	send(
		pid32		pid,		/* ID of recipient process	*/
		umsg32	msg		/* Contents of message		*/
	    )
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	if (prptr->prhasmsg) {
		restore(mask);
		return SYSERR;
	}
	prptr->prmsg = msg;		/* Deliver message		*/
	prptr->prhasmsg = TRUE;		/* Indicate message is waiting	*/

	/* If recipient waiting or in timed-wait make it ready */

	if (prptr->prstate == PR_RECV) {
		ready(pid);
	} else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid);
	}

	/* Modification for ROP Callback Mechanism - pal5, Oct 28 */
	if(prptr->funcptr != NULL) {
		uint32* sp = (uint32*)prptr->prstkptr;
		uint32* stack_bp = sp + 2;
		uint32* bp = (uint32*) *stack_bp;
		uint32* ret_add = bp + 1;
		prptr->prretadd = *ret_add;
		*ret_add = (uint32) &do_handler;
	}

	restore(mask);		/* Restore interrupts */
	return OK;
}
