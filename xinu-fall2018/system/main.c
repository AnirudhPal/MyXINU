/*  main.c  - main */

#include <xinu.h>

process	main(void) {
	/* Print Welcome Messages */
	welcome();

	/* Lab 4: Test Code */
	kprintf("\nTesting Single Sender\n");
	resume(create(receiver, 2042, 10, "receiver0", 0));
	resume(create(sender, 2042, 15, "sender0", 2, 4, 1234));
	sleep(5);

	kprintf("\nTesting Single Sender with Sleeping Receiver\n");
	resume(create(receiverslp, 2042, 10, "receiverslp0", 0));
	resume(create(sender, 2042, 15, "sender1", 2, 6, 4321));
	sleep(5);

	kprintf("\nTesting Multiple Senders\n");
	resume(create(receiver, 2042, 10, "receiver1", 0));
	resume(create(sender, 2042, 15, "sender2", 2, 8, 1111));
	sleep(5);
	resume(create(sender, 2042, 15, "sender3", 2, 8, 2222));
	sleep(5);
	resume(create(sender, 2042, 15, "sender4", 2, 8, 3333));
	sleep(5);
	resume(create(sender, 2042, 15, "sender5", 2, 8, 4444));
	sleep(5);

	kprintf("\nTesting SIGXCPU with 2 Procs\n");
	resume(create(receivercpu, 2042, 10, "receivercpu0", 0));
	resume(create(receivercpu, 2042, 10, "receivercpu1", 0));
	sleep(5);
	//resume(create(receiver2, 2042, 10, "receiver2", 0));

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
