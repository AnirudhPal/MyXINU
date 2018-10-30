/*  main.c  - main */

#include <xinu.h>

process	main(void) {
	/* Print Welcome Messages */
	welcome();

	/* Lab 4: Test Code */
	kprintf("\nTesting Single Sender\n");
	resume(create(receiver, 2042, 10, "receiver0", 0));
	resume(create(sender, 2042, 15, "sender0", 2, 4, 1234));
	sleep(1);

	kprintf("\nTesting Single Sender with Sleeping Receiver\n");
	resume(create(receiverslp, 2042, 10, "receiverslp0", 0));
	resume(create(sender, 2042, 15, "sender1", 2, 6, 4321));
	sleep(2);

	kprintf("\nTesting Multiple Senders\n");
	resume(create(receiver, 2042, 10, "receiver1", 0));
	resume(create(sender, 2042, 15, "sender2", 2, 8, 1111));
	sleep(1);
	resume(create(sender, 2042, 15, "sender3", 2, 8, 2222));
	sleep(1);
	resume(create(sender, 2042, 15, "sender4", 2, 8, 3333));
	sleep(1);
	resume(create(sender, 2042, 15, "sender5", 2, 8, 4444));
	sleep(1);

	kprintf("\nTesting SIGXCPU with 2 Procs\n");
	resume(create(receivercpu, 2042, 10, "receivercpu0", 0));
	resume(create(receivercpu, 2042, 10, "receivercpu1", 0));
	sleep(3);
	
	kprintf("\nTesting SIGTIME with 2 Procs without ROP\n");
	resume(create(receiveralm, 2042, 10, "receiveralm0", 0));
	resume(create(receiveralm, 2042, 10, "receiveralm1", 0));
	sleep(1);

	kprintf("\nTesting SIGTIME with 2 Procs with ROP\n");
	resume(create(receiveralmslp, 2042, 10, "receiveralmslp0", 0));
	resume(create(receiveralmslp, 2042, 10, "receiveralmslp1", 0));
	sleep(2);

	kprintf("\nTesting SIGRECV\n");
	kprintf("\nTesting Single Sender\n");
	resume(create(receiversig, 2042, 10, "receiversig0", 0));
	resume(create(sender, 2042, 15, "sender0", 2, 19, 1234));
	sleep(1);
	
	kprintf("\nTesting Single Sender with Sleeping receiversig\n");
	resume(create(receiversigslp, 2042, 10, "receiversigslp0", 0));
	resume(create(sender, 2042, 15, "sender1", 2, 21, 4321));
	sleep(2);
	
	kprintf("\nTesting Multiple Senders\n");
	resume(create(receiversig, 2042, 10, "receiversig1", 0));
	resume(create(sender, 2042, 15, "sender2", 2, 23, 1111));
	sleep(1);
	resume(create(sender, 2042, 15, "sender3", 2, 23, 2222));
	sleep(1);
	resume(create(sender, 2042, 15, "sender4", 2, 23, 3333));
	sleep(1);
	resume(create(sender, 2042, 15, "sender5", 2, 23, 4444));
	sleep(1);

	kprintf("\nTesting all Signals\n");
	resume(create(receivermix, 2042, 10, "receivermix0", 0));
	resume(create(sender, 2042, 15, "sender6", 2, 28, 1010));
	sleep(5);

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
