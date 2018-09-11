long revbyteorder(long x) {
	// Bit Manipluation
	x = (((x >> 24) & 0xFF) | ((x >> 8) & 0xFF00) | ((x << 8) & 0xFF0000) | ((x << 24) & 0xFF000000));

	// Return
	return x;
}
