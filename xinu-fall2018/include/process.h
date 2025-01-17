/* process.h - isbadpid */

/* Maximum number of processes in the system */

#ifndef NPROC
#define	NPROC		8
#endif

/* CFS Vars - pal5, Oct 15 */
#define MAXPRIO		0x7FFF

/* Process state constants */

#define	PR_FREE		0	/* Process table entry is unused	*/
#define	PR_CURR		1	/* Process is currently running		*/
#define	PR_READY	2	/* Process is on ready queue		*/
#define	PR_RECV		3	/* Process waiting for message		*/
#define	PR_SLEEP	4	/* Process is sleeping			*/
#define	PR_SUSP		5	/* Process is suspended			*/
#define	PR_WAIT		6	/* Process is on semaphore queue	*/
#define	PR_RECTIM	7	/* Process is receiving with timeout	*/

/* Miscellaneous process definitions */

#define	PNMLEN		16	/* Length of process "name"		*/
#define	NULLPROC	0	/* ID of the null process		*/

/* Process initialization constants */

#define	INITSTK		65536	/* Initial process stack size		*/
#define	INITPRIO	/*0x7FFF*/20	/* Initial process priority, Moded for testing - pal5, Oct 16		*/
#define IOPRIO		21	/* I/O Bound Process Priority - pal5, Sep 26	*/
#define XINUSCHED	1	/* Use R3 Scheduler - pal5, Sep 26 and Use CFS Scheduler - pal5, Oct 15		*/
#define	INITRET		userret	/* Address to which process returns	*/

/* Inline code to check process ID (assumes interrupts are disabled)	*/

// PID Halved for New Delta Queue - pal5, Qct 29
#define	isbadpid(x)	( ((pid32)(x) < 0) || \
			  ((pid32)(x) >= (NPROC / 2)) || \
			  (proctab[(x)].prstate == PR_FREE))

/* Number of device descriptors a process can have open */

#define NDESC		5	/* must be odd to make procent 4N bytes	*/

/* Definition of the process table (multiple of 32 bits) */

struct procent {		/* Entry in the process table		*/
	uint16	prstate;	/* Process state: PR_CURR, etc.		*/
	pri16	prprio;		/* Process priority			*/
	char	*prstkptr;	/* Saved stack pointer			*/
	char	*prstkbase;	/* Base of run time stack		*/
	uint32	prstklen;	/* Stack length in bytes		*/
	char	prname[PNMLEN];	/* Process name				*/
	sid32	prsem;		/* Semaphore on which process waits	*/
	pid32	prparent;	/* ID of the creating process		*/
	umsg32	prmsg;		/* Message sent to this process		*/
	bool8	prhasmsg;	/* Nonzero iff msg is valid		*/
	int16	prdesc[NDESC];	/* Device descriptors for process	*/
	uint32	pgrosscpu;	/* Stores CPU Usage Time - pal5		*/
	uint32	pstartwait;	/* Waiting Start Marker  - pal5		*/
	uint32	pwaittime;	/* Stores Process Wait   - pal5		*/
	uint32	pwaitcount;	/* Stores Wait Iterations- pal5		*/
	uint32	pvirtcpu;	/* Stores Virtual CPU Time - pal5 	*/
	bool8	prrms;		/* Identifies RMS Proc - pal5		*/
	uint16	prct;		/* RMS Computatation Time - pal5 	*/
	uint16	prperiod;	/* RMS Period - pal5			*/
	void	(*funcptr)();	/* Call Back - pal5			*/
	uint32	prretadd;	/* Return Address - pal5		*/
	struct xsigtab prsig[SIGNUM]; /* Signal Handlers - pal5		*/
	int sigs[2];		/* Stores Received Signals */
 
};

/* Marker for the top of a process stack (used to help detect overflow)	*/
#define	STACKMAGIC	0x0A0AAAA9

extern	struct	procent proctab[];
extern	int32	prcount;	/* Currently active processes		*/
extern	pid32	currpid;	/* Currently executing process		*/
