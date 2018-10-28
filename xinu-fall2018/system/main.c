/*  main.c  - main */

#include <xinu.h>

process	main(void) {
	/* Print Welcome Messages */
	welcome();

	/* Lab 3: Test Code */
	// Test Code for CFS
	/**
	kprintf("\nTesting CFS with 4 CPU Bound and 4 I/O Bound Procs.\n");
	resume(create(appR3test, 1024, 20, "appR3test23", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test24", 1, 1));
	resume(create(appR3test, 1024, 20, "appR3test25", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test26", 1, 1));
	resume(create(appR3test, 1024, 20, "appR3test27", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test28", 1, 1));
	resume(create(appR3test, 1024, 20, "appR3test29", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test30", 1, 1));
	sleep(25);
	
	kprintf("\nTesting CFS with Dynamic 4 CPU Bound and 4 I/O Bound Procs.\n");
	resume(create(appR3test, 1024, 20, "appR3test23", 1, 0));
	sleepms(500);
	resume(create(appR3test, 1024, 20, "appR3test24", 1, 1));
	sleepms(500);
	resume(create(appR3test, 1024, 20, "appR3test25", 1, 0));
	sleepms(500);
	resume(create(appR3test, 1024, 20, "appR3test26", 1, 1));
	sleepms(500);
	resume(create(appR3test, 1024, 20, "appR3test27", 1, 0));
	sleepms(500);
	resume(create(appR3test, 1024, 20, "appR3test28", 1, 1));
	sleepms(500);
	resume(create(appR3test, 1024, 20, "appR3test29", 1, 0));
	sleepms(500);
	resume(create(appR3test, 1024, 20, "appR3test30", 1, 1));
	sleep(25);
	

	// Test Code for RMS
	kprintf("\nTesting RMS with 4 Real Time Procs\n");

	// Set Parameters
	rmsparam_t p1, p2, p3, p4;
	p1.rms_ct = 300;
	p1.rms_period = 999;
	p2.rms_ct = 100;
	p2.rms_period = 1000;
	p3.rms_ct = 50;
	p3.rms_period = 900;
	p4.rms_ct = 25;
	p4.rms_period = 800;
	
	// Create RMS Procs
	resume(rms_create(rms_app, 1024, &p1, "rms_app1", 2, p1.rms_ct, p1.rms_period));		
	resume(rms_create(rms_app, 1024, &p2, "rms_app2", 2, p2.rms_ct, p2.rms_period));	
	resume(rms_create(rms_app, 1024, &p3, "rms_app3", 2, p3.rms_ct, p3.rms_period));	
	resume(rms_create(rms_app, 1024, &p4, "rms_app4", 2, p4.rms_ct, p4.rms_period));
	sleep(25);
	
	kprintf("\nTesting R3 with RMS\n");
	
	// Create TS Procs
	resume(create(appR3test, 1024, 20, "appR3test7", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test8", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test9", 1, 0));
	resume(create(appR3test, 1024, 20, "appR3test10", 1, 0));

	// Create RMS Procs
	resume(rms_create(rms_app, 1024, &p1, "rms_app1", 2, p1.rms_ct, p1.rms_period));		
	resume(rms_create(rms_app, 1024, &p2, "rms_app2", 2, p2.rms_ct, p2.rms_period));	
	resume(rms_create(rms_app, 1024, &p3, "rms_app3", 2, p3.rms_ct, p3.rms_period));	
	resume(rms_create(rms_app, 1024, &p4, "rms_app4", 2, p4.rms_ct, p4.rms_period));
	sleep(25);
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
