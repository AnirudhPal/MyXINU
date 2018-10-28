/*  main.c  - main */

#include <xinu.h>

process	main(void) {
	/* Print Welcome Messages */
	welcome();

	/* Lab 3: Test Code */
	//kprintf("resched: %d\n", (uint32)&resched);
	resume(create(receiver, 2042, 10, "receiver", 0));
	resume(create(sender, 2042, 15, "sender", 2, 4, 1213));	

	/* Run the Xinu shell */
	/**
	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	**/

	/* Wait for shell to exit and recreate it */
	/**
	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
	**/
}
