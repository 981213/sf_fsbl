#include <stdiol.h>
#include <soc.h>
#include <uart.h>
#include <periphcrm.h>
#include <qspi.h>
#include <flash.h>
#include <brom_header.h>
#include "reg.h"
#include "clk.h"
#include "iomux.h"
#include "ddr.h"

int soc_init()
{
	int i, ret;
	struct sf_brom_header brom_header;

	sf21_crm_setup_cmn_and_postdiv();
	sf_periph_clken_reset(UART_CRM_BASE);
	uart_init(UART1_BASE, sf21_uart_ref_rate(), 115200);
	sf21_clk_dump_rates();
	sf_periph_clken_reset(SPI_CRM_BASE);

	for (i = 2; i <= 7; i++)
		sf_iomux_set_func(i, 0);
	sf_qspi_init(SPI0_BASE, 10);

	ret = flash_init();
	if (ret) {
		printf("failed to init flash.\n");
		return ret;
	}

	flash_read(0, sizeof(brom_header), (unsigned char *)&brom_header);

	ret = ddr_init(sizeof(brom_header) + brom_header.ih_size, NULL);
	if (ret) {
		printf("failed to init dram.\n");
		return ret;
	}

	return 0;
}