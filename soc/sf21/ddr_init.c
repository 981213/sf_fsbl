#include <stdiol.h>
#include <asm/io.h>
#include <ram.h>
#ifdef DRAM_DDR4
#include "ddr4_phyconfig.h"
#else
#include "ddr3_phyconfig.h"
#endif
#include "ddr_regs.h"
#include <flash.h>
#include "reg.h"
#include <string.h>

static unsigned long dram_size;

static int min(int x, int y)
{
	return x < y ? x : y;
}

static int max(int x, int y)
{
	return x > y ? x : y;
}

int freq(int x,int y)
{
	if(x == 1)
		return (0x2000+y);
	else
		return (0x3000+y);
}

int ddr_pow(int count)
{
	int i;
	int ret = 1;

	if(count == 0)
		return 1;
	for(i = 0 ;i < count;i++)
		ret = 2*ret;

	return ret;
}

int gen_all_1_data(u32 width)
{
	int i;
	u32 data = 0x0;
	for(i = 0;i < width;i++) {
		data = data | (1 << i);
	}
	return data;
}

#define TOP_CRM_RSTEN_CFG_REG_ADDR	(TOPCRM_BASE+0xc0)
#define TOP_CRM_CLKEN_CFG_REG_ADDR	(TOPCRM_BASE+0x8c)
#define TOP_CRM_CLK_SEL0_REG_ADDR	(TOPCRM_BASE+0x80)
#define TOP_CRM_CLK_SEL1_REG_ADDR	(TOPCRM_BASE+0x84)
#define TOP_CRM_PLL_CMN_CFG1_REG_ADDR	(TOPCRM_BASE+0x00)
#define TOP_CRM_PLL_LOCK1_REG_ADDR	(TOPCRM_BASE+0xc8)
#define TOP_CRM_LOAD_REG_ADDR		(TOPCRM_BASE+0x100)
#define LOAD_CFG_PLL_CMN_PARA_LOAD_FIELD_OFFSET	1
#define PLL_LOCK1_PLL_CMN_LOCK_FIELD_OFFSET	0
#define PLL_LOCK1_PLL_CMN_LOCK_FIELD_SIZE	1

#define sf_wr_reg(addr, data)  writel(data, addr)

void sf_wait_reg(u32 addr, u32 offset, u32 width, u32 value)
{
	u32 data;
	u32 tmp = gen_all_1_data(width);
	u32 cnt = 0;

	while(1) {
		data = readl(addr);
		cnt++;
		if ((data & (tmp << offset)) == (value << offset))
			break;
		if (cnt > 10000) {
			printf("wait reg timeout , addr is 0x%x!\n ", addr);
                        break;
                }
	}
}

static void ddr_sys_default(void) {
	u32 reg;

	reg = readl(TOP_CRM_CLKEN_CFG_REG_ADDR);
	reg |= (3 << 9);
	writel(reg, TOP_CRM_CLKEN_CFG_REG_ADDR);
}

void sf_update_reg(u32 addr, u32 offset, u32 width, u32 value)
{
	u32 data;
	u32 new_data;
	u32 tmp = gen_all_1_data(width);

	data = readl(addr);
	new_data = (data & ~(tmp << offset)) | (value << offset);
	writel(new_data, addr);
}

#define RSTEN_CFG_DDR_CTL_SW_RST_N_FIELD_OFFSET 	8
#define RSTEN_CFG_DDR_CTL_SW_RST_N_FIELD_SIZE		1
#define RSTEN_CFG_DDR_CTL_SW_APB_RST_N_FIELD_OFFSET	11
#define RSTEN_CFG_DDR_CTL_SW_APB_RST_N_FIELD_SIZE	1
#define RSTEN_CFG_DDR_PHY_SW_APB_RST_N_FIELD_OFFSET	12
#define RSTEN_CFG_DDR_PHY_SW_APB_RST_N_FIELD_SIZE	1
#define RSTEN_CFG_DDR_PHY_SW_RST_N_FIELD_OFFSET		9
#define RSTEN_CFG_DDR_PHY_SW_RST_N_FIELD_SIZE		1
#define RSTEN_CFG_DDR_SW_PWR_OK_IN_FIELD_OFFSET		10
#define RSTEN_CFG_DDR_SW_PWR_OK_IN_FIELD_SIZE		1

void assert_core_ddrc_rstn(void) {
	sf_update_reg(TOP_CRM_RSTEN_CFG_REG_ADDR, RSTEN_CFG_DDR_CTL_SW_RST_N_FIELD_OFFSET, RSTEN_CFG_DDR_CTL_SW_RST_N_FIELD_SIZE, 0);
}

void assert_apb_ddrc_rstn(void) {
	sf_update_reg(TOP_CRM_RSTEN_CFG_REG_ADDR, RSTEN_CFG_DDR_CTL_SW_APB_RST_N_FIELD_OFFSET, RSTEN_CFG_DDR_CTL_SW_APB_RST_N_FIELD_SIZE, 0);
}

void assert_apb_ddrp_rstn(void) {
	sf_update_reg(TOP_CRM_RSTEN_CFG_REG_ADDR, RSTEN_CFG_DDR_PHY_SW_APB_RST_N_FIELD_OFFSET, RSTEN_CFG_DDR_PHY_SW_APB_RST_N_FIELD_SIZE, 0);
}

void assert_ddrp_rstn(void) {
	sf_update_reg(TOP_CRM_RSTEN_CFG_REG_ADDR, RSTEN_CFG_DDR_PHY_SW_RST_N_FIELD_OFFSET, RSTEN_CFG_DDR_PHY_SW_RST_N_FIELD_SIZE, 0);
}

void deassert_apb_ddrc_rstn(void) {
	sf_update_reg(TOP_CRM_RSTEN_CFG_REG_ADDR, RSTEN_CFG_DDR_CTL_SW_APB_RST_N_FIELD_OFFSET, RSTEN_CFG_DDR_CTL_SW_APB_RST_N_FIELD_SIZE, 1);
}

void deassert_apb_ddrp_rstn(void) {
	sf_update_reg(TOP_CRM_RSTEN_CFG_REG_ADDR, RSTEN_CFG_DDR_PHY_SW_APB_RST_N_FIELD_OFFSET, RSTEN_CFG_DDR_PHY_SW_APB_RST_N_FIELD_SIZE, 1);
}

void deassert_ddrp_rstn(void) {
	sf_update_reg(TOP_CRM_RSTEN_CFG_REG_ADDR, RSTEN_CFG_DDR_PHY_SW_RST_N_FIELD_OFFSET, RSTEN_CFG_DDR_PHY_SW_RST_N_FIELD_SIZE, 1);
}

void set_PwrOKIn(int val) {
	sf_update_reg(TOP_CRM_RSTEN_CFG_REG_ADDR, RSTEN_CFG_DDR_SW_PWR_OK_IN_FIELD_OFFSET, RSTEN_CFG_DDR_SW_PWR_OK_IN_FIELD_SIZE, val);
}

void deassert_core_ddrc_rstn(void) {
	sf_update_reg(TOP_CRM_RSTEN_CFG_REG_ADDR, RSTEN_CFG_DDR_CTL_SW_RST_N_FIELD_OFFSET, RSTEN_CFG_DDR_CTL_SW_RST_N_FIELD_SIZE, 1);

}

static struct ddr_timing ddr4_1600Mbps = {
#undef Tck
#define Tck 1250
        .tck = Tck,

	.cl = 10,
	.al = 0,
	.cwl = 9,

	.trefi = ns_to_tck(7800),
	.tfaw = DMAX((u32)20, ns_to_tck(25)),//28tck
	.trc = ps_to_tck(48750),
	.twr = ns_to_tck(15),
	.trfc = ns_to_tck(160),
	.trcd = ps_to_tck(13750),
	.trp = ps_to_tck(13750),
	.tras_min = ns_to_tck(35),
	.tras = ps_to_tck(70200),
	.twlo = ps_to_tck(9500),
	.twlmrd = 40,
	.tmrd = 8,
	.tmod = DMAX((u32)24, ns_to_tck(15)),
	.tccd = 4,
	.tccd_s = 4,
	.tdllk = 597,
	.txsdll = 597,
	.tzqinit = 1024,
	.tzqoper = 512,
	.tzqcs = 128,
	.txp = DMAX((u32)4, ps_to_tck(6000)),
	.tcksre = DMAX((u32)5, ns_to_tck(10)),
	.tcksrx = DMAX((u32)5, ns_to_tck(10)),
	.trrd = DMAX((u32)4, ps_to_tck(6000)),
	.trrd_s = DMAX((u32)4, ps_to_tck(5000)),
	.tcke = DMAX((u32)3, ps_to_tck(5000)),
	.twtr = DMAX((u32)4, ps_to_tck(7500)),
	.trtp = DMAX((u32)4, ps_to_tck(7500)),
	.txs_abort = ns_to_tck(120),
	.txs_fast = ns_to_tck(120),
	.twtr_s = ns_to_tck(2),
        .pl = 0,
        .tmpx_lh = ns_to_tck(12),
	//tls 115ps tlh 140ps
        .tmpx_s = ps_to_tck(255),
        .tcmdcke = 0,
        .tmrd_pda = DMAX((u32)16, ns_to_tck(10)),
        .tescke = 0,
};

static struct ddr_timing ddr4_2133Mbps = {
#undef Tck
#define Tck 938
        .tck = Tck,

	.cl = 14,
	.al = 0,
	.cwl = 11,

	.trefi = ns_to_tck(7800),
	.tfaw = DMAX((u32)28, ns_to_tck(30)),
	.trc = ps_to_tck(47060),
	.twr = ns_to_tck(15),
	.trfc = ns_to_tck(160),
	.trcd = ps_to_tck(14060),
	.trp = ps_to_tck(14060),
	.tras_min = ns_to_tck(33),
	.tras = ps_to_tck(70200),
	.twlo = ps_to_tck(9500),
	.twlmrd = 40,
	.tmrd = 8,
	.tmod = DMAX((u32)24, ns_to_tck(15)),
	.tccd = DMAX((u32)5, ps_to_tck(5355)),
	.tccd_s = 4,
	.tdllk = 768,
	.txsdll = 768,
	.tzqinit = 1024,
	.tzqoper = 512,
	.tzqcs = 128,
	.txp = DMAX((u32)4, ps_to_tck(6000)),
	.tcksre = DMAX((u32)5, ns_to_tck(10)),
	.tcksrx = DMAX((u32)5, ns_to_tck(10)),
	.trrd = DMAX((u32)4, ps_to_tck(5300)),
	.trrd_s = DMAX((u32)4, ps_to_tck(3700)),
	.tcke = DMAX((u32)3, ps_to_tck(5000)),
	.twtr = DMAX((u32)4, ps_to_tck(7500)),
	.trtp = DMAX((u32)4, ps_to_tck(7500)),
        //need to make sure
	.txs_abort = ns_to_tck(120),
	.txs_fast = ns_to_tck(120),
	.twtr_s = DMAX((u32)2, ps_to_tck(2500)),
        .pl = 0,
        .tmpx_lh = ns_to_tck(12),		//TBD???
	//tls 80ps tlh 105ps			//TBD???
        .tmpx_s = ps_to_tck(185),
        .tcmdcke = 0,
        .tmrd_pda = DMAX((u32)16, ns_to_tck(10)),
        .tescke = 0,
};

static struct ddr_timing ddr4_2400Mbps = {
#undef Tck
#define Tck 833
        .tck = Tck,

	.cl = 15,
	.al = 0,
	.cwl = 12,

	.trefi = ns_to_tck(7800),
	.tfaw = DMAX((u32)28, ns_to_tck(30)),
	.trc = ps_to_tck(44500),
	.twr = ns_to_tck(15),
	.trfc = ns_to_tck(160),
	.trcd = ps_to_tck(12500),
	.trp = ps_to_tck(12500),
	.tras_min = ns_to_tck(32),
	.tras = ps_to_tck(70200),
	.twlo = ps_to_tck(9500),
	.twlmrd = 40,
	.tmrd = 8,
	.tmod = DMAX((u32)24, ns_to_tck(15)),
	.tccd = DMAX((u32)5, ns_to_tck(5)),
	.tccd_s = 4,
	.tdllk = 768,
	.txsdll = 768,
	.tzqinit = 1024,
	.tzqoper = 512,
	.tzqcs = 128,
	.txp = DMAX((u32)4, ps_to_tck(6000)),
	.tcksre = DMAX((u32)5, ns_to_tck(10)),
	.tcksrx = DMAX((u32)5, ns_to_tck(10)),
	.trrd = DMAX((u32)4, ps_to_tck(6400)),
	.trrd_s = DMAX((u32)4, ps_to_tck(3300)),
	.tcke = DMAX((u32)3, ps_to_tck(5000)),
	.twtr = DMAX((u32)4, ps_to_tck(7500)),
	.trtp = DMAX((u32)4, ps_to_tck(7500)),
	.txs_abort = ns_to_tck(120),
	.txs_fast = ns_to_tck(120),
	.twtr_s = DMAX((u32)3, ps_to_tck(2500)),
        .pl = 0,
        .tmpx_lh = ns_to_tck(12),
	//tls 62ps tlh 87ps
        .tmpx_s = ps_to_tck(149),
        .tcmdcke = 0,
        .tmrd_pda = DMAX((u32)16, ns_to_tck(10)),
        .tescke = 0,
};

static struct ddr_timing ddr4_2666Mbps = {
#undef Tck
#define Tck 750
        .tck = Tck,

	.cl = 19,
	.al = 0,
	.cwl = 18,

	.trefi = ns_to_tck(7800),
	.tfaw = DMAX((u32)28, ns_to_tck(30)),
	.trc = ps_to_tck(46250), //min 46250
	.twr = ns_to_tck(15),
	.trfc = ns_to_tck(260), //4G trfc1:260 trfc2:160 trfc4:110
	.trcd = ps_to_tck(14250), //min 14250
	.trp = ps_to_tck(14250), //min 14250
	.tras_min = ns_to_tck(32),
	.tras = ps_to_tck(70200), // 9 x trefi
	.twlo = ps_to_tck(9500), //min:0 max:9500
	.twlmrd = 40, //min 40
	.tmrd = 8, //min 8
	.tmod = DMAX((u32)24, ns_to_tck(15)),
	.tccd = DMAX((u32)5, ns_to_tck(5)),
	.tccd_s = 4,
	.tdllk = 854, // 9 x trefi
	.txsdll = 854, // 9 x trefi
	.tzqinit = 1024,
	.tzqoper = 512,
	.tzqcs = 128,
	.txp = DMAX((u32)4, ps_to_tck(6000)),
	.tcksre = DMAX((u32)5, ns_to_tck(10)),
	.tcksrx = DMAX((u32)5, ns_to_tck(10)),
	.trrd = DMAX((u32)4, ps_to_tck(6400)), //trrd_l(2k)
	.trrd_s = DMAX((u32)4, ps_to_tck(5300)), //trrd_s(2k)
	.tcke = DMAX((u32)3, ps_to_tck(5000)),
	.twtr = DMAX((u32)4, ps_to_tck(7500)), //twtr_l(2k)
	.trtp = DMAX((u32)4, ps_to_tck(7500)),
	.txs_abort = ns_to_tck(120), //min 120
	.txs_fast = ns_to_tck(120), //min 120
	.twtr_s = DMAX((u32)2, ps_to_tck(2500)),
        .pl = 5,
        .tmpx_lh = ns_to_tck(12), //min 12
		// tls 55ps tlh 80ps
        .tmpx_s = ps_to_tck(135),
        .tcmdcke = 0,
        .tmrd_pda = DMAX((u32)16, ns_to_tck(10)),
        .tescke = 0,
};

static struct ddr_timing ddr4_3200Mbps = {
#undef Tck
#define Tck 625
        .tck = Tck,

	.cl = 24,
	.al = 0,
	.cwl = 20,

	.trefi = ns_to_tck(7800),
	.tfaw = DMAX((u32)28, ns_to_tck(30)),
	.trc = ps_to_tck(45750),
	.twr = ns_to_tck(15),
	.trfc = ns_to_tck(160),
	.trcd = ps_to_tck(13750),
	.trp = ps_to_tck(13750),
	.tras_min = ns_to_tck(32),
	.tras = ps_to_tck(70200),
	.twlo = ps_to_tck(9500),
	.twlmrd = 40,
	.tmrd = 8,
	.tmod = DMAX((u32)24, ns_to_tck(15)),
	.tccd = DMAX((u32)5, ns_to_tck(5)),
	.tccd_s = 4,
	.tdllk = 1024,
	.txsdll = 1024,
	.tzqinit = 1024,
	.tzqoper = 512,
	.tzqcs = 128,
	.txp = DMAX((u32)4, ps_to_tck(6000)),
	.tcksre = DMAX((u32)5, ns_to_tck(10)),
	.tcksrx = DMAX((u32)5, ns_to_tck(10)),
	.trrd = DMAX((u32)4, ps_to_tck(6400)),
	.trrd_s = DMAX((u32)4, ps_to_tck(5300)),
	.tcke = DMAX((u32)3, ps_to_tck(5000)),
	.twtr = DMAX((u32)4, ps_to_tck(7500)),
	.trtp = DMAX((u32)4, ps_to_tck(7500)),
	.txs_abort = ns_to_tck(120),
	.txs_fast = ns_to_tck(120),
	.twtr_s = DMAX((u32)2, ps_to_tck(2500)),
        .pl = 0,
        .tmpx_lh = ns_to_tck(12),		//TBD???
	//tls 62ps tlh 87ps			//TBD???
        .tmpx_s = ps_to_tck(149),
        .tcmdcke = 0,
        .tmrd_pda = DMAX((u32)16, ns_to_tck(10)),
        .tescke = 0,
};

static struct ddr_timing ddr3_2133Mbps = {
#undef Tck
#define Tck 938
        .tck = Tck,

	.cl = 11,
	.al = 0,
	.cwl = 10,

	.trefi = ns_to_tck(7800),
	.tfaw = ns_to_tck(35),//28tck
	.trc = ps_to_tck(44700),
	.twr = ns_to_tck(15),
//	.trfc = ns_to_tck(110),
	.trfc = ns_to_tck(260),
	.trcd = ps_to_tck(10700),
	.trp = ps_to_tck(10700),
	.tras_min = ns_to_tck(34),
	.tras = ps_to_tck(57500),
	.twlo = ps_to_tck(7500),
	.twlmrd = 40,
	.tmrd = 4,
	.tmod = DMAX((u32)12, ns_to_tck(15)),
	.tccd = 4,
	.tdllk = 512,
	.txsdll = 512,
	.tzqinit = DMAX((u32)512, ns_to_tck(640)),
	.tzqoper = DMAX((u32)256, ns_to_tck(320)),
	.tzqcs = DMAX((u32)64, ns_to_tck(80)),
	.txpdll = DMAX((u32)10, ns_to_tck(24)),
	.txp = DMAX((u32)3, ps_to_tck(6000)),
	.tcksre = DMAX((u32)5, ns_to_tck(10)),
	.tcksrx = DMAX((u32)5, ns_to_tck(10)),
	.trrd = DMAX((u32)4, ps_to_tck(6000)),
	.tcke = DMAX((u32)3, ps_to_tck(5000)),
	.twtr = DMAX((u32)4, ps_to_tck(7500)),
	.trtp = DMAX((u32)4, ps_to_tck(7500)),
};

static struct ddr_timing ddr3_1600Mbps = {
#undef Tck
#define Tck 1250
        .tck = Tck,

	.cl = 10,
	.al = 0,
	.cwl = 8,

	.trefi = ns_to_tck(7800),
	.tfaw = ns_to_tck(40),//28tck
	.trc = ps_to_tck(48750),
	.twr = ns_to_tck(15),
	.trfc = ns_to_tck(110),
	.trcd = ps_to_tck(13750),
	.trp = ps_to_tck(13750),
	.tras_min = ns_to_tck(35),
	.tras = ps_to_tck(57500),
	.twlo = ps_to_tck(7500),
	.twlmrd = 40,
	.tmrd = 4,
	.tmod = DMAX((u32)12, ns_to_tck(15)),
	.tccd = 4,
	.tdllk = 512,
	.txsdll = 512,
	.tzqinit = DMAX((u32)512, ns_to_tck(640)),
	.tzqoper = DMAX((u32)256, ns_to_tck(320)),
	.tzqcs = DMAX((u32)64, ns_to_tck(80)),
	.txpdll = DMAX((u32)10, ns_to_tck(24)),
	.txp = DMAX((u32)3, ps_to_tck(6000)),
	.tcksre = DMAX((u32)5, ns_to_tck(10)),
	.tcksrx = DMAX((u32)5, ns_to_tck(10)),
	.trrd = DMAX((u32)4, ps_to_tck(7500)),
	.tcke = DMAX((u32)3, ps_to_tck(5000)),
	.twtr = DMAX((u32)4, ps_to_tck(7500)),
	.trtp = DMAX((u32)4, ps_to_tck(7500)),
};

static struct ddr_timing ddr3_1066Mbps = {
#undef Tck
#define Tck 1875
        .tck = Tck,

	.cl = 7,
	.al = 0,
	.cwl = 6,

	.trefi = ns_to_tck(7800),
	.tfaw = ns_to_tck(50),
	.trc = ps_to_tck(50625),
	.twr = ns_to_tck(15),
	.trfc = ns_to_tck(110),
	.trcd = ps_to_tck(13125),
	.trp = ps_to_tck(13125),
	.tras_min = ns_to_tck(38),
	.tras = ps_to_tck(57500),
	.twlo = ns_to_tck(9),
	.twlmrd = 40,
	.tmrd = 4,
	.tmod = DMAX((u32)12, ns_to_tck(15)),
	.tccd = 4,
	.tdllk = 512,
	.txsdll = 512,
	.tzqinit = DMAX((u32)512, ns_to_tck(640)),
	.tzqoper = DMAX((u32)256, ns_to_tck(320)),
	.tzqcs = DMAX((u32)64, ns_to_tck(80)),
	.txpdll = DMAX((u32)10, ns_to_tck(24)),
	.txp = DMAX((u32)3, ps_to_tck(7500)),
	.tcksre = DMAX((u32)5, ns_to_tck(10)),
	.tcksrx = DMAX((u32)5, ns_to_tck(10)),
	.trrd = DMAX((u32)4, ps_to_tck(10000)),
	.tcke = DMAX((u32)3, ps_to_tck(5625)),
	.twtr = DMAX((u32)4, ps_to_tck(7500)),
	.trtp = DMAX((u32)4, ps_to_tck(7500)),
};

static struct ddr_timing ddr3_800Mbps = {
#undef Tck
#define Tck 2500
        .tck = Tck,

	.cl = 6,
	.al = 0,
	.cwl = 5,

	.trefi = ns_to_tck(7800),
	.tfaw = ns_to_tck(50),
	.trc = ps_to_tck(52500),
	.twr = ns_to_tck(15),
	.trfc = ns_to_tck(110),
	.trcd = ps_to_tck(15000),
	.trp = ps_to_tck(15000),
	.tras_min = ns_to_tck(38),
	.tras = ps_to_tck(57500),
	.twlo = ns_to_tck(9),
	.twlmrd = 40,
	.tmrd = 4,
	.tmod = DMAX((u32)12, ns_to_tck(15)),
	.tccd = 4,
	.tdllk = 512,
	.txsdll = 512,
	.tzqinit = DMAX((u32)512, ns_to_tck(640)),
	.tzqoper = DMAX((u32)256, ns_to_tck(320)),
	.tzqcs = DMAX((u32)64, ns_to_tck(80)),
	.txpdll = DMAX((u32)10, ns_to_tck(24)),
	.txp = DMAX((u32)3, ps_to_tck(7500)),
	.tcksre = DMAX((u32)5, ns_to_tck(10)),
	.tcksrx = DMAX((u32)5, ns_to_tck(10)),
	.trrd = DMAX((u32)4, ps_to_tck(10000)),
	.tcke = DMAX((u32)3, ps_to_tck(7500)),
	.twtr = DMAX((u32)4, ps_to_tck(7500)),
	.trtp = DMAX((u32)4, ps_to_tck(7500)),
};

void ddr3_set_timing(struct ddr_info *ddr)
{
	struct ddr_timing *t;
	switch (ddr->freq) {
	case 400:
		ddr->timing = &ddr3_800Mbps;
		break;
	case 533:
		ddr->timing = &ddr3_1066Mbps;
		break;
	case 800:
		ddr->timing = &ddr3_1600Mbps;
		break;
	case 1066:
		ddr->timing = &ddr3_2133Mbps;
		break;
        default:
		printf("ERROR: DDR freq %dMHz not support!!!\n", ddr->freq);
		ddr->freq = 800;
		printf("Use default value %dMHz!!!\n", ddr->freq);
                ddr->timing = &ddr3_1600Mbps;
	}
	printf("Now DDR3 frequency is: %dMHz!!!\n",ddr->freq);
	t = ddr->timing;
#undef Tck
#define Tck (t->tck)
        switch (ddr->size) {
        case 512:
                t->trfc = ns_to_tck(90);
                break;
        case 1024:
                t->trfc = ns_to_tck(110);
                break;
        case 2048:
                t->trfc = ns_to_tck(160);
                break;
        case 4096:
                t->trfc = ns_to_tck(260);
                break;
        default:
                t->trfc = ns_to_tck(350);
                break;
        }

	t->wl = t->al + t->cwl;
	t->rl = t->al + t->cl;
	t->tckesr = t->tcke + 1;
	t->tras = t->tras_min;
	t->tras_max = 9 * t->trefi;
	t->txs = DMAX((u32)5, ns_to_tck(10) + t->trfc);
        t->txpr = DMAX((u32)5, ns_to_tck(10) + t->trfc);
}

void ddr4_set_timing(struct ddr_info *ddr)
{
	struct ddr_timing *t;
	int ddr_cc;
	switch (ddr->freq) {
	case 800:
		ddr->timing = &ddr4_1600Mbps;
		break;
	case 1066:
		ddr->timing = &ddr4_2133Mbps;
		break;
	case 1200:
		ddr->timing = &ddr4_2400Mbps;
		break;
	case 1333:
		ddr->timing = &ddr4_2666Mbps;
		break;
	case 1600:
		ddr->timing = &ddr4_3200Mbps;
		break;
        default:
		printf("ERROR: DDR freq %dMHz not support!!!\n", ddr->freq);
		ddr->freq = 800;
		printf("Use default value %dMHz!!!\n", ddr->freq);
                ddr->timing = &ddr4_1600Mbps;
	}
	printf("Now DDR4 frequency is: %dMHz!!!\n",ddr->freq);
	t = ddr->timing;
#undef Tck
#define Tck (t->tck)
	ddr_cc = ddr->size / 1024;
	if(ddr->refresh_mode == 1)
		ddr_cc /= 2;
	else if(ddr->refresh_mode == 2)
		ddr_cc /= 4;

	switch (ddr_cc) {
	case 0:
		t->trfc = ns_to_tck(90);
		break;
	case 1:
		t->trfc = ns_to_tck(110);
		break;
	case 2:
		t->trfc = ns_to_tck(160);
		break;
	case 4:
		t->trfc = ns_to_tck(260);
		break;
	case 8:
		t->trfc = ns_to_tck(350);
		break;
	default:
		t->trfc = ns_to_tck(550);
		break;
	}

	t->wl = t->al + t->cwl;
	t->rl = t->al + t->cl;
	t->tckesr = t->tcke + 1;
	t->tras = t->tras_min;
	t->tras_max = 9 * t->trefi;
	t->txs = DMAX((u32)5, ns_to_tck(10) + t->trfc);
	t->txpr = DMAX((u32)5, ns_to_tck(10) + t->trfc);
	t->txmpdll = (t->txs + t->txsdll);
	t->tckmpe = t->tmod + 4;
	t->twr_mpr = t->tmod + t->al + t->pl;
}

static int phy_init(unsigned long ddr_fw_offset, unsigned char *ddr_fw_sha256)
{
	int i;
	int PllCtrl2;
	int ARdPtrInitVal;
	int ProcOdtTimeCtl;
	int ODTStrenP_state,ODTStrenN_state,TxOdtDrvStren;
	int DrvStrenFSDqP_state,DrvStrenFSDqN_state,TxImpedanceCtrl1;
	int ADrvStrenP_state,ADrvStrenN_state,ATxImpedance;
	int CalDrvStrPu50,CalDrvStr0;
	int CalUClkTicksPer1uS;
	int vref_percentVddq,GlobalVrefInDAC,GlobalVrefInSel;
	int VrefInGlobal,DqDqsRcvCntrl;
	uint16_t psCount[4];
	int delayScale = 1;
	int DfiFrq;
	int LowFreqOpt = 0;
	int TwoTckRxDqsPre;
	int dllLock;
	int TxPreDrvMode;
	int tmp;
	u8 buff1[1024];
	u8 fw_hash[32];
	u32 buf_i, buf_len;
	int read_len = 0;

//	dwc_ddrphy_phyinit_setDefault(0);

	dwc_ddrphy_phyinit_userCustom_overrideUserInput();

	dwc_ddrphy_phyinit_userCustom_A_bringupPower();

	dwc_ddrphy_phyinit_userCustom_B_startClockResetPhy();
#ifdef DRAM_DDR4
	TxPreDrvMode = 2;
#else
	TxPreDrvMode = 3;
#endif
	//userInputAdvanced.TxSlewRiseDQ 4
	//userInputAdvanced.TxSlewFallDQ 4
	tmp = (0x44 | (TxPreDrvMode << 8));
	dwc_ddrphy_apb_wr(0x1005f,tmp);
	dwc_ddrphy_apb_wr(0x1015f,tmp);
	dwc_ddrphy_apb_wr(0x1105f,tmp);
	dwc_ddrphy_apb_wr(0x1115f,tmp);

	//userInputAdvanced.TxSlewRiseAC 4
	//userInputAdvanced.TxSlewFallAC 4
	dwc_ddrphy_apb_wr(0x0055,0x344);
	dwc_ddrphy_apb_wr(0x1055,0x344);
	dwc_ddrphy_apb_wr(0x2055,0x344);
	dwc_ddrphy_apb_wr(0x3055,0x344);
	dwc_ddrphy_apb_wr(0x4055,0x44);
	dwc_ddrphy_apb_wr(0x5055,0x44);
	dwc_ddrphy_apb_wr(0x6055,0x344);
	dwc_ddrphy_apb_wr(0x7055,0x344);
	dwc_ddrphy_apb_wr(0x8055,0x344);
	dwc_ddrphy_apb_wr(0x9055,0x344);

	//relate freq
        if (userInputBasic.Frequency[0]/2 < 235) {
                PllCtrl2 = 0x7;
        }
        else if(userInputBasic.Frequency[0]/2 < 313) {
                PllCtrl2 = 0x6;
        }
        else if(userInputBasic.Frequency[0]/2 < 469) {
                PllCtrl2 = 0xb;
        }
        else if(userInputBasic.Frequency[0]/2 < 625) {
                PllCtrl2 = 0xa;
        }
        else if(userInputBasic.Frequency[0]/2 < 938) {
                PllCtrl2 = 0x19;
        }
        else if(userInputBasic.Frequency[0]/2 < 1067) {
                PllCtrl2 = 0x18;
        }
        else {
                PllCtrl2 = 0x19;
        }
	dwc_ddrphy_apb_wr(0x200c5,PllCtrl2);

        if (userInputBasic.Frequency[0] >= 933) {
                ARdPtrInitVal = 0x2;
        }
        else {
                ARdPtrInitVal = 0x1;
        }
        // Add one UI for synchronizer on SyncBus when PLL is bypassed
        if (userInputBasic.PllBypass[0] == 1) {
                ARdPtrInitVal ++;
        }
	dwc_ddrphy_apb_wr(0x2002e,ARdPtrInitVal);
#ifdef DRAM_DDR4
	dwc_ddrphy_apb_wr(0x20024,0x8);
	dwc_ddrphy_apb_wr(0x2003a,0x2);
#else
	dwc_ddrphy_apb_wr(0x20024,0x0);
	dwc_ddrphy_apb_wr(0x2003a,0x0);
#endif
	dwc_ddrphy_apb_wr(0x2007d,0x212);
	dwc_ddrphy_apb_wr(0x2007c,0x61);

	TwoTckRxDqsPre  = userInputAdvanced.D4RxPreambleLength[0];
	//relate freq
     //   if (userInputAdvanced.WDQSExt) {
     //     ProcOdtTimeCtl = 0x3;
     //   }
        // Memclk Freq <= 933MHz
     //   else if (userInputBasic.Frequency[0] <= 933) {
    	if (userInputBasic.Frequency[0] <= 933) {
                ProcOdtTimeCtl = 0xa;
        }
        // 933MHz < Memclk Freq <= 1200MHz
        else if (userInputBasic.Frequency[0] <= 1200) {
                if (TwoTckRxDqsPre == 1) {
                        ProcOdtTimeCtl = 0x2;
                }
                else {
                        ProcOdtTimeCtl = 0x6;
                }
        }
        // Memclk Freq > 1200MHz
        else {
                if (TwoTckRxDqsPre == 1) {
                        ProcOdtTimeCtl = 0x3;
                }
                else {
                        ProcOdtTimeCtl = 0x7;
                }
        }
	dwc_ddrphy_apb_wr(0x20056,ProcOdtTimeCtl);

	//input ODTImpedance
	//ODT 60 TX 60
	ODTStrenP_state = dwc_ddrphy_phyinit_mapDrvStren((int)userInputAdvanced.ODTImpedance[0], ODTStrenP, userInputBasic.HardMacroVer);
	ODTStrenN_state = dwc_ddrphy_phyinit_mapDrvStren((int)userInputAdvanced.ODTImpedance[0], ODTStrenN, userInputBasic.HardMacroVer);
	TxOdtDrvStren = (ODTStrenN_state << 6) | ODTStrenP_state;
	dwc_ddrphy_apb_wr(0x1004d,TxOdtDrvStren);
	dwc_ddrphy_apb_wr(0x1014d,TxOdtDrvStren);
	dwc_ddrphy_apb_wr(0x1104d,TxOdtDrvStren);
	dwc_ddrphy_apb_wr(0x1114d,TxOdtDrvStren);

	DrvStrenFSDqP_state = dwc_ddrphy_phyinit_mapDrvStren((int)userInputAdvanced.TxImpedance[0], DrvStrenFSDqP, userInputBasic.HardMacroVer);
	DrvStrenFSDqN_state = dwc_ddrphy_phyinit_mapDrvStren((int)userInputAdvanced.TxImpedance[0], DrvStrenFSDqN, userInputBasic.HardMacroVer);
	TxImpedanceCtrl1 = (DrvStrenFSDqN_state << 6) | DrvStrenFSDqP_state;
	dwc_ddrphy_apb_wr(0x10049,TxImpedanceCtrl1);
	dwc_ddrphy_apb_wr(0x10149,TxImpedanceCtrl1);
	dwc_ddrphy_apb_wr(0x11049,TxImpedanceCtrl1);
	dwc_ddrphy_apb_wr(0x11149,TxImpedanceCtrl1);

	//ATx
	ADrvStrenP_state = dwc_ddrphy_phyinit_mapDrvStren((int) userInputAdvanced.ATxImpedance, ADrvStrenP, userInputBasic.HardMacroVer);
	ADrvStrenN_state = dwc_ddrphy_phyinit_mapDrvStren((int) userInputAdvanced.ATxImpedance, ADrvStrenN, userInputBasic.HardMacroVer);
	ATxImpedance = (ADrvStrenN_state << 5) | ADrvStrenP_state;
	dwc_ddrphy_apb_wr(0x0043,ATxImpedance);
	dwc_ddrphy_apb_wr(0x1043,ATxImpedance);
	dwc_ddrphy_apb_wr(0x2043,ATxImpedance);
	dwc_ddrphy_apb_wr(0x3043,ATxImpedance);
	dwc_ddrphy_apb_wr(0x4043,ATxImpedance);
	dwc_ddrphy_apb_wr(0x5043,ATxImpedance);
	dwc_ddrphy_apb_wr(0x6043,ATxImpedance);
	dwc_ddrphy_apb_wr(0x7043,ATxImpedance);
	dwc_ddrphy_apb_wr(0x8043,ATxImpedance);
	dwc_ddrphy_apb_wr(0x9043,ATxImpedance);

	dwc_ddrphy_apb_wr(0x20018,0x1);
#ifdef DRAM_DDR4
	dwc_ddrphy_apb_wr(0x20075,0x2);
#else
	dwc_ddrphy_apb_wr(0x20075,0x0);
#endif

	CalDrvStrPu50 = userInputAdvanced.ExtCalResVal;
	CalDrvStr0 = CalDrvStrPu50 << 4 | CalDrvStrPu50;
	dwc_ddrphy_apb_wr(0x20050,CalDrvStr0);

	CalUClkTicksPer1uS = (userInputBasic.Frequency[0])/2;
	dwc_ddrphy_apb_wr(0x20008,CalUClkTicksPer1uS);

	dwc_ddrphy_apb_wr(0x20088,0x9);
#ifdef DRAM_DDR4
	vref_percentVddq = (mb_DDR4U_1D[0].PhyVref)*1000*100/128;
#else
	vref_percentVddq = (mb_DDR3U_1D[0].PhyVref)*1000*100/128;
#endif
	GlobalVrefInDAC = 0x0;
	GlobalVrefInSel = 0x4;
	GlobalVrefInDAC = (uint8_t)((vref_percentVddq / 500)+1);
	if (GlobalVrefInDAC > 127){
                GlobalVrefInDAC = (uint8_t)(max((vref_percentVddq-34500),500) / 500); // Min value is 1
                GlobalVrefInSel = 0x0;
        }
        GlobalVrefInDAC = min(GlobalVrefInDAC,127);

        VrefInGlobal = (GlobalVrefInDAC << 3) | GlobalVrefInSel;
	dwc_ddrphy_apb_wr(0x200b2,VrefInGlobal);
#ifdef DRAM_DDR4
	DqDqsRcvCntrl = (0xb << 7) | (3 << 4) | (0x1);
#else
	DqDqsRcvCntrl = (0xb << 7) | (0x1);
#endif
	dwc_ddrphy_apb_wr(0x10043,DqDqsRcvCntrl);
	dwc_ddrphy_apb_wr(0x10143,DqDqsRcvCntrl);
	dwc_ddrphy_apb_wr(0x11043,DqDqsRcvCntrl);
	dwc_ddrphy_apb_wr(0x11143,DqDqsRcvCntrl);

	dwc_ddrphy_apb_wr(0x200fa,0x1);

	//2T mode
	dwc_ddrphy_apb_wr(0x20019,0x4);

	dwc_ddrphy_apb_wr(0x200f0,0x5555);
	dwc_ddrphy_apb_wr(0x200f1,0x5555);
	dwc_ddrphy_apb_wr(0x200f2,0x5555);
	dwc_ddrphy_apb_wr(0x200f3,0x5555);
	dwc_ddrphy_apb_wr(0x200f4,0x5555);
	dwc_ddrphy_apb_wr(0x200f5,0x5555);
	dwc_ddrphy_apb_wr(0x200f6,0x5555);
	dwc_ddrphy_apb_wr(0x200f7,0xf000);

	dwc_ddrphy_apb_wr(0x1004a,0x500);
	dwc_ddrphy_apb_wr(0x1104a,0x500);

	dwc_ddrphy_apb_wr(0x20025,0x0);
#ifdef DRAM_DDR4
	dwc_ddrphy_apb_wr(0x2002d,0x0);
#endif
	dwc_ddrphy_apb_wr(0x2002c,0x0);

	dwc_ddrphy_apb_wr(0x20060,0x2);

	dwc_ddrphy_apb_wr(0xd0000,0x0);
	buf_i = 0;
	buf_len = 0;

	for(i = 0; i < 16384; i++)
        {
                if (buf_i >= buf_len) {
			buf_i = 0;
			flash_read(ddr_fw_offset, sizeof(buff1), buff1);
			// sha256_hw_update(&sha_state, buff1, sizeof(buff1), 0);
			buf_len = sizeof(buff1);
			ddr_fw_offset += buf_len;
			read_len += buf_len;
                }
                dwc_ddrphy_apb_wr(0x50000+i, (buff1[buf_i] + (buff1[buf_i+1]<<8)));
		//printf("Wr %d %08x\n", i, (buff1[buf_i] + (buff1[buf_i+1]<<8)));
		buf_i += 2;
        }

	dwc_ddrphy_apb_wr(0xd0000,0x1);
	dwc_ddrphy_phyinit_userCustom_E_setDfiClk(0);

	//dwc_ddrphy_phyinit_WriteOutMem
	dwc_ddrphy_apb_wr(0xd0000,0x0);
	buf_i = 0;
	buf_len = 0;
#ifdef DRAM_DDR4
        for(i = 0; i < 870; i++)
#else
        for(i = 0; i < 868; i++)
#endif
	{
                if (buf_i >= buf_len) {
			buf_i = 0;
			flash_read(ddr_fw_offset, sizeof(buff1), buff1);
			// sha256_hw_update(&sha_state, buff1, sizeof(buff1), 0);
			buf_len = sizeof(buff1);
			ddr_fw_offset += buf_len;
			read_len += buf_len;
                }
                dwc_ddrphy_apb_wr(0x54000+i, (buff1[buf_i] + (buff1[buf_i+1]<<8)));
		buf_i += 2;
        }

	while (read_len < DDR_FW_LEN) {
		flash_read(ddr_fw_offset, sizeof(buff1), buff1);
		// sha256_hw_update(&sha_state, buff1, sizeof(buff1), 0);
		buf_len = sizeof(buff1);
		ddr_fw_offset += buf_len;
		read_len += buf_len;
	}

	// sha256_hw_final(&sha_state, fw_hash);
	// if (memcmp(fw_hash, _ddr_fw_hash, 32)) {
	// 	printf("ddr firmware hash mismatch. Is firmware corrupted?\n");
	// 	for(;;);
	// }

#ifdef DRAM_DDR4
	dwc_ddrphy_apb_wr(0x54000+0, (mb_DDR4U_1D[0].MsgMisc << 8));
	dwc_ddrphy_apb_wr(0x54000+3, userInputBasic.Frequency[0]*2);
	dwc_ddrphy_apb_wr(0x54000+4, userInputBasic.DfiFreqRatio[0]*2);// | (0x78 << 8);
	dwc_ddrphy_apb_wr(0x54000+6, mb_DDR4U_1D[0].PhyVref | (mb_DDR4U_1D[0].DramType << 8));
	dwc_ddrphy_apb_wr(0x54000+7, (mb_DDR4U_1D[0].EnabledDQs << 8));
	dwc_ddrphy_apb_wr(0x54000+8, 0x101);//mb_DDR4U_1D[0].CsPresent;
	dwc_ddrphy_apb_wr(0x54000+9, mb_DDR4U_1D[0].AddrMirror << 8);
	dwc_ddrphy_apb_wr(0x54000+10, mb_DDR4U_1D[0].PhyCfg);
	dwc_ddrphy_apb_wr(0x54000+11, mb_DDR4U_1D[0].SequenceCtrl);
	dwc_ddrphy_apb_wr(0x54000+12, mb_DDR4U_1D[0].HdtCtrl);
	dwc_ddrphy_apb_wr(0x54000+18, mb_DDR4U_1D[0].DFIMRLMargin);
	dwc_ddrphy_apb_wr(0x54000+47, mb_DDR4U_1D[0].MR0);
	dwc_ddrphy_apb_wr(0x54000+48, mb_DDR4U_1D[0].MR1);
	dwc_ddrphy_apb_wr(0x54000+49, mb_DDR4U_1D[0].MR2);
	dwc_ddrphy_apb_wr(0x54000+50, mb_DDR4U_1D[0].MR3);
	dwc_ddrphy_apb_wr(0x54000+51, mb_DDR4U_1D[0].MR4);
	dwc_ddrphy_apb_wr(0x54000+52, mb_DDR4U_1D[0].MR5);
	dwc_ddrphy_apb_wr(0x54000+53, mb_DDR4U_1D[0].MR6);
	dwc_ddrphy_apb_wr(0x54000+55, mb_DDR4U_1D[0].RTT_NOM_WR_PARK0);
#else
	dwc_ddrphy_apb_wr(0x54000+0, (mb_DDR3U_1D[0].MsgMisc << 8));
	dwc_ddrphy_apb_wr(0x54000+3, userInputBasic.Frequency[0]*2);
	dwc_ddrphy_apb_wr(0x54000+4, userInputBasic.DfiFreqRatio[0]*2);// | (0x78 << 8);
	dwc_ddrphy_apb_wr(0x54000+6, mb_DDR3U_1D[0].PhyVref | (mb_DDR3U_1D[0].DramType << 8));
	dwc_ddrphy_apb_wr(0x54000+7, (mb_DDR3U_1D[0].EnabledDQs << 8));
	dwc_ddrphy_apb_wr(0x54000+8, 0x101);//mb_DDR4U_1D[0].CsPresent;
	dwc_ddrphy_apb_wr(0x54000+9, mb_DDR3U_1D[0].AddrMirror << 8);
	dwc_ddrphy_apb_wr(0x54000+10, mb_DDR3U_1D[0].PhyCfg);
	dwc_ddrphy_apb_wr(0x54000+11, mb_DDR3U_1D[0].SequenceCtrl);
	dwc_ddrphy_apb_wr(0x54000+12, mb_DDR3U_1D[0].HdtCtrl);
	dwc_ddrphy_apb_wr(0x54000+18, mb_DDR3U_1D[0].DFIMRLMargin);
	dwc_ddrphy_apb_wr(0x54000+47, mb_DDR3U_1D[0].MR0);
	dwc_ddrphy_apb_wr(0x54000+48, mb_DDR3U_1D[0].MR1);
	dwc_ddrphy_apb_wr(0x54000+49, mb_DDR3U_1D[0].MR2);
#endif
	dwc_ddrphy_apb_wr(0xd0000,0x1);

	//dwc_ddrphy_phyinit_G_execFW
	dwc_ddrphy_apb_wr(0xd0000,0x1);
	dwc_ddrphy_apb_wr(0xd0099,0x9);
	dwc_ddrphy_apb_wr(0xd0099,0x1);
	dwc_ddrphy_apb_wr(0xd0099,0x0);

//	init_streaming_idx_arr();
//	init_streaming_msg_arr();

	tmp = dwc_ddrphy_phyinit_userCustom_G_waitFwDone();
	if(tmp)
		return tmp;
	dwc_ddrphy_apb_wr(0xd0099,0x1);

	//dwc_ddrphy_phyinit_H_readMsgBlock
	dwc_ddrphy_apb_wr(0xd0000,0x0);
	dwc_ddrphy_phyinit_userCustom_H_readMsgBlock(0);
	dwc_ddrphy_apb_wr(0xd0000,0x1);

	//dwc_ddrphy_phyinit_I_loadPIEImage
	dwc_ddrphy_apb_wr(0xd0000,0x0);
	dwc_ddrphy_apb_wr(0x90000,0x10);
	dwc_ddrphy_apb_wr(0x90001,0x400);
	dwc_ddrphy_apb_wr(0x90002,0x10e);
	dwc_ddrphy_apb_wr(0x90003,0x0);
	dwc_ddrphy_apb_wr(0x90004,0x0);
	dwc_ddrphy_apb_wr(0x90005,0x8);
	dwc_ddrphy_apb_wr(0x90029,0xb);
	dwc_ddrphy_apb_wr(0x9002a,0x480);
	dwc_ddrphy_apb_wr(0x9002b,0x109);
	dwc_ddrphy_apb_wr(0x9002c,0x8);
	dwc_ddrphy_apb_wr(0x9002d,0x448);
	dwc_ddrphy_apb_wr(0x9002e,0x139);
	dwc_ddrphy_apb_wr(0x9002f,0x8);
	dwc_ddrphy_apb_wr(0x90030,0x478);
	dwc_ddrphy_apb_wr(0x90031,0x109);
	dwc_ddrphy_apb_wr(0x90032,0x2);
	dwc_ddrphy_apb_wr(0x90033,0x10);
	dwc_ddrphy_apb_wr(0x90034,0x139);
	dwc_ddrphy_apb_wr(0x90035,0xb);
	dwc_ddrphy_apb_wr(0x90036,0x7c0);
	dwc_ddrphy_apb_wr(0x90037,0x139);
	dwc_ddrphy_apb_wr(0x90038,0x44);
	dwc_ddrphy_apb_wr(0x90039,0x633);
	dwc_ddrphy_apb_wr(0x9003a,0x159);
	dwc_ddrphy_apb_wr(0x9003b,0x14f);
	dwc_ddrphy_apb_wr(0x9003c,0x630);
	dwc_ddrphy_apb_wr(0x9003d,0x159);
	dwc_ddrphy_apb_wr(0x9003e,0x47);
	dwc_ddrphy_apb_wr(0x9003f,0x633);
	dwc_ddrphy_apb_wr(0x90040,0x149);
	dwc_ddrphy_apb_wr(0x90041,0x4f);
	dwc_ddrphy_apb_wr(0x90042,0x633);
	dwc_ddrphy_apb_wr(0x90043,0x179);
	dwc_ddrphy_apb_wr(0x90044,0x8);
	dwc_ddrphy_apb_wr(0x90045,0xe0);
	dwc_ddrphy_apb_wr(0x90046,0x109);
	dwc_ddrphy_apb_wr(0x90047,0x0);
	dwc_ddrphy_apb_wr(0x90048,0x7c8);
	dwc_ddrphy_apb_wr(0x90049,0x109);
	dwc_ddrphy_apb_wr(0x9004a,0x0);
	dwc_ddrphy_apb_wr(0x9004b,0x1);
	dwc_ddrphy_apb_wr(0x9004c,0x8);
	dwc_ddrphy_apb_wr(0x9004d,0x0);
	dwc_ddrphy_apb_wr(0x9004e,0x45a);
	dwc_ddrphy_apb_wr(0x9004f,0x9);
	dwc_ddrphy_apb_wr(0x90050,0x0);
	dwc_ddrphy_apb_wr(0x90051,0x448);
	dwc_ddrphy_apb_wr(0x90052,0x109);
	dwc_ddrphy_apb_wr(0x90053,0x40);
	dwc_ddrphy_apb_wr(0x90054,0x633);
	dwc_ddrphy_apb_wr(0x90055,0x179);
	dwc_ddrphy_apb_wr(0x90056,0x1);
	dwc_ddrphy_apb_wr(0x90057,0x618);
	dwc_ddrphy_apb_wr(0x90058,0x109);
	dwc_ddrphy_apb_wr(0x90059,0x40c0);
	dwc_ddrphy_apb_wr(0x9005a,0x633);
	dwc_ddrphy_apb_wr(0x9005b,0x149);
	dwc_ddrphy_apb_wr(0x9005c,0x8);
	dwc_ddrphy_apb_wr(0x9005d,0x4);
	dwc_ddrphy_apb_wr(0x9005e,0x48);
	dwc_ddrphy_apb_wr(0x9005f,0x4040);
	dwc_ddrphy_apb_wr(0x90060,0x633);
	dwc_ddrphy_apb_wr(0x90061,0x149);
	dwc_ddrphy_apb_wr(0x90062,0x0);
	dwc_ddrphy_apb_wr(0x90063,0x4);
	dwc_ddrphy_apb_wr(0x90064,0x48);
	dwc_ddrphy_apb_wr(0x90065,0x40);
	dwc_ddrphy_apb_wr(0x90066,0x633);
	dwc_ddrphy_apb_wr(0x90067,0x149);
	dwc_ddrphy_apb_wr(0x90068,0x10);
	dwc_ddrphy_apb_wr(0x90069,0x4);
	dwc_ddrphy_apb_wr(0x9006a,0x18);
	dwc_ddrphy_apb_wr(0x9006b,0x0);
	dwc_ddrphy_apb_wr(0x9006c,0x4);
	dwc_ddrphy_apb_wr(0x9006d,0x78);
	dwc_ddrphy_apb_wr(0x9006e,0x549);
	dwc_ddrphy_apb_wr(0x9006f,0x633);
	dwc_ddrphy_apb_wr(0x90070,0x159);
	dwc_ddrphy_apb_wr(0x90071,0xd49);
	dwc_ddrphy_apb_wr(0x90072,0x633);
	dwc_ddrphy_apb_wr(0x90073,0x159);
	dwc_ddrphy_apb_wr(0x90074,0x94a);
	dwc_ddrphy_apb_wr(0x90075,0x633);
	dwc_ddrphy_apb_wr(0x90076,0x159);
	dwc_ddrphy_apb_wr(0x90077,0x441);
	dwc_ddrphy_apb_wr(0x90078,0x633);
	dwc_ddrphy_apb_wr(0x90079,0x149);
	dwc_ddrphy_apb_wr(0x9007a,0x42);
	dwc_ddrphy_apb_wr(0x9007b,0x633);
	dwc_ddrphy_apb_wr(0x9007c,0x149);
	dwc_ddrphy_apb_wr(0x9007d,0x1);
	dwc_ddrphy_apb_wr(0x9007e,0x633);
	dwc_ddrphy_apb_wr(0x9007f,0x149);
	dwc_ddrphy_apb_wr(0x90080,0x0);
	dwc_ddrphy_apb_wr(0x90081,0xe0);
	dwc_ddrphy_apb_wr(0x90082,0x109);
	dwc_ddrphy_apb_wr(0x90083,0xa);
	dwc_ddrphy_apb_wr(0x90084,0x10);
	dwc_ddrphy_apb_wr(0x90085,0x109);
	dwc_ddrphy_apb_wr(0x90086,0x9);
	dwc_ddrphy_apb_wr(0x90087,0x3c0);
	dwc_ddrphy_apb_wr(0x90088,0x149);
	dwc_ddrphy_apb_wr(0x90089,0x9);
	dwc_ddrphy_apb_wr(0x9008a,0x3c0);
	dwc_ddrphy_apb_wr(0x9008b,0x159);
	dwc_ddrphy_apb_wr(0x9008c,0x18);
	dwc_ddrphy_apb_wr(0x9008d,0x10);
	dwc_ddrphy_apb_wr(0x9008e,0x109);
	dwc_ddrphy_apb_wr(0x9008f,0x0);
	dwc_ddrphy_apb_wr(0x90090,0x3c0);
	dwc_ddrphy_apb_wr(0x90091,0x109);
	dwc_ddrphy_apb_wr(0x90092,0x18);
	dwc_ddrphy_apb_wr(0x90093,0x4);
	dwc_ddrphy_apb_wr(0x90094,0x48);
	dwc_ddrphy_apb_wr(0x90095,0x18);
	dwc_ddrphy_apb_wr(0x90096,0x4);
	dwc_ddrphy_apb_wr(0x90097,0x58);
	dwc_ddrphy_apb_wr(0x90098,0xb);
	dwc_ddrphy_apb_wr(0x90099,0x10);
	dwc_ddrphy_apb_wr(0x9009a,0x109);
	dwc_ddrphy_apb_wr(0x9009b,0x1);
	dwc_ddrphy_apb_wr(0x9009c,0x10);
	dwc_ddrphy_apb_wr(0x9009d,0x109);
	dwc_ddrphy_apb_wr(0x9009e,0x5);
	dwc_ddrphy_apb_wr(0x9009f,0x7c0);
	dwc_ddrphy_apb_wr(0x900a0,0x109);
	dwc_ddrphy_apb_wr(0x900a1,0x0);
	dwc_ddrphy_apb_wr(0x900a2,0x8140);
	dwc_ddrphy_apb_wr(0x900a3,0x10c);
	dwc_ddrphy_apb_wr(0x900a4,0x10);
	dwc_ddrphy_apb_wr(0x900a5,0x8138);
	dwc_ddrphy_apb_wr(0x900a6,0x104);
	dwc_ddrphy_apb_wr(0x900a7,0x8);
	dwc_ddrphy_apb_wr(0x900a8,0x448);
	dwc_ddrphy_apb_wr(0x900a9,0x109);
	dwc_ddrphy_apb_wr(0x900aa,0xf);
	dwc_ddrphy_apb_wr(0x900ab,0x7c0);
	dwc_ddrphy_apb_wr(0x900ac,0x109);
	dwc_ddrphy_apb_wr(0x900ad,0x47);
	dwc_ddrphy_apb_wr(0x900ae,0x630);
	dwc_ddrphy_apb_wr(0x900af,0x109);
	dwc_ddrphy_apb_wr(0x900b0,0x8);
	dwc_ddrphy_apb_wr(0x900b1,0x618);
	dwc_ddrphy_apb_wr(0x900b2,0x109);
	dwc_ddrphy_apb_wr(0x900b3,0x8);
	dwc_ddrphy_apb_wr(0x900b4,0xe0);
	dwc_ddrphy_apb_wr(0x900b5,0x109);
	dwc_ddrphy_apb_wr(0x900b6,0x0);
	dwc_ddrphy_apb_wr(0x900b7,0x7c8);
	dwc_ddrphy_apb_wr(0x900b8,0x109);
	dwc_ddrphy_apb_wr(0x900b9,0x8);
	dwc_ddrphy_apb_wr(0x900ba,0x8140);
	dwc_ddrphy_apb_wr(0x900bb,0x10c);
	dwc_ddrphy_apb_wr(0x900bc,0x0);
	dwc_ddrphy_apb_wr(0x900bd,0x478);
	dwc_ddrphy_apb_wr(0x900be,0x109);
	dwc_ddrphy_apb_wr(0x900bf,0x0);
	dwc_ddrphy_apb_wr(0x900c0,0x1);
	dwc_ddrphy_apb_wr(0x900c1,0x8);
	dwc_ddrphy_apb_wr(0x900c2,0x8);
	dwc_ddrphy_apb_wr(0x900c3,0x4);
	dwc_ddrphy_apb_wr(0x900c4,0x0);
	dwc_ddrphy_apb_wr(0x90006,0x8);
	dwc_ddrphy_apb_wr(0x90007,0x7c8);
	dwc_ddrphy_apb_wr(0x90008,0x109);
	dwc_ddrphy_apb_wr(0x90009,0x0);
	dwc_ddrphy_apb_wr(0x9000a,0x400);
	dwc_ddrphy_apb_wr(0x9000b,0x106);
	dwc_ddrphy_apb_wr(0xd00e7,0x400);
	dwc_ddrphy_apb_wr(0x90017,0x0);
	dwc_ddrphy_apb_wr(0x90026,0x2a);

	//

        DfiFrq = (userInputBasic.Frequency[0] >> 1);
        psCount[0] = (int)((DfiFrq * delayScale) >> 3);
        if ( userInputBasic.Frequency[0] < 400 ) LowFreqOpt = 3;
        else if ( userInputBasic.Frequency[0] < 533 ) LowFreqOpt = 11;
        psCount[1] = (int)((DfiFrq * delayScale) >> 2) - LowFreqOpt;
        psCount[2] = (int)((10 * DfiFrq * delayScale) >> 2);

        if (DfiFrq * 2 > 533) { dllLock = 176; }
        else if (DfiFrq * 2<= 533 && DfiFrq > 200) { dllLock = 132; }
        else { dllLock = 64; }

        psCount[3] = (int)(dllLock >> 2);

	dwc_ddrphy_apb_wr(0x2000b,psCount[0]);
	dwc_ddrphy_apb_wr(0x2000c,psCount[1]);
	dwc_ddrphy_apb_wr(0x2000d,psCount[2]);
	dwc_ddrphy_apb_wr(0x2000e,psCount[3]);

	dwc_ddrphy_apb_wr(0x9000c,0x0);
	dwc_ddrphy_apb_wr(0x9000d,0x173);
	dwc_ddrphy_apb_wr(0x9000e,0x60);
	dwc_ddrphy_apb_wr(0x9000f,0x6110);
	dwc_ddrphy_apb_wr(0x90010,0x2152);
	dwc_ddrphy_apb_wr(0x90011,0xdfbd);
	dwc_ddrphy_apb_wr(0x90012,0xffff);
	dwc_ddrphy_apb_wr(0x90013,0x6152);

	dwc_ddrphy_apb_wr(0x20089,0x1);

	dwc_ddrphy_apb_wr(0x20088,0x19);

	dwc_ddrphy_apb_wr(0xc0080,0x0);
	dwc_ddrphy_apb_wr(0xd0000,0x1);

	dwc_ddrphy_phyinit_userCustom_customPostTrain ();
	
	dwc_ddrphy_phyinit_userCustom_J_enterMissionMode ();
#ifndef DRAM_DDR4
	dwc_ddrphy_apb_wr(0xd0000,0x0);
	dwc_ddrphy_apb_rd(0x20097);
#endif

	return 0;
}

static int ddr_wr_test(void)
{
	u32 reg;
	u64 ret;
	writeb(0x5a, 0x20000000);
	printf("ddr w1b test ok! addr:0x20000000 value:0x5a\n");
	reg = readb(0x20000000);
	printf("read value is 0x%x\n",reg);
	if(reg == 0x5a)
		printf("ddr r1b test ok!\n");

	writew(0x5aa7, 0x30300000);
	printf("ddr w2b test ok! addr:0x30300000 value:0x5aa7\n");
	reg = readw(0x30300000);
	printf("read value is 0x%x\n",reg);
	if(reg == 0x5aa7)
		printf("ddr r2b test ok!\n");

	writel(0x5aa71342, 0x40540000);
	printf("ddr w4b test ok! addr:0x40540000, value:0x5aa71342\n");
	reg = readl(0x40540000);
	printf("read value is 0x%x\n",reg);
	if(reg == 0x5aa71342)
		printf("ddr r4b test ok!\n");

	writeq(0x5aa713425a5a5a5a, 0x66099000);
	printf("ddr w8b test ok! addr:0x66099000, value:0x5aa713425a5a5a5a\n");
	ret = readq(0x66099000);
	if(ret == 0x5aa713425a5a5a5a)
		printf("ddr r8b test ok!\n");

	return 0;
}

unsigned long ddr_size() {
	return dram_size;
}

static int ddr_init_with_size(unsigned long ddr_size, unsigned long ddr_fw_offset, unsigned char *ddr_fw_sha256)
{
	int ret;
	u32 tmp = 0;
	int reg;

	struct ddr_info ddr = {
			.size = ddr_size,
			.freq = 800,
			.bl = 8,
			.bank = 8,
			.refresh_mode = 0,
	};
	struct ddr_timing *t;

	ddr.freq = ddr_freq;

	//pll_default();
	ddr_sys_default();

	assert_core_ddrc_rstn();
	assert_apb_ddrc_rstn();
	assert_apb_ddrp_rstn();
	assert_ddrp_rstn();
	deassert_apb_ddrc_rstn();
	set_PwrOKIn(1);
	deassert_apb_ddrp_rstn();
	deassert_ddrp_rstn();

	dwc_ddrphy_phyinit_setDefault(0);

	//ddr_pll_config(ddr.freq);
	userInputBasic.Frequency[0] = ddr.freq;

#ifdef DRAM_DDR4
	ddr.refresh_mode = refresh_mode;
	ddr4_set_timing(&ddr);
#else
	ddr3_set_timing(&ddr);
#endif

#ifdef DRAM_DDR3
	if(ddr.freq == 400) {
		ret = readl(0x0ce0049c);
		ret &= ~0xff;
		ret |= 0x7;
		writel(ret, 0x0ce0049c);
	}
	else if(ddr.freq == 533)
	{
		ret = readl(0x0ce00418);
		ret &= ~(1 << 22);
		writel(ret, 0x0ce00418);

		//ddr para load
		writel(0x4, 0x0ce00500);
		writel(0x0, 0x0ce00500);

		writel(0x1a000000, 0x0ce0041c);

		ret = readl(0x0ce00420);
		writel(0x1001, 0x0ce00420);

		//ddr para load
		writel(0x4, 0x0ce00500);
		writel(0x0, 0x0ce00500);

		ret = readl(0x0ce00418);
		ret |= (1 << 22);
		writel(ret, 0x0ce00418);

		//ddr para load
		writel(0x4, 0x0ce00500);
		writel(0x0, 0x0ce00500);

		ret = readl(0x0ce0049c);
		ret &= ~0xff;
		writel(ret, 0x0ce0049c);
	}
	else if(ddr.freq == 800) {
		ret = readl(0x0ce0049c);
		ret &= ~0xff;
		ret |= 0x3;
		writel(ret, 0x0ce0049c);
	}
	else if(ddr.freq == 1066)
	{
		ret = readl(0x0ce00418);
		ret &= ~(1 << 22);
		writel(ret, 0x0ce00418);

		//ddr para load
		writel(0x4, 0x0ce00500);
		writel(0x0, 0x0ce00500);

		writel(0x19000000, 0x0ce0041c);

		ret = readl(0x0ce00420);
		writel(0x1001, 0x0ce00420);

		//ddr para load
		writel(0x4, 0x0ce00500);
		writel(0x0, 0x0ce00500);

		ret = readl(0x0ce00418);
		ret |= (1 << 22);
		writel(ret, 0x0ce00418);

		//ddr para load
		writel(0x4, 0x0ce00500);
		writel(0x0, 0x0ce00500);

		ret = readl(0x0ce0049c);
		ret &= ~0xff;
		writel(ret, 0x0ce0049c);
	}
#else
	if(ddr.freq == 1200) {
		ret = readl(0x0ce00418);
		ret &= ~(1 << 22);
		writel(ret, 0x0ce00418);

		//ddr para load
		writel(0x4, 0x0ce00500);
		writel(0x0, 0x0ce00500);

		writel(0x21000000, 0x0ce0041c);

		ret = readl(0x0ce00420);
		writel(0x1801, 0x0ce00420);

		//ddr para load
		writel(0x4, 0x0ce00500);
		writel(0x0, 0x0ce00500);

		ret = readl(0x0ce00418);
		ret |= (1 << 22);
		writel(ret, 0x0ce00418);

		//ddr para load
		writel(0x4, 0x0ce00500);
		writel(0x0, 0x0ce00500);

		ret = readl(0x0ce0049c);
		ret &= ~0xff;
		writel(ret, 0x0ce0049c);
	}
	else if(ddr.freq == 1066)
	{
		ret = readl(0x0ce00418);
		ret &= ~(1 << 22);
		writel(ret, 0x0ce00418);

		//ddr para load
		writel(0x4, 0x0ce00500);
		writel(0x0, 0x0ce00500);

		writel(0x19000000, 0x0ce0041c);

		ret = readl(0x0ce00420);
		writel(0x1001, 0x0ce00420);

		//ddr para load
		writel(0x4, 0x0ce00500);
		writel(0x0, 0x0ce00500);

		ret = readl(0x0ce00418);
		ret |= (1 << 22);
		writel(ret, 0x0ce00418);

		//ddr para load
		writel(0x4, 0x0ce00500);
		writel(0x0, 0x0ce00500);

		ret = readl(0x0ce0049c);
		ret &= ~0xff;
		writel(ret, 0x0ce0049c);
	}
	else if (ddr.freq == 1333) {
		ret = readl(0x0ce00418);
		ret &= ~(1 << 22);
		writel(ret, 0x0ce00418);

		//ddr para load
		writel(0x4, 0x0ce00500);
		writel(0x0, 0x0ce00500);

		writel(0x19000000, 0x0ce0041c);

		ret = readl(0x0ce00420);
		writel(0x1401, 0x0ce00420);

		//ddr para load
		writel(0x4, 0x0ce00500);
		writel(0x0, 0x0ce00500);

		ret = readl(0x0ce00418);
		ret |= (1 << 22);
		writel(ret, 0x0ce00418);

		//ddr para load
		writel(0x4, 0x0ce00500);
		writel(0x0, 0x0ce00500);

		ret = readl(0x0ce0049c);
		ret &= ~0xff;
		writel(ret, 0x0ce0049c);
	}
	else if (ddr.freq == 1600) {
		ret = readl(0x0ce0049c);
		ret &= ~0xff;
		ret |= 0x1;
		writel(ret, 0x0ce0049c);
	}
	else {
		ret = readl(0x0ce0049c);
		ret &= ~0xff;
		ret |= 0x3;
		writel(ret, 0x0ce0049c);
	}
#endif

	writel(0x1, 0x0ce00500);
	writel(0x0, 0x0ce00500);

#if 1
	t = ddr.timing;

	writel(0x00000001, DDR_UMCTL2_DBG1);
	writel(0x00000001, DDR_UMCTL2_PWRCTL);

	readl(DDR_UMCTL2_STAT);
	// x16 device | burst length 8 | ddr4  
	tmp = ((ddr.bl / 2) << 16) | (1 << 31);
#ifdef DRAM_DDR4
	tmp |= (1 << 4);
#else
	tmp |= (1 << 0);
#endif
//	tmp |= (1 << 12);
	writel(tmp, DDR_UMCTL2_MSTR);
	//??? mr_addr | select rank 0
	tmp = (0xd << 12) | (0x1 << 4);
	writel(tmp, DDR_UMCTL2_MRCTRL0);

	writel(0x00037c0b, DDR_UMCTL2_MRCTRL1);
#ifdef DRAM_DDR4
	writel(0x795d1c6f, DDR_UMCTL2_MRCTRL2);
#else
	writel(0x8541c500, DDR_UMCTL2_MRCTRL2);
#endif

	//when mstr.freq_mode=0 bit[1:0] is ignored!???	
	writel(0x00000001, DDR_UMCTL2_MSTR2);

	//need to ensure
#ifdef DRAM_DDR4
	tmp = 0xa2;
#else
	tmp = 0x20;
#endif
	writel(tmp, DDR_UMCTL2_PWRCTL);

#ifdef DRAM_DDR4
	tmp = (0xc << 16) | (0x3 << 0);
#else
	tmp = 0x2;
#endif
	writel(tmp, DDR_UMCTL2_PWRTMG);

#ifdef DRAM_DDR4
	tmp = (0x86 << 16) | 0x1;
#else
	tmp = (0x7 << 16) | 0x3;
#endif
	writel(tmp, DDR_UMCTL2_HWLPCTL);

#ifdef DRAM_DDR4
	tmp = (0x10 << 12) | (0xc << 4);
#else
	tmp = 0x11c040;
#endif
	writel(tmp, DDR_UMCTL2_RFSHCTL0);

	tmp = (ddr.refresh_mode << 4);//refresh_mode = 2X  mode
	writel(tmp, DDR_UMCTL2_RFSHCTL3);

	ret = ddr_pow(ddr.refresh_mode);
	tmp = (((t->trefi) / 2 / 32 /ret) << 16) | (tck_to_uctl2(t->trfc) << 0);
	writel(tmp, DDR_UMCTL2_RFSHTMG);

	writel(0x00000000, DDR_UMCTL2_CRCPARCTL0);
	writel(0x00000000, DDR_UMCTL2_CRCPARCTL1);

	tmp = (0x3 << 30) | (tck_to_x1024(t->txpr) << 16) | ((tck_to_x1024(us_to_tck(500))+1) << 0);
	writel(tmp, DDR_UMCTL2_INIT0);

	tmp = (tck_to_x1024(us_to_tck(200)) << 16); // if need to be divided by 2?
	writel(tmp, DDR_UMCTL2_INIT1);

#ifdef DRAM_DDR4
	t->mr[0] = ((t->twr / 2 - 5) & 0x7) << 9;

	tmp = t->cl /2 + 1 - tck_to_uctl2(t->cl);
	t->mr[0] |= (tmp << 2);

	if (t->cl < 17)
		t->mr[0] |= ((t->cl - 9) / 2) << 4;
	else if (t->cl == 23)
		t->mr[0] |= (0x6 << 4);
	else if (t->cl/2 == tck_to_uctl2(t->cl))
		t->mr[0] |= DIV_ROUND_UP(t->cl-4, 4) << 4;
	else
		t->mr[0] |= DIV_ROUND_UP(t->cl+7, 4) << 4;
#else
	if(t->twr < 9)
		t->mr[0] = ((t->twr - 4) & 0x7) << 9;
	else if(t->twr < 15)
		t->mr[0] = ((t->twr / 2) & 0x7) << 9;
	else
		t->mr[0] = 0;

	if(t->cl > 11) {
		t->mr[0] |= (1 << 2);
		t->mr[0] |= ((t->cl - 12) << 4);
	} else {
		t->mr[0] |= ((t->cl - 4) << 4);
	}
	//need to check open DLL?
	t->mr[0] |= ((1 << 8) | (1<< 12));
#endif
	if ((t->cl - t->al) < 3)
		t->mr[1] = (t->cl - t->al) << 3;
	else
		t->mr[1] = 0;

#ifdef DRAM_DDR4
	t->mr[1] |= 0x1;
	t->mr[1] |= (mb_DDR4U_1D[0].RTT_NOM_WR_PARK0 & 0x38) << 5;
#endif
	t->mr[1] |= (ODIC & 0x3) <<1;
	writel((t->mr[0] << 16) | t->mr[1], DDR_UMCTL2_INIT3);

#ifdef DRAM_DDR4
	if(t->cwl < 13)
		t->mr[2] = (t->cwl - 9) << 3;
	else
		t->mr[2] = (t->cwl/2 - 3) << 3;

	t->mr[2] |= mb_DDR4U_1D[0].RTT_NOM_WR_PARK0 & 0xE00;
#else
	t->mr[2] = (t->cwl - 5) << 3;
#endif
#ifdef DRAM_DDR4
	if (ddr.freq == 800)
		tmp = 0;
	else if (ddr.freq < 1400)
		tmp = 1;
	else
		tmp = 2;
	t->mr[3] = (tmp << 9);
#else
	t->mr[3] = 0;
#endif
	t->mr[3] |= (ddr.refresh_mode << 6);

	writel((t->mr[2] << 16) | t->mr[3], DDR_UMCTL2_INIT4);

	tmp = (tck_to_uctl2(t->tzqinit / 32) << 16);
	writel(tmp, DDR_UMCTL2_INIT5);
	
#ifdef DRAM_DDR4
	t->mr[4] = 0x0;
	t->mr[5] = mb_DDR4U_1D[0].RTT_NOM_WR_PARK0 & 0x1c0;
	t->mr[5] |= (read_dbi_en << 12) | (write_dbi_en << 11) | (data_mask << 10);
/*	if(ddr.freq < 1200)
		t->mr[5] |= 1;
	else if(ddr.freq < 1400)
		t->mr[5] |= 2;
	else
		t->mr[5] |= 3;
*/
	tmp = (t->mr[4] << 16) | (t->mr[5]);
#else
	tmp = 0;
#endif
	writel(tmp, DDR_UMCTL2_INIT6);

#ifdef DRAM_DDR4
	if (ddr.freq < 800)
		tmp = 0;
	else if (ddr.freq < 1000)
		tmp = 1;
	else if (ddr.freq <= 1200)
		tmp = 2;

	t->mr[6] = tmp << 10;
        if(vrefdq >= 60) {
                tmp = (int) ((vrefdq-60)*100/65);
                t->mr[6] |= tmp;
        }
        else {
                t->mr[6] |= (1 << 6);
                tmp = (int) ((vrefdq-45)*100/65);
                t->mr[6] |= tmp;
        }

	t->mr[22] = 0;
	tmp = (t->mr[22] << 16) | (t->mr[6]);
#else
	tmp = 0;
#endif
	writel(tmp, DDR_UMCTL2_INIT7);
#ifdef DRAM_DDR4
	mb_DDR4U_1D[0].MR0 = t->mr[0];
	mb_DDR4U_1D[0].MR1 = t->mr[1];
	mb_DDR4U_1D[0].MR2 = t->mr[2];
	mb_DDR4U_1D[0].MR3 = t->mr[3];
	mb_DDR4U_1D[0].MR4 = t->mr[4];
	mb_DDR4U_1D[0].MR5 = t->mr[5];
	mb_DDR4U_1D[0].MR6 = t->mr[6];
#else
	mb_DDR3U_1D[0].MR0 = t->mr[0];
	mb_DDR3U_1D[0].MR1 = t->mr[1];
	mb_DDR3U_1D[0].MR2 = t->mr[2];
#endif

#ifdef DRAM_DDR4
	tmp = 1 << 5;
#else
	tmp = 0;
#endif
	writel(tmp, DDR_UMCTL2_DIMMCTL);

	tmp = (((t->wl + (ddr.bl / 2) + t->twr) / 2) << 24) |
	      (tck_to_uctl2(t->tfaw) << 16) |
	      (((t->tras_max / 1024 - 1)/2) << 8) |
	      ((t->tras_min)/2 << 0);
	writel(tmp, DDR_UMCTL2_DRAMTMG0);

	tmp = tck_to_uctl2(t->trc) << 0;
#ifndef DRAM_DDR4
	tmp |= (tck_to_uctl2(t->txpdll) << 16) |
	       (((t->al + DMAX(t->trtp, (u32)4)) / 2) << 8);
#else
	tmp |= (tck_to_uctl2(t->txp) << 16) | 
	       (tck_to_uctl2(DMAX((t->al + t->trtp), (t->rl+ddr.bl/2-t->trp))) << 8);
#endif
	writel(tmp, DDR_UMCTL2_DRAMTMG1);

#ifdef DRAM_DDR4
	//wr preamble
	tmp = (tck_to_uctl2(t->rl + ddr.bl / 2 + 1 + 1- t->wl) << 8) |
	      (tck_to_uctl2(t->cwl + ddr.bl / 2 + t->twtr) << 0);
#else
	tmp = (tck_to_uctl2(t->rl + ddr.bl / 2 + 2 - t->wl) << 8) |
	      (tck_to_uctl2(t->cwl + ddr.bl / 2 + t->twtr) << 0);
#endif
	//check if need
	tmp |= (tck_to_uctl2(t->rl) << 16) | (tck_to_uctl2(t->wl) << 24);
	writel(tmp, DDR_UMCTL2_DRAMTMG2);

	tmp = (tck_to_uctl2(t->tmrd) << 12) | (tck_to_uctl2(t->tmod) << 0);
	writel(tmp, DDR_UMCTL2_DRAMTMG3);

	if (t->trcd > t->al)
		tmp = tck_to_uctl2(t->trcd - t->al) << 24;
	else
		tmp = BIT(24);
	tmp |= (tck_to_uctl2(t->tccd) << 16) | (tck_to_uctl2(t->trrd) << 8) |
	       ((tck_to_uctl2(t->trp) + 1) << 0);
	writel(tmp, DDR_UMCTL2_DRAMTMG4);

	//RDIMM??
	tmp = (tck_to_uctl2(t->tcksrx) << 24) |
	      (tck_to_uctl2(t->tcksre) << 16) | (tck_to_uctl2(t->tckesr) << 8) |
	      (tck_to_uctl2(t->tcke) << 0);
	writel(tmp, DDR_UMCTL2_DRAMTMG5);

#ifdef DRAM_DDR4
	tmp = (tck_to_x32(t->txs_fast) << 24) | (tck_to_x32(t->txs_abort) << 16) |
		(tck_to_x32(t->txsdll) << 8) | (tck_to_x32(t->txs) << 0);
#else
	tmp = (tck_to_x32(t->txsdll) << 8) | (tck_to_x32(t->txs) << 0);
#endif
	writel(tmp, DDR_UMCTL2_DRAMTMG8);

#ifdef DRAM_DDR4
	//trrd_s/2 ? 
	tmp = (tck_to_uctl2(t->tccd_s) << 16) | (tck_to_uctl2(t->trrd_s) << 8) |
		tck_to_uctl2(t->cwl+t->pl+ddr.bl/2+t->twtr_s);
#else
	tmp = 0;
#endif
	writel(tmp, DDR_UMCTL2_DRAMTMG9);

#ifdef DRAM_DDR4
	if(ddr.freq >= 1333)
		tmp = ((tck_to_uctl2(t->tmod) + 4) << 16) | (tck_to_uctl2(t->tmod) << 8) |
			(0x5);
	else
		tmp = 0;
#else
	tmp = 0;
#endif
	writel(tmp, DDR_UMCTL2_DRAMTMG10);

#ifdef DRAM_DDR4
	tmp = (tck_to_uctl2(t->txmpdll) << 24) | ((tck_to_uctl2(t->tmpx_lh) + 1) << 16) | 
		(tck_to_uctl2(t->tmpx_s) << 8) | tck_to_uctl2(t->tckmpe);
#else
	tmp = 0;
#endif
	writel(tmp, DDR_UMCTL2_DRAMTMG11);

#ifdef DRAM_DDR4
	tmp = (tck_to_uctl2(t->twr_mpr) << 24) | (tck_to_uctl2(DMAX(t->tescke, t->tcmdcke)) << 16) |
		tck_to_uctl2(t->tmrd_pda);
#else
	tmp = 0;
#endif
	writel(tmp, DDR_UMCTL2_DRAMTMG12);

#ifdef DRAM_DDR4
	tmp = (1 << 31);
#else
	tmp = 0;
#endif
	writel(tmp, DDR_UMCTL2_DRAMTMG15);

	tmp = (1 << 30) | ((t->tzqoper / 2) << 16) |
		((t->tzqcs / 2) << 0);
	writel(tmp, DDR_UMCTL2_ZQCTL0);

	tmp = 0x70;
	writel(tmp, DDR_UMCTL2_ZQCTL1);

	tmp = (0x3 << 24) | ((t->rl - 5) << 16) | (2 << 8) |
	      ((t->wl - 5) << 0) | BIT(23) | BIT(15);
	writel(tmp, DDR_UMCTL2_DFITMG0);

	tmp = (7 << 16) | BIT(9) | BIT(1);
	writel(tmp, DDR_UMCTL2_DFITMG1);
#ifdef DRAM_DDR4
	writel(0x07007021, DDR_UMCTL2_DFILPCFG0);
	writel(0x000000c1, DDR_UMCTL2_DFILPCFG1);

	writel(0xc0400018, DDR_UMCTL2_DFIUPD0);
	writel(0x00270055, DDR_UMCTL2_DFIUPD1);
	writel(0x80000000, DDR_UMCTL2_DFIUPD2);

	writel(0x00000041, DDR_UMCTL2_DFIMISC);

	tmp = (t->wl - 5) | (t->rl - 5) << 8;
	writel(tmp, DDR_UMCTL2_DFITMG2);

	writel(0x00000008, DDR_UMCTL2_DFITMG3);

	writel(0x00000001, DDR_UMCTL2_DBICTL);
// default is 0x80 << 24
	writel(0x81000000, DDR_UMCTL2_DFIPHYMSTR);

	writel(0x003f0118, DDR_UMCTL2_ADDRMAP1);
	writel(0x01010600, DDR_UMCTL2_ADDRMAP2);
	writel(0x03030101, DDR_UMCTL2_ADDRMAP3);
	writel(0x00001f1f, DDR_UMCTL2_ADDRMAP4);
	writel(0x07060604, DDR_UMCTL2_ADDRMAP5);
	writel(0x07030609, DDR_UMCTL2_ADDRMAP6);
	writel(0x00000f07, DDR_UMCTL2_ADDRMAP7);
    	writel(0x00003f01, DDR_UMCTL2_ADDRMAP8);
	writel(0x0a040905, DDR_UMCTL2_ADDRMAP9);
	writel(0x08050002, DDR_UMCTL2_ADDRMAP10);
	writel(0x00000009, DDR_UMCTL2_ADDRMAP11);
#else	
	writel(0x07000130, DDR_UMCTL2_DFILPCFG0);
	writel(0x00000021, DDR_UMCTL2_DFILPCFG1);

	writel(0xe0400018, DDR_UMCTL2_DFIUPD0);
	writel(0x009900d8, DDR_UMCTL2_DFIUPD1);
	writel(0x80000000, DDR_UMCTL2_DFIUPD2);

	writel(0x00000041, DDR_UMCTL2_DFIMISC);

	tmp = (t->wl - 5) | (t->rl - 5) << 8;
	writel(tmp, DDR_UMCTL2_DFITMG2);

	writel(0x00000008, DDR_UMCTL2_DFITMG3);

	writel(0x00000001, DDR_UMCTL2_DBICTL);
// default is 0x80 << 24
	writel(0x8d000000, DDR_UMCTL2_DFIPHYMSTR);

	writel(0x0002000a, DDR_UMCTL2_ADDRMAP1);
	writel(0x00000700, DDR_UMCTL2_ADDRMAP2);
	writel(0x02050002, DDR_UMCTL2_ADDRMAP3);
	writel(0x00001f1f, DDR_UMCTL2_ADDRMAP4);
	writel(0x08070208, DDR_UMCTL2_ADDRMAP5);
	writel(0x0f070706, DDR_UMCTL2_ADDRMAP6);
	writel(0x00000f0f, DDR_UMCTL2_ADDRMAP7);
	writel(0x00000000, DDR_UMCTL2_ADDRMAP8);
	writel(0x03020605, DDR_UMCTL2_ADDRMAP9);
	writel(0x09010b0b, DDR_UMCTL2_ADDRMAP10);
	writel(0x00000005, DDR_UMCTL2_ADDRMAP11);
#endif
	//how cacl ???
#ifdef DRAM_DDR4
	tmp = (0xa << 24) | (0x1e << 16) | (0xb << 8) | (0x17 << 2);
#else
	tmp = (0x6 << 24) | (0x6 << 8) | ((t->cl - t->cwl) << 2);
#endif
	writel(tmp, DDR_UMCTL2_ODTCFG);

#ifdef DDR_DISABLE_ODT
	tmp = 0;
#else
	tmp = 0x11;
#endif
	writel(tmp, DDR_UMCTL2_ODTMAP);

	//judge if need to config in DDR3 ??
#ifdef DRAM_DDR4
//	writel(0x389a0902, DDR_UMCTL2_SCHED);
//for test
	writel(0x389a0900, DDR_UMCTL2_SCHED);
	writel(0x000000f3, DDR_UMCTL2_SCHED1);
	writel(0x3b0005a4, DDR_UMCTL2_PERFHPR1);
	writel(0xc900f43d, DDR_UMCTL2_PERFLPR1);
	writel(0x7a00e5da, DDR_UMCTL2_PERFWR1);
#else
	writel(0x1cb22300, DDR_UMCTL2_SCHED);
	writel(0x0000001d, DDR_UMCTL2_SCHED1);
	writel(0xf300fba3, DDR_UMCTL2_PERFHPR1);
	writel(0x8500923d, DDR_UMCTL2_PERFLPR1);
	writel(0xd10053e3, DDR_UMCTL2_PERFWR1);
#endif

	//dq bits ??
#ifdef DRAM_DDR4
	writel(0x0534370a, DDR_UMCTL2_DQMAP0);
//	writel(0x340a112e, DDR_UMCTL2_DQMAP1);
	writel(0x00000000, DDR_UMCTL2_DQMAP5);
#endif

	//disable read bypass ??
	writel(0x00000006, DDR_UMCTL2_DBG0);
	writel(0x00000000, DDR_UMCTL2_DBG1);
	writel(0x00000000, DDR_UMCTL2_DBGCMD);

	writel(0x00000001, DDR_UMCTL2_SWCTL);
	writel(0x00000000, DDR_UMCTL2_SWCTLSTATIC);
#ifdef DRAM_DDR4
	writel(0x00110000, DDR_UMCTL2_POISONCFG);
	writel(0x00000011, DDR_UMCTL2_PCCFG);
#else
	writel(0x00110010, DDR_UMCTL2_POISONCFG);
	writel(0x00000000, DDR_UMCTL2_PCCFG);
#endif
	writel(0x00004000, DDR_UMCTL2_PCFGR_0);
	writel(0x00004000, DDR_UMCTL2_PCFGW_0);
	writel(0x00000001, DDR_UMCTL2_PCTRL_0);
	writel(0x00220000, DDR_UMCTL2_PCFGQOS0_0);
	writel(0x03ff03ff, DDR_UMCTL2_PCFGQOS1_0);
	writel(0x00000c00, DDR_UMCTL2_PCFGWQOS0_0);
	writel(0x03ff03ff, DDR_UMCTL2_PCFGWQOS1_0);

	writel(0x00004000, DDR_UMCTL2_PCFGR_1);
	writel(0x00004000, DDR_UMCTL2_PCFGW_1);
	writel(0x00000001, DDR_UMCTL2_PCTRL_1);
	writel(0x00220000, DDR_UMCTL2_PCFGQOS0_1);
	writel(0x03ff03ff, DDR_UMCTL2_PCFGQOS1_1);
	writel(0x00000c00, DDR_UMCTL2_PCFGWQOS0_1);
	writel(0x03ff03ff, DDR_UMCTL2_PCFGWQOS1_1);

	writel(0x00004000, DDR_UMCTL2_PCFGR_2);
	writel(0x00004000, DDR_UMCTL2_PCFGW_2);
	writel(0x00000001, DDR_UMCTL2_PCTRL_2);
	writel(0x00220000, DDR_UMCTL2_PCFGQOS0_2);
	writel(0x03ff03ff, DDR_UMCTL2_PCFGQOS1_2);
	writel(0x00000c00, DDR_UMCTL2_PCFGWQOS0_2);
	writel(0x03ff03ff, DDR_UMCTL2_PCFGWQOS1_2);

	writel(0x00004000, DDR_UMCTL2_PCFGR_3);
	writel(0x00004000, DDR_UMCTL2_PCFGW_3);
	writel(0x00000001, DDR_UMCTL2_PCTRL_3);
	writel(0x00220000, DDR_UMCTL2_PCFGQOS0_3);
	writel(0x03ff03ff, DDR_UMCTL2_PCFGQOS1_3);
	writel(0x00000c00, DDR_UMCTL2_PCFGWQOS0_3);
	writel(0x03ff03ff, DDR_UMCTL2_PCFGWQOS1_3);
	writel(0x00004000, DDR_UMCTL2_PCFGR_4);
	writel(0x00004000, DDR_UMCTL2_PCFGW_4);
	writel(0x00000001, DDR_UMCTL2_PCTRL_4);
	writel(0x00220000, DDR_UMCTL2_PCFGQOS0_4);
	writel(0x03ff03ff, DDR_UMCTL2_PCFGQOS1_4);
	writel(0x00000c00, DDR_UMCTL2_PCFGWQOS0_4);
	writel(0x03ff03ff, DDR_UMCTL2_PCFGWQOS1_4);
	readl(DDR_UMCTL2_RFSHCTL3);
	readl(DDR_UMCTL2_PWRCTL);
#ifdef DRAM_DDR4
	//tmp = 0xa2;
    //for test
	tmp = 0xa0;
#else
	tmp = 0x20;
#endif
	writel(tmp, DDR_UMCTL2_PWRCTL);

	//ddrp init
	deassert_core_ddrc_rstn();

	writel(0x00000000, DDR_UMCTL2_DBG1);
	readl(DDR_UMCTL2_PWRCTL);
	writel(tmp, DDR_UMCTL2_PWRCTL);
	readl(DDR_UMCTL2_PWRCTL);
	writel(tmp & (~(1 << 1)), DDR_UMCTL2_PWRCTL);

	writel(0x00000000, DDR_UMCTL2_SWCTL);
#ifdef DRAM_DDR4
	writel(0x00000041, DDR_UMCTL2_DFIMISC);
#endif
	writel(0x00000040, DDR_UMCTL2_DFIMISC);
	writel(0x00000040, DDR_UMCTL2_DFIMISC);

	readl(DDR_UMCTL2_INIT0);
	readl(DDR_UMCTL2_DBICTL);
	readl(DDR_UMCTL2_MSTR);
	readl(DDR_UMCTL2_MSTR);
#ifdef DRAM_DDR4
	readl(DDR_UMCTL2_DFIMISC);
	readl(DDR_UMCTL2_INIT3);
	readl(DDR_UMCTL2_INIT3);
	readl(DDR_UMCTL2_INIT4);
	readl(DDR_UMCTL2_INIT4);
	readl(DDR_UMCTL2_INIT6);
	readl(DDR_UMCTL2_INIT6);
	readl(DDR_UMCTL2_INIT7);
	readl(DDR_UMCTL2_INIT0);
#else
	readl(DDR_UMCTL2_INIT3);
	readl(DDR_UMCTL2_INIT3);
	readl(DDR_UMCTL2_INIT4);
	readl(DDR_UMCTL2_INIT0);
#endif

	ret = phy_init(ddr_fw_offset, ddr_fw_sha256);
	if(!ret) {
	writel(0x00000060, DDR_UMCTL2_DFIMISC);

	reg = readl(DDR_UMCTL2_DFISTAT);
	while((reg & 0x1) == 0)
	{
		reg = readl(DDR_UMCTL2_DFISTAT);
	}

	writel(0x00000040, DDR_UMCTL2_DFIMISC);
	writel(0x00000041, DDR_UMCTL2_DFIMISC);

	writel(0x00000000, DDR_UMCTL2_PWRCTL);
	writel(0x00000000, DDR_UMCTL2_PWRCTL);

	writel(0x00000001, DDR_UMCTL2_SWCTL);

	reg = readl(DDR_UMCTL2_SWSTAT);
	while((reg & 0x1) == 0)
	{
		reg = readl(DDR_UMCTL2_SWSTAT);
	}

	reg = readl(DDR_UMCTL2_STAT);
	while((reg & 0x2))
	{
		reg = readl(DDR_UMCTL2_STAT);
	}

	writel(0x00000000, DDR_UMCTL2_PWRCTL);
	writel(0x00000000, DDR_UMCTL2_PWRCTL);
	writel(0x00000000, DDR_UMCTL2_PWRCTL);

	writel(0x00000001, DDR_UMCTL2_PCTRL_0);
	writel(0x00000001, DDR_UMCTL2_PCTRL_1);
	writel(0x00000001, DDR_UMCTL2_PCTRL_2);
	writel(0x00000001, DDR_UMCTL2_PCTRL_3);
	}
	return ret;
#endif
}

int ddr_init(unsigned long ddr_fw_offset, unsigned char *ddr_fw_sha256)
{
	int ret;
	unsigned long dram_mbits = DRAM_MBITS;
retry:
	printf("DDR init for %lu Mb RAM...\n", dram_mbits);
	ret = ddr_init_with_size(dram_mbits, ddr_fw_offset, ddr_fw_sha256);
	if (ret)
		return ret;
	dram_size = get_ram_size((void *)DDR_BASE, DDR_MAXSIZE);
	if (dram_size / 1024 / 1024 * 8 != dram_mbits) {
		printf("DRAM size mismatch. Re-do DDR init...\n");
		dram_mbits = dram_size / 1024 / 1024 * 8;
		goto retry;
	}

	printf("Detected DRAM size: %lu Mb\n", dram_mbits);
	ddr_wr_test();
//	ddr_loop_test();
//	ddr_addr_test();
	return 0;
}
