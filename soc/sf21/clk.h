#ifndef __CLK_H__
#define __CLK_H__
void sf21_crm_setup_cmn_and_postdiv();
unsigned long sf21_uart_ref_rate();
unsigned long sf21_cpu_rate();
void sf21_clk_dump_rates();
#endif