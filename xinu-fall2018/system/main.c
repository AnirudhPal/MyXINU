/*  main.c  - main */

#include <xinu.h>

process	main(void) {
	/* Print Welcome Messages */
	welcome();

	/* Lab 2: Test Code */
	
	// Test Code for 3.1
	kprintf("\nTesting clktimemilli.\n");
	sleep(2); // Syscall
	int k;
	for(k = 0; k < 100000; k++); // Computation
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

	// Test Code for 5.5 (R3 Scheduler)
	kprintf("\nTesting R3 with 8 CPU Bound Procs.\n");
	resume(create(appR3test, 1024, 20, "appR3test7", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test8", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test9", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test10", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test11", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test12", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test13", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test14", 1, 0));
	sleep(5);	
	kprintf("\nTesting R3 with 8 I/O Bound Procs.\n");
	resume(create(appR3test, 1024, 20, "appR3test15", 1, 1));
	resume(create(appR3test, 1024, 20, "appR3test16", 1, 1));
	resume(create(appR3test, 1024, 20, "appR3test17", 1, 1));
	resume(create(appR3test, 1024, 20, "appR3test18", 1, 1));
	resume(create(appR3test, 1024, 20, "appR3test19", 1, 1));
	resume(create(appR3test, 1024, 20, "appR3test20", 1, 1));
	resume(create(appR3test, 1024, 20, "appR3test21", 1, 1));
	resume(create(appR3test, 1024, 20, "appR3test22", 1, 1));
	sleep(25);	
	kprintf("\nTesting R3 with 4 CPU Bound and 4 I/O Bound Procs.\n");
	resume(create(appR3test, 1024, 20, "appR3test23", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test24", 1, 1));
	resume(create(appR3test, 1024, 20, "appR3test25", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test26", 1, 1));
	resume(create(appR3test, 1024, 20, "appR3test27", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test28", 1, 1));
	resume(create(appR3test, 1024, 20, "appR3test29", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test30", 1, 1));
	sleep(25);	
	
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
