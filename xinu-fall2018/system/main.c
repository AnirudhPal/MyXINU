/*  main.c  - main */

#include <xinu.h>

process	main(void) {
	/* Print Welcome Messages */
	welcome();

	/* Lab 1: Test Code */
	// Test Code for 4.1
	int x = 1;
	kprintf("\nGoing to sleep for %d to test xuptime().\n", x);
	sleep(x);
	xminsec_t obj;
	xuptime(&obj);
	kprintf("upmin: %d\n", obj.upmin);
	kprintf("upsec: %d\n\n", obj.upsec);

	// Test Code for 5.1
	kprintf("\nAttempting to Reverse byte order for 0x12ABCDEF.\n");
	kprintf("revbyteorder_asm(): 0x%08X\n", revbyteorder_asm(313249263));
	kprintf("revbyteorder_inline(): 0x%08X\n", revbyteorder_inline(313249263));
	kprintf("revbyteorder(): 0x%08X\n", revbyteorder(313249263));
	kprintf("revbyteorder_gcc(): = 0x%08X\n\n", revbyteorder_gcc(313249263));

	// Test Code for 5.2
	kprintf("\nCalling printsegaddress().\n");
	printsegaddress();

	// Test Code for 5.3
	kprintf("\nRun Time Stack Top Tests.\nBefore creating myprogA().\n");
	char* rsp;
	__asm__("movl %%esp, %%ebx;"
		: "=b" (rsp)
	);
	kprintf("Address: 0x%08X, Value: 0x%08X\n", (uint32)rsp, (uint32)*rsp);
	resume(create(myprogA, 1024, 21, "myprogA", 0));
	kprintf("After completion of myprogA()\n");
	__asm__("movl %%esp, %%ebx;"
		: "=b" (rsp)
	);
	kprintf("Address: 0x%08X, Value: 0x%08X\n\n", (uint32)rsp, (uint32)*rsp);

	// Test Code for 5.4
	kprintf("\nComparision of Run Time Stack.\n");
	resume(create(myprogA, 1024, 21, "myprogA", 0));
	resume(create(myfuncA, 1024, 21, "myfuncA", 1, 456));

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
