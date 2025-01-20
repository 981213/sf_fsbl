#ifndef __IOMUX_H__
#define __IOMUX_H__
#include <bit.h>
#include <asm/io.h>
#define IOMUX_BASE(x)		(0x0ce3c000ul + 4 * (x))
#define IOMUX_FUNC_SW_SEL	BIT(12)
#define IOMUX_FMUX_SEL		BIT(11)
#define IOMUX_MODE		GENMASK(10, 9)
#define IOMUX_PINCONF		GENMASK(12, 9)

static void sf_iomux_set_func(unsigned int pin, unsigned int func)
{
	uint32_t reg = readl(IOMUX_BASE(pin));
	reg &= ~IOMUX_PINCONF;
	reg |= IOMUX_FUNC_SW_SEL | FIELD_PREP(IOMUX_MODE, func);
	writel(reg, IOMUX_BASE(pin));
}

#endif