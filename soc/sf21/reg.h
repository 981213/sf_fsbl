#ifndef _REG_H
#define _REG_H
#include <bit.h>

#define SYSM_BASE	0x0ce00000UL

#define SYSM_RSTC	(SYSM_BASE + 0x30)

#define CLKEN_CFG	(SYSM_BASE + 0x48c)
#define CLKEN_APB	BIT(4)
#define RSTEN_CFG	(SYSM_BASE + 0x4c0)
#define RSTEN_APB	BIT(4)

#define SPI_CRM_BASE	(SYSM_BASE + 0x8800)
#define UART_CRM_BASE	(SYSM_BASE + 0x8c00)

#define UART0_BASE	0x0c300000UL
#define UART1_BASE	0x0c301000UL
#define SPI0_BASE	0x0c200000UL

#endif
