#include <xinu.h>

void printsegaddress() {
	// Print Map
	kprintf("\nEnd of Text at 0x%08X.\n", (uint32)&etext - 1);
	kprintf("End of Data at 0x%08X.\n", (uint32)&edata - 1);
	kprintf("End of Bss at 0x%08X.\n", (uint32)&ebss - 1);

	// Print Preceding
	print6preceding((char *)((uint32)&etext - 1));
	print6preceding((char *)((uint32)&edata - 1));
	print6preceding((char *)((uint32)&ebss - 1));

	// Print Following
	print6following((char *)((uint32)&etext - 1));
	print6following((char *)((uint32)&edata - 1));		
	print6following((char *)((uint32)&ebss - 1));	
}

void print6preceding(char* p) {
	// Loop
	kprintf("Printing 6 bytes before 0x%08X:\n", p);
	int i;
	for(i = 1; i <= 6; i++)
	kprintf("0x%08X: %x\n", p - i, (*(p - i)) & 0xFF);
}

void print6following(char* p) {
	// Loop
	kprintf("Printing 6 bytes after 0x%08X:\n", p);
	int i;
	for(i = 1; i <= 6; i++)
	kprintf("0x%08X: %x\n", p + i, (*(p + i)) & 0xFF);
}
