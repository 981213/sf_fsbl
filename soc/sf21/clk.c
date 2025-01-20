#include "reg.h"
#include <asm/io.h>
#include "clk.h"
#include <stdio.h>
#include <stdbool.h>

#ifdef SF21H8898
#define CPU_CLK 1250000000lu
#else
#define CPU_CLK 1125000000lu
#endif

#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

#define CRM_BASE (SYSM_BASE + 0x400)

#define PLL_CMN_CFG1 0x0
#define PLL_CMN_BYPASS BIT(27)
#define PLL_CMN_PD BIT(26)
#define PLL_CMN_FBDIV GENMASK(25, 14)
#define PLL_CMN_POSTDIV_PD BIT(13)
#define PLL_CMN_VCO_PD BIT(12)
#define PLL_CMN_POSTDIV1 GENMASK(11, 9)
#define PLL_CMN_POSTDIV2 GENMASK(8, 6)
#define PLL_CMN_REFDIV GENMASK(5, 0)

#define PLL_CMN_LOCK 0xc8
#define PLL_DDR_LOCK 0xcc
#define PLL_PCIE_LOCK 0xd4

#define CFG_LOAD 0x100
#define CFG_LOAD_PCIE_PLL BIT(4)
#define CFG_LOAD_DDR_PLL BIT(2)
#define CFG_LOAD_CMN_PLL BIT(1)
#define CFG_LOAD_DIV BIT(0)

#define CRM_CLK_SEL(_x) ((_x) * 4 + 0x80)
#define CRM_CLK_EN 0x8c
#define CRM_CLK_DIV(_x) ((_x) * 4 + 0x94)
#define CRM_CLK_DIV_MASK GENMASK(7, 0)

#define XTAL_FREQ 25000000

struct div_clk {
	const char *name;
	unsigned long rate;
	uint8_t div_reg;
	uint8_t div_offs;
	bool use_vco;
};

#define CLK_POSTDIV(_name, _rate, _div_reg, _div_offs)              \
	{                                                           \
		.name = #_name, .rate = _rate, .div_reg = _div_reg, \
		.div_offs = _div_offs, .use_vco = false,            \
	}

#define CLK_VCO(_name, _rate, _div_reg, _div_offs)                  \
	{                                                           \
		.name = #_name, .rate = _rate, .div_reg = _div_reg, \
		.div_offs = _div_offs, .use_vco = true,             \
	}

#define CLK_CPU 0
#define CLK_AXI 2
#define CLK_UART 5
#define CLK_NPU 7
#define CLK_CRYPT_APP 14

static struct div_clk cmnpll_div_clks[] = {
	[CLK_CPU] = CLK_POSTDIV(cpu, CPU_CLK, 0, 0),
	CLK_POSTDIV(pic, 562500000, 3, 16),
	[CLK_AXI] = CLK_POSTDIV(axi, 500000000, 0, 8),
	CLK_POSTDIV(ahb, 281250000, 0, 16),
	CLK_POSTDIV(apb, 187500000, 0, 24),
	[CLK_UART] = CLK_POSTDIV(uart, 93750000, 1, 0),
	CLK_POSTDIV(iram, 562500000, 1, 8),
	[CLK_NPU] = CLK_POSTDIV(npu, 562500000, 1, 24),
	CLK_POSTDIV(ethtsu, 93750000, 2, 16),
	CLK_VCO(gmac_byp_ref, 250000000, 2, 24),
	CLK_VCO(usb, 250000000, 1, 16),
	CLK_VCO(usbphy, 50000000, 2, 8),
	CLK_POSTDIV(serdes_csr, 93750000, 5, 0),
	CLK_POSTDIV(crypt_csr, 75000000, 5, 8),
	[CLK_CRYPT_APP] = CLK_POSTDIV(crypt_app, 375000000, 5, 16),
	CLK_POSTDIV(irom, 375000000, 5, 24),
	{},
};

static inline uint32_t crm_readl(uint32_t reg)
{
	return readl(CRM_BASE + reg);
}

static inline void crm_writel(uint32_t reg, uint32_t val)
{
	writel(val, CRM_BASE + reg);
}

static inline void crm_rmw(uint32_t reg, uint32_t clr, uint32_t set)
{
	uint32_t val = crm_readl(reg);
	val &= ~clr;
	val |= set;
	crm_writel(reg, val);
}

static unsigned long crm_cmnpll_vco_rate()
{
	uint32_t cfg = crm_readl(PLL_CMN_CFG1);
	unsigned long refdiv = FIELD_GET(PLL_CMN_REFDIV, cfg);
	unsigned long fbdiv = FIELD_GET(PLL_CMN_FBDIV, cfg);
	return (XTAL_FREQ / refdiv) * fbdiv;
}

static unsigned long crm_cmnpll_postdiv_rate(unsigned long parent_rate)
{
	uint32_t cfg = crm_readl(PLL_CMN_CFG1);
	unsigned long div1 = FIELD_GET(PLL_CMN_POSTDIV1, cfg);
	unsigned long div2 = FIELD_GET(PLL_CMN_POSTDIV2, cfg);
	return parent_rate / div1 / div2;
}

static unsigned long crm_div_rate(int idx, unsigned long parent_rate)
{
	struct div_clk *priv = &cmnpll_div_clks[idx];
	unsigned long div_reg = CRM_CLK_DIV(priv->div_reg);
	uint16_t div_offs = priv->div_offs;
	uint16_t div_val = (crm_readl(div_reg) >> div_offs) & CRM_CLK_DIV_MASK;
	div_val += 1;
	return parent_rate / div_val;
}

static void crm_div_set_divider(int idx, unsigned long parent_rate)
{
	struct div_clk *priv = &cmnpll_div_clks[idx];
	unsigned long div_reg = CRM_CLK_DIV(priv->div_reg);
	uint16_t div_offs = priv->div_offs;
	uint16_t div = DIV_ROUND_UP(parent_rate, priv->rate);
	if (div < 1)
		div = 1;
	else if (div > CRM_CLK_DIV_MASK + 1)
		div = CRM_CLK_DIV_MASK + 1;
	div -= 1;
	crm_rmw(div_reg, CRM_CLK_DIV_MASK << div_offs, div << div_offs);
}

static void crm_setup_dividers(unsigned long vco_rate, unsigned long postdiv)
{
	unsigned long postdiv_rate = vco_rate / postdiv;
	int i;
	for (i = 0; cmnpll_div_clks[i].name; i++)
		crm_div_set_divider(i, cmnpll_div_clks[i].use_vco ?
					       vco_rate :
					       postdiv_rate);
	crm_writel(CFG_LOAD, CFG_LOAD_DIV);
	crm_writel(CFG_LOAD, 0);
}

static void crm_divmux_bypass_cmnpll(bool bypass)
{
	if (bypass) {
		crm_writel(CRM_CLK_SEL(0), 0x5011555);
		crm_writel(CRM_CLK_SEL(1), 0x158005);
	} else {
		crm_writel(CRM_CLK_SEL(0), 0x0);
		crm_writel(CRM_CLK_SEL(1), 0x0);
	}
	crm_writel(CFG_LOAD, CFG_LOAD_DIV);
	crm_writel(CFG_LOAD, 0);
}

static void crm_setup_cmnpll(unsigned long vco_rate)
{
	uint32_t refdiv = 1, fbdiv = vco_rate / XTAL_FREQ / refdiv;
	uint32_t val;

	crm_divmux_bypass_cmnpll(true);

	crm_rmw(PLL_CMN_CFG1, 0, PLL_CMN_PD);
	crm_writel(CFG_LOAD, CFG_LOAD_CMN_PLL);
	crm_writel(CFG_LOAD, 0);

	while ((crm_readl(PLL_CMN_LOCK) & 1))
		cpu_relax();

	val = FIELD_PREP(PLL_CMN_FBDIV, fbdiv) |
	      FIELD_PREP(PLL_CMN_POSTDIV1, 2) |
	      FIELD_PREP(PLL_CMN_POSTDIV2, 1) |
	      FIELD_PREP(PLL_CMN_REFDIV, refdiv);

	crm_writel(PLL_CMN_CFG1, val);
	crm_writel(CFG_LOAD, CFG_LOAD_CMN_PLL);
	crm_writel(CFG_LOAD, 0);

	while (!(crm_readl(PLL_CMN_LOCK) & 1))
		cpu_relax();

	crm_divmux_bypass_cmnpll(false);
}

void sf21_crm_setup_cmn_and_postdiv()
{
	unsigned long vco_rate = CPU_CLK * 2ul;
	crm_setup_dividers(vco_rate, 2);
	crm_setup_cmnpll(vco_rate);
}

unsigned long sf21_uart_ref_rate()
{
	unsigned long vco_rate = crm_cmnpll_vco_rate();
	unsigned long postdiv_rate = crm_cmnpll_postdiv_rate(vco_rate);
	return crm_div_rate(CLK_UART, cmnpll_div_clks[CLK_UART].use_vco ?
					      vco_rate :
					      postdiv_rate);
}

unsigned long sf21_cpu_rate()
{
	unsigned long vco_rate = crm_cmnpll_vco_rate();
	unsigned long postdiv_rate = crm_cmnpll_postdiv_rate(vco_rate);
	return crm_div_rate(CLK_CPU, cmnpll_div_clks[CLK_CPU].use_vco ?
					     vco_rate :
					     postdiv_rate);
}

void sf21_clk_dump_rates()
{
	unsigned long vco_rate = crm_cmnpll_vco_rate();
	unsigned long postdiv_rate = crm_cmnpll_postdiv_rate(vco_rate);
	unsigned long rate;
	int i;
	printf("CMN_PLL_VCO: %lu\n", vco_rate);
	printf("CMN_PLL_POSTDIV: %lu\n", postdiv_rate);
	for (i = 0; cmnpll_div_clks[i].name; i++) {
		rate = crm_div_rate(i, cmnpll_div_clks[i].use_vco ?
					       vco_rate :
					       postdiv_rate);
		printf("clk %s: real: %lu, target: %lu\n",
		       cmnpll_div_clks[i].name, rate, cmnpll_div_clks[i].rate);
	}
}
