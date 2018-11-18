/* Page Fault Dispatcher - pal5, Nov 16 */
		.text
		.globl	pfisr

pfisr:
		cli				# Disable Interrupts
		popl err_code			# Pop Error Code onto Global Var
		pushal				# Save General Registers
		pushfl				# Save Flags
		call	pfhandler		# Call Handler
		popfl				# Restore	
		popal				# Restore Registers
		sti				# Restore Interrupts
		iret				# Return from interrupt
