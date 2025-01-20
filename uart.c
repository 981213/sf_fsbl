#include <uart.h>
#include <asm/io.h>

#define ODD_PARITY	1
#define EVEN_PARITY	2
#define MASK_PARITY	3
#define NULL_PARITY	4
#define NO_PARITY	5

#define UART_DR		0x00  // Data Register
#define UART_RSR	0x04  // Receive Status Register
#define UART_ECR	0x04  // Error Clear Register
#define UART_FR		0x18  // Flag Register
#define UART_ILPR	0x20  // IrDA Low-Power Counter Register
#define UART_IBRD	0x24  // Integer Baud Rate Register
#define UART_FBRD	0x28  // Fractional Baud Rate Register
#define UART_LCRH	0x2c  // Line Control Register
#define UART_CR		0x30  // Control Register
#define UART_IFLS	0x34  // Interrupt FIFO Level Select Register
#define UART_IMSC	0x38  // Interrupt Mask Set/Clear Register
#define UART_RIS	0x3c  // Raw Interrupt Status Register
#define UART_MIS	0x40  // Masked Interrupt Status Register
#define UART_ICR	0x44  // Interrupt Clear Register
#define UART_DMACR	0x48  // DMA Control Register

#define UART_FR_CTS		(1 << 0)
#define UART_FR_BUSY		(1 << 3)
#define UART_FR_RXFE		(1 << 4)
#define UART_FR_TXFF		(1 << 5)
#define UART_FR_TXFE		(1 << 7)
#define UART_LCRH_BRK		(1 << 0)
#define UART_LCRH_PEN		(1 << 1)
#define UART_LCRH_EPS		(1 << 2)
#define UART_LCRH_STP2		(1 << 3)
#define UART_LCRH_FEN		(1 << 4)
#define UART_LCRH_WLEN0		(1 << 5)
#define UART_LCRH_WLEN1		(1 << 6)
#define UART_LCRH_SPS		(1 << 7)
#define UART_CR_RTS		(1 << 11)

#define UART_FIFO_DEPTH		32

static unsigned long base_addr;

void uart_putchar(int ch)
{
	while ((readl(UART_FR + base_addr) & UART_FR_TXFF))
		cpu_relax();

	writel(ch, base_addr + UART_DR);
}

void uart_wait_tx() {
	while (!(readl(UART_FR + base_addr) & UART_FR_BUSY))
		;
}

int uart_getchar_nonblock()
{
	if(readl(UART_FR + base_addr) & UART_FR_RXFE)
		return -1;

	return readl(base_addr + UART_DR);
}

int uart_getchar()
{
	while(readl(UART_FR + base_addr) & UART_FR_RXFE)
		cpu_relax();

	return readl(base_addr + UART_DR);
}

static int uart_set_baud(uint32_t uart_clk, uint32_t baudrate)
{
	uint16_t ibr, fbr;

	/*create the baudrate */
	ibr = (uart_clk / (16 * baudrate)) & 0xffff;	/*calculate the baudrate divisor and put the integer part into ibr*/
	fbr = (((uart_clk - ibr * (16 * baudrate)) * 64) / (16 * baudrate)) & 0x3f;	/*put the fractional part into fbr*/

	writel(ibr, (UART_IBRD + base_addr));	/*put ibr into Uart Integer Baud Rate Register*/
	writel(fbr, (UART_FBRD + base_addr));

	return 0;
}

static int uart_set_data_len(uint32_t data_len)
{
	uint32_t reg = 0;
	reg = readl(UART_LCRH + base_addr);

	if (data_len == 5) {
		reg &= ~((1 << 5) | (1 << 6));	/*data length = 5 */
		writel(reg, UART_LCRH + base_addr);
	} else if (data_len == 6) {
		reg |= (1 << 5);
		reg &= ~(1 << 6);
		writel(reg , UART_LCRH + base_addr);	/*data length = 6 */
	} else if (data_len == 7) {
		reg &= ~(1 << 5);
		reg |= (1 << 6);
		writel(reg , UART_LCRH + base_addr);	/*data length = 7 */
	} else if (data_len == 8) {
		reg |= ((1 << 5) | (1 << 6));
		writel(reg , UART_LCRH + base_addr);	/*data length = 8 */
	} else {
		return -1;
	}
	return 0 ;
}

static int uart_set_parity(uint32_t parity)
{
	uint32_t reg = 0;
	reg = readl(UART_LCRH + base_addr);

	switch (parity) {
	case ODD_PARITY:
		reg |= (1 << 1);
		reg &= ~(1 << 2);
		writel(reg, UART_LCRH + base_addr);	/*odd parity */
		break;
	case EVEN_PARITY:
		reg |= ((1 << 1) | (1 << 2));
		writel(reg, UART_LCRH + base_addr);	/*even parity */
		break;
	case MASK_PARITY:
		reg |= ((1 << 1) | (1 << 7));
		reg &= ~(1 << 2);
		writel(reg, UART_LCRH + base_addr);	/*parity = 1 */
		break;
	case NULL_PARITY:
		reg |= ((1 << 1) | (1 << 2) | (1 << 7));
		writel(reg, UART_LCRH + base_addr);	/*parity = 0 */
		break;
	case NO_PARITY:
		reg &= ~(1 << 1);
		writel(reg, UART_LCRH + base_addr);	/*NO parity */
		break;
	default:
		return -1;
	}
	return 0;
}

static int uart_init_enable()
{
	uint32_t ttl = 0;
	ttl = readl(UART_CR + base_addr);
	ttl |= 0x301;
	writel(ttl, UART_CR + base_addr);

	return 0;
}

static void uart_config(uint32_t uart_clk, uint32_t baudrate, uint32_t data_len, uint32_t parity, uint32_t stop)
{
	uint32_t reg = 0;

	uart_set_baud(uart_clk, baudrate);	/*create the baudrate you choose */
	uart_set_data_len(data_len);		/*choose the data length you want */
	uart_set_parity(parity);		/*choose the parity mode you want */

	reg = readl(UART_LCRH + base_addr);
	if (stop == 1) {
		reg &= ~(1 << 3);
	} else {
		reg |= (1 << 3);
	}
	reg |= (1 << 4);
	writel(reg, UART_LCRH + base_addr);	/*choose one stop bit and enable the FIFO */
}

void uart_init(unsigned long base, uint32_t uart_clk, uint32_t baudrate)
{
	base_addr = base;
	uart_init_enable();
	uart_config(uart_clk, baudrate, 8, 5, 1);
}
