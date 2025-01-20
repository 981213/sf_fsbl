#ifndef __PERIPH_CRM_H__
#define __PERIPH_CRM_H__
#include <asm/io.h>
#define PERIPH_RST			0x0
#define PERIPH_CLK_EN			0x4
#define PERIPH_BOE			0xc

static void sf_periph_clken_reset(unsigned long base) {
	writel(0xff, base + PERIPH_CLK_EN);
	writel(0x3, base + PERIPH_BOE);
	writel(0xff, base + PERIPH_RST);
	writel(0x0, base + PERIPH_RST);
}

#endif