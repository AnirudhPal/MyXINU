/*  main.c  - main */

#include <xinu.h>

process	main(void) {
	/* Print Welcome Messages */
	welcome();

	/* Lab 1: Test Code */
	sleep(5);
	xminsec_t obj;
	xuptime(&obj);

	kprintf("CLKTIME: %d\n", clktime);
	kprintf("MIN: %d\n", obj.upmin);
	kprintf("SEC: %d\n", obj.upsec);

	kprintf("\nrevbyteorder_asm(0x12ABCDEF) = 0x%08X\n", revbyteorder_asm(313249263));
	kprintf("\nrevbyteorder_inline(0x12ABCDEF) = 0x%08X\n", revbyteorder_inline(313249263));
	kprintf("\nrevbyteorder(0x12ABCDEF) = 0x%08X\n", revbyteorder(313249263));
	kprintf("\nrevbyteorder_gcc(0x12ABCDEF) = 0x%08X\n", revbyteorder_gcc(313249263));

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
