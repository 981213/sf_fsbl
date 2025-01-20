#ifndef __RAM_H__
#define __RAM_H__

static long get_ram_size(long *base, long maxsize)
{
	volatile long *addr;
	long           cnt;
	long           val;
	long           size;

	for (cnt = (maxsize / sizeof(long)) >> 1; cnt > 0; cnt >>= 1) {
		addr = base + cnt;	/* pointer arith! */
		asm volatile ("" : : : "memory");
		*addr = ~cnt;
	}

	addr = base;
	asm volatile ("" : : : "memory");
	*addr = 0;
	asm volatile ("" : : : "memory");
	if ((val = *addr) != 0)
		return (0);

	for (cnt = 1; cnt < maxsize / sizeof(long); cnt <<= 1) {
		addr = base + cnt;	/* pointer arith! */
		val = *addr;
		if (val != ~cnt) {
			size = cnt * sizeof(long);
			return (size);
		}
	}

	return (maxsize);
}

#endif