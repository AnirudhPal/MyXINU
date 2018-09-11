#include <xinu.h>

long revbyteorder_inline(long x) {
	// Inline Assembly
	int ret;
	__asm__("movl %%ebx, %%eax;"
		"bswap	%%eax;"
		: "=a"	(ret)
		: "b"	(x)
	);

	// Return
	return ret;
}	
