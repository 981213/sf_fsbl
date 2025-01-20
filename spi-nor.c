#include <errno.h>
#include <qspi.h>
#include <brom_header.h>

static uint8_t spi_nor_addr_len;

static int spi_nor_read(unsigned long addr, unsigned long size, unsigned char *buf)
{
	struct spi_mem_op op = SPI_MEM_OP(SPI_MEM_OP_CMD(0x3b, 1),
					  SPI_MEM_OP_ADDR(spi_nor_addr_len, addr, 1),
					  SPI_MEM_OP_DUMMY(1, 1),
					  SPI_MEM_OP_DATA_IN(size, buf, 2));
	int ret;
	ret = sf_qspi_adjust_op_size(&op);
	if (ret < 0)
		return ret;

	sf_qspi_exec_op(&op);
	return op.data.nbytes;
}

int flash_init(void) {
	struct sf_brom_header header;

	spi_nor_addr_len = 3;
	spi_nor_read(0, sizeof(header), (unsigned char *)&header);
	if (header.ih_magic == BROM_MAGIC)
		return 0;
	spi_nor_addr_len = 4;
	spi_nor_read(0, sizeof(header), (unsigned char *)&header);
	if (header.ih_magic == BROM_MAGIC)
		return 0;
	spi_nor_addr_len = 3;
	return -EINVAL;
}

int flash_read(unsigned long addr, unsigned long size, unsigned char *buf)
{
	int ret;
	while (size) {
		ret = spi_nor_read(addr, size, buf);
		if (ret < 0)
			return ret;
		else if (ret == 0)
			return -EINVAL;
		addr += ret;
		size -= ret;
		buf += ret;
	}
	return 0;
}
