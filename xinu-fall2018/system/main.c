/*  main.c  - main */

#include <xinu.h>

process	main(void) {
	/* Print Welcome Messages */
	welcome();

	/* Lab 1: Test Code */
	sleep(123);
	xminsec_t obj;
	xuptime(&obj);

	kprintf("CLKTIME: %d\n", clktime);
	kprintf("MIN: %d\n", obj.upmin);
	kprintf("SEC: %d\n", obj.upsec);


	/* Run the Xinu shell */
	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */
	while (TRUE) {
		receive();
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
	}
	return OK;
}
