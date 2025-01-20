#ifndef _IO_H
#define _IO_H
#include <stdint.h>
#include <stddef.h>

#define barrier()	asm volatile("":::"memory")
#define mb()		asm volatile("fence":::"memory")
#define rmb()		asm volatile("fence ir,ir":::"memory")
#define wmb()		asm volatile("fence ow,ow":::"memory")
#define __iormb()	asm volatile("fence i,ir":::"memory")
#define __iowmb()	asm volatile("fence w,o":::"memory")
#define cpu_relax()	asm volatile("pause":::"memory")
#define BUG()		do { asm volatile("ebreak":::"memory"); __builtin_unreachable(); } while (0)

#define readb_relaxed(p)	(*(const volatile uint8_t*)(p))
#define writeb_relaxed(v, p)	(void)(*(volatile uint8_t*)(p) = (v))
#define readw_relaxed(p)	(*(const volatile uint16_t*)(p))
#define writew_relaxed(v, p)	(void)(*(volatile uint16_t*)(p) = (v))
#define readl_relaxed(p)	(*(const volatile uint32_t*)(p))
#define writel_relaxed(v, p)	(void)(*(volatile uint32_t*)(p) = (v))
#define readq_relaxed(p)	(*(const volatile uint64_t*)(p))
#define writeq_relaxed(v, p)	(void)(*(volatile uint64_t*)(p) = (v))

#define readb(p)		({ uint8_t __v = readl_relaxed(p); __iormb(); __v; })
#define writeb(v, p)		({ __iowmb(); writeb_relaxed(v, p); })
#define readw(p)		({ uint16_t __v = readw_relaxed(p); __iormb(); __v; })
#define writew(v, p)		({ __iowmb(); writew_relaxed(v, p); })
#define readl(p)		({ uint32_t __v = readl_relaxed(p); __iormb(); __v; })
#define writel(v, p)		({ __iowmb(); writel_relaxed(v, p); })
#define readq(p)		({ uint64_t __v = readq_relaxed(p); __iormb(); __v; })
#define writeq(v, p)		({ __iowmb(); writeq_relaxed(v, p); })

#define L1_CACHE_SIZE		64
#if 0
static inline void dcache_wb(const volatile void *ptr, size_t size){wmb();}
static inline void dcache_inv(const volatile void *ptr, size_t size){wmb();}
static inline void dcache_wbinv(const volatile void *ptr, size_t size){wmb();}
#else
static inline void dcache_wb(const volatile void *ptr, size_t size)
{
	const volatile void * end = ptr + size;

	for (; ptr < end; ptr += L1_CACHE_SIZE)
		asm volatile("dcache.cpa %0" :: "r"(ptr));

	mb();
}

static inline void dcache_inv(const volatile void *ptr, size_t size)
{
	const volatile void * end = ptr + size;

	for (; ptr < end; ptr += L1_CACHE_SIZE)
		asm volatile("dcache.ipa %0" :: "r"(ptr));

	mb();
}

static inline void dcache_wbinv(const volatile void *ptr, size_t size)
{
	const volatile void * end = ptr + size;

	for (; ptr < end; ptr += L1_CACHE_SIZE)
		asm volatile("dcache.cipa %0" :: "r"(ptr));

	mb();
}
#endif

#endif
