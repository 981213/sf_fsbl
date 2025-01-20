#include <bit.h>
#include <qspi.h>
#include <string.h>
#include <asm/io.h>
#include <errno.h>

#define SPI_XFER_BEGIN BIT(0)
#define SPI_XFER_END BIT(1)

/*
 * siflower SSP fifo level
 */
#define SF_SSP_FIFO_LEVEL 0x100

/*
 * siflower SSP register
 */
#define SSP_CR0			0x000
#define SSP_CR1			0x004
#define SSP_DR			0x008
#define SSP_SR			0x00C
#define SSP_CPSR		0x010
#define SSP_IMSC		0x014
#define SSP_RIS			0x018
#define SSP_MIS			0x01C
#define SSP_ICR			0x020
#define SSP_DMACR		0x024
#define SSP_FIFO_LEVEL		0x028
#define SSP_EXSPI_CMD0		0x02C
#define SSP_EXSPI_CMD1		0x030
#define SSP_EXSPI_CMD2		0x034
/* SSP Control Register 0  - SSP_CR0 */
#define SSP_CR0_EXSPI_FRAME	(0x3 << 4)
#define SSP_CR0_SPO		(0x1 << 6)
#define SSP_CR0_SPH		(0x1 << 7)
#define SSP_CR0_BIT_MODE(x)	((x) - 1)
#define SSP_CR0_BIT_MODE_MASK	GENMASK(3, 0)
#define SSP_SCR_MIN		0x00
#define SSP_SCR_MAX		0xFF
#define SSP_SCR_SHFT		8
#define DFLT_CLKRATE		2
/* SSP Control Register 1  - SSP_CR1 */
#define SSP_CR1_MASK_SSE	(0x1 << 1)
#define SSP_CPSR_MIN		(0x02)
#define SSP_CPSR_MAX		(0xFE)
#define DFLT_PRESCALE		(0x40)
/* SSP Status Register - SSP_SR */
#define SSP_SR_MASK_TFE		(0x1 << 0) /* Transmit FIFO empty */
#define SSP_SR_MASK_TNF		(0x1 << 1) /* Transmit FIFO not full */
#define SSP_SR_MASK_RNE		(0x1 << 2) /* Receive FIFO not empty */
#define SSP_SR_MASK_RFF		(0x1 << 3) /* Receive FIFO full */
#define SSP_SR_MASK_BSY		(0x1 << 4) /* Busy Flag */

/* SSP FIFO Threshold Register - SSP_FIFO_LEVEL */
#define SSP_FIFO_LEVEL_RX	GENMASK(14, 8) /* Receive FIFO watermark */
#define SSP_FIFO_LEVEL_TX	GENMASK(6, 0) /* Transmit FIFO watermark */
#define DFLT_THRESH_RX		32
#define DFLT_THRESH_TX		32

/* SSP Raw Interrupt Status Register - SSP_RIS */
#define SSP_RIS_MASK_RORRIS	(0x1 << 0) /* Receive Overrun */
#define SSP_RIS_MASK_RTRIS	(0x1 << 1) /* Receive Timeout */
#define SSP_RIS_MASK_RXRIS	(0x1 << 2) /* Receive FIFO Raw Interrupt status */
#define SSP_RIS_MASK_TXRIS	(0x1 << 3) /* Transmit FIFO Raw Interrupt status */

/* EXSPI command register 0 SSP_EXSPI_CMD0 */
#define EXSPI_CMD0_CMD_COUNT	BIT(0) /* cmd byte, must be set at last */
#define EXSPI_CMD0_ADDR_COUNT	GENMASK(2, 1) /* addr bytes */
#define EXSPI_CMD0_EHC_COUNT	BIT(3) /* Set 1 for 4-byte address mode */
#define EXSPI_CMD0_TX_COUNT	GENMASK(14, 4) /* TX data bytes */
#define EXSPI_CMD0_VALID	BIT(15) /* Set 1 to make the cmd to be run */

/* EXSPI command register 1 SSP_EXSPI_CMD1 */
#define EXSPI_CMD1_DUMMY_COUNT	GENMASK(3, 0) /* dummy bytes */
#define EXSPI_CMD1_RX_COUNT	GENMASK(14, 4) /* RX data bytes */

/* EXSPI command register 2 SSP_EXSPI_CMD2 */
/* Set 1 for 1-wire, 2 for 2-wire, 3 for 4-wire */
#define EXSPI_CMD2_CMD_IO_MODE	GENMASK(1, 0) /* cmd IO mode */
#define EXSPI_CMD2_ADDR_IO_MODE	GENMASK(3, 2) /* addr IO mode */
#define EXSPI_CMD2_DATA_IO_MODE	GENMASK(5, 4) /* data IO mode */

#define MAX_S_BUF 16

#define min_t(type, x, y) ({			\
	type __min1 = (x);			\
	type __min2 = (y);			\
	__min1 < __min2 ? __min1: __min2; })

static unsigned long siflower_spi_base;

static void sf_qspi_flush_rxfifo(void)
{
	while (readw(siflower_spi_base + SSP_SR) & SSP_SR_MASK_RNE)
		readw(siflower_spi_base + SSP_DR);
}

static void sf_qspi_wait_not_busy(void)
{
	while (readw(siflower_spi_base + SSP_SR) & SSP_SR_MASK_BSY)
		;
}

static void sf_qspi_wait_rx_not_empty(void)
{
	while (!(readw(siflower_spi_base + SSP_SR) & SSP_SR_MASK_RNE))
		;
}

static void sf_qspi_wait_rxfifo(void)
{
	while (!(readw(siflower_spi_base + SSP_RIS) & SSP_RIS_MASK_RXRIS))
		;
}

static void sf_qspi_enable(void)
{
	/* Enable the SPI hardware */
	writew(SSP_CR1_MASK_SSE, siflower_spi_base + SSP_CR1);
}

static void sf_qspi_disable(void)
{
	/* Disable the SPI hardware */
	writew(0, siflower_spi_base + SSP_CR1);
}

static void sf_qspi_xmit(unsigned int nbytes, const uint8_t *out)
{
	while (nbytes--)
		writew(*out++, siflower_spi_base + SSP_DR);
}

static int sf_qspi_rcv(unsigned int nbytes, uint8_t *in)
{
	int i;

	while (nbytes >= DFLT_THRESH_RX) {
		/* wait for RX FIFO to reach the threshold */
		sf_qspi_wait_rxfifo();

		for (i = 0; i < DFLT_THRESH_RX; i++)
			*in++ = readw(siflower_spi_base + SSP_DR);

		nbytes -= DFLT_THRESH_RX;
	}

	/* read the remaining data */
	while (nbytes) {
		sf_qspi_wait_rx_not_empty();

		*in++ = readw(siflower_spi_base + SSP_DR);
		nbytes--;
	}

	return 0;
}

static void sf_qspi_set_param(const struct spi_mem_op *op)
{
	unsigned int tx_count = 0, rx_count = 0;
	uint8_t cmd_io, addr_io, data_io;
	uint8_t addr_count, ehc_count;

	cmd_io = op->cmd.buswidth == 4 ? 3 : op->cmd.buswidth;
	addr_io = op->addr.buswidth == 4 ? 3 : op->addr.buswidth;
	data_io = op->data.buswidth == 4 ? 3 : op->data.buswidth;

	if (op->data.nbytes) {
		if (op->data.dir == SPI_MEM_DATA_IN) {
			rx_count = op->data.nbytes;
		} else {
			tx_count = op->data.nbytes;
		}
	}
	if (op->addr.nbytes > 3) {
		addr_count = 3;
		ehc_count = 1;
	} else {
		addr_count = op->addr.nbytes;
		ehc_count = 0;
	}

	writew(FIELD_PREP(EXSPI_CMD2_CMD_IO_MODE, cmd_io) |
		       FIELD_PREP(EXSPI_CMD2_ADDR_IO_MODE, addr_io) |
		       FIELD_PREP(EXSPI_CMD2_DATA_IO_MODE, data_io),
	       siflower_spi_base + SSP_EXSPI_CMD2);
	writew(FIELD_PREP(EXSPI_CMD1_DUMMY_COUNT, op->dummy.nbytes) |
		       FIELD_PREP(EXSPI_CMD1_RX_COUNT, rx_count),
	       siflower_spi_base + SSP_EXSPI_CMD1);
	writew(EXSPI_CMD0_VALID |
		       FIELD_PREP(EXSPI_CMD0_CMD_COUNT, op->cmd.nbytes) |
		       FIELD_PREP(EXSPI_CMD0_ADDR_COUNT, addr_count) |
		       FIELD_PREP(EXSPI_CMD0_EHC_COUNT, ehc_count) |
		       FIELD_PREP(EXSPI_CMD0_TX_COUNT, tx_count),
	       siflower_spi_base + SSP_EXSPI_CMD0);
}

int sf_qspi_exec_op(const struct spi_mem_op *op)
{
	unsigned int pops = 0;
	int i, op_len;
	const uint8_t *tx_buf = NULL;
	uint8_t *rx_buf = NULL, op_buf[MAX_S_BUF];

	if (op->data.nbytes) {
		if (op->data.dir == SPI_MEM_DATA_IN) {
			rx_buf = op->data.buf.in;
		} else {
			tx_buf = op->data.buf.out;
		}
	}
	op_len = op->cmd.nbytes + op->addr.nbytes + op->dummy.nbytes;
	sf_qspi_set_param(op);
	/*
	 * Avoid using malloc() here so that we can use this code in SPL where
	 * simple malloc may be used. That implementation does not allow free()
	 * so repeated calls to this code can exhaust the space.
	 *
	 * The value of op_len is small, since it does not include the actual
	 * data being sent, only the op-code and address. In fact, it should be
	 * popssible to just use a small fixed value here instead of op_len.
	 */
	op_buf[pops++] = op->cmd.opcode;
	if (op->addr.nbytes) {
		for (i = 0; i < op->addr.nbytes; i++)
			op_buf[pops + i] = op->addr.val >>
					   (8 * (op->addr.nbytes - i - 1));
		pops += op->addr.nbytes;
	}

	sf_qspi_flush_rxfifo();
	memset(op_buf + pops, 0xff, op->dummy.nbytes);
	sf_qspi_xmit(op_len, op_buf);
	if (tx_buf) {
		sf_qspi_xmit(op->data.nbytes, tx_buf);
	}
	sf_qspi_enable();
	if (rx_buf) {
		sf_qspi_rcv(op->data.nbytes, rx_buf);
	} else {
		sf_qspi_wait_not_busy();
	}
	sf_qspi_disable();

	return 0;
}

int sf_qspi_adjust_op_size(struct spi_mem_op *op)
{
	uint32_t nbytes;

	nbytes = op->cmd.nbytes + op->addr.nbytes + op->dummy.nbytes;
	if (nbytes >= SF_SSP_FIFO_LEVEL)
		return -EOPNOTSUPP;

	if (op->data.dir == SPI_MEM_DATA_IN)
		op->data.nbytes =
			min_t(unsigned int, op->data.nbytes, SF_SSP_FIFO_LEVEL);
	else
		op->data.nbytes = min_t(unsigned int, op->data.nbytes,
					SF_SSP_FIFO_LEVEL - nbytes);

	return 0;
}

static void sf_qspi_set_bitrate(uint32_t ratio) {
	uint16_t reg_cr0;
	uint16_t scr;
	/* Clear SPI CR0 Bit 8:15 and CPR Bit 0:7 */
	reg_cr0 = readw(siflower_spi_base + SSP_CR0);
	reg_cr0 &= ~(0xff << 8);
	scr = (ratio / 2 - 1) & 0xff;
	writew(2, siflower_spi_base + SSP_CPSR);
	writew(reg_cr0 | (scr << 8), siflower_spi_base + SSP_CR0);
}

int sf_qspi_init(unsigned long base, uint32_t ratio)
{
	uint16_t cr0;

	siflower_spi_base = base;

	cr0 = readw(siflower_spi_base + SSP_CR0);
	cr0 |= SSP_CR0_EXSPI_FRAME | SSP_CR0_BIT_MODE(8);
	writew(cr0, siflower_spi_base + SSP_CR0);

	sf_qspi_set_bitrate(ratio);

	writew(FIELD_PREP(SSP_FIFO_LEVEL_RX, DFLT_THRESH_RX) |
		       FIELD_PREP(SSP_FIFO_LEVEL_TX, DFLT_THRESH_TX),
	       siflower_spi_base + SSP_FIFO_LEVEL);

	return 0;
}
