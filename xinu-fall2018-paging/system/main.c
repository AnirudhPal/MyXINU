/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

process	main(void)
{

	/* Start the network */
	/* DO NOT REMOVE OR COMMENT THIS CALL */
	//netstart();

	/* Initialize the page server */
	/* DO NOT REMOVE OR COMMENT THIS CALL */
	//psinit();

	// Testing
	intmask mask = disable();
	kprintf("\nTesting 1 Page Usage\n");
	restore(mask);
	resume(vcreate(test1P, 1024, 1, 50, "test1P", 0));
	
	mask = disable();
	kprintf("\nTesting 2072 Page Usage\n");	
	restore(mask);
	resume(vcreate(test2072P, 1024, 2072, 50, "test2072P", 0));

	/*
	mask = disable();
	kprintf("\nTesting Same Virtual Address\n");	
	restore(mask);
	int AP = vcreate(test1A, 1024, 1, INITPRIO, "test1A", 0);
	int BP = vcreate(test1B, 1024, 1, INITPRIO, "test1B", 0);
	resume(AP);
	resume(BP);
	sleep(3);
	kill(AP);
	kill(BP);	
	
	mask = disable();
	kprintf("\nTesting vgetmem() and vfreemem()\n");
	restore(mask);
	resume(vcreate(test2072PGF, 1024, 2072, 50, "test2072PGF", 0));

	mask = disable();
	kprintf("\nTesting Exceeding Frames\n");	
	restore(mask);
	resume(vcreate(test2072P, 1024, 2072, INITPRIO, "test2072P0", 0));
	resume(vcreate(test2072P, 1024, 2072, INITPRIO, "test2072P1", 0));
	sleep(5);

	mask = disable();
	kprintf("\nTesting Freeing Frames\n");	
	restore(mask);
	resume(vcreate(test2072P, 1024, 2072, 50, "test2072P2", 0));
	resume(vcreate(test2072P, 1024, 2072, 50, "test2072P3", 0));

	mask = disable();
	kprintf("\nTesting Exceeding Pages\n");
	restore(mask);
	resume(vcreate(test2P, 1024, 1, 50, "test2P", 0));
	**/	


	kprintf("\n...creating a shell\n");
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
