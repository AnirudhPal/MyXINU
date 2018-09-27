/*  main.c  - main */

#include <xinu.h>

process	main(void) {
	/* Print Welcome Messages */
	welcome();

	/* Lab 2: Test Code */
	
	// Test Code for 3.1
	kprintf("\nTesting clktimemilli by sleeping.\n");
	sleep(1);
	kprintf("CLKTIME: %d s\n", clktime);
	kprintf("CLKTIMEMILLI: %d ms\n\n", clktimemilli);

	// Test Code for 3.2
	kprintf("\nTesting CPU Gross Time.\n");
	resume(create(appR3test, 1024, 20, "appR3test1", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test2", 1, 1));
	resume(create(appR3test, 1024, 20, "appR3test3", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test4", 1, 1));
	sleep(25);

	// Test Code for 3.3
	kprintf("\nTesting CPU Wait Time.\n");
	resume(create(appR3test, 1024, 19, "appR3test5", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test6", 1, 0));
	sleep(5);

	// Test Code for 4
	kprintf("\nTesting igetpid().\n");
	resume(create(pidProc, 1024, 20, "pidProc1", 0));
	resume(create(pidProc, 1024, 20, "pidProc2", 0));
	resume(create(pidProc, 1024, 20, "pidProc3", 0));
	resume(create(pidProc, 1024, 20, "pidProc4", 0));
	sleep(5);

	
	/**
	// Test Code for 5.5
	kprintf("\nTesting CPU Bound.\n");
	resume(create(cpuProc, 1024, 19, "cpuProc5", 3, 100, 10000, 5));
	resume(create(cpuProc, 1024, 19, "cpuProc6", 3, 100, 10000, 6));
	resume(create(cpuProc, 1024, 19, "cpuProc7", 3, 100, 10000, 7));
	resume(create(cpuProc, 1024, 19, "cpuProc8", 3, 100, 10000, 8));

	kprintf("\nTesting I/O Bound.\n");
	resume(create(ioProc, 1024, 19, "ioProc3", 3, 1000, 10, 3));
	resume(create(ioProc, 1024, 19, "ioProc4", 3, 1000, 10, 4));
	resume(create(ioProc, 1024, 19, "ioProc5", 3, 1000, 10, 5));
	resume(create(ioProc, 1024, 19, "ioProc6", 3, 1000, 10, 6));
	**/
		

		
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
