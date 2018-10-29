// Definitions of XINU signals.

#define	SIGRECV	0
#define	SIGXCPU	1
#define	SIGTIME	2
#define SIGNUM	3

/* Signal Process Properties */
struct xsigtab{
	bool8 regyes;
	int (*fnt)();
	uint32 optarg;
};
