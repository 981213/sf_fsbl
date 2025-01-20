#ifndef __SF_QSPI_H__
#define __SF_QSPI_H__
#include "spi-mem.h"
int sf_qspi_exec_op(const struct spi_mem_op *op);
int sf_qspi_adjust_op_size(struct spi_mem_op *op);
int sf_qspi_init(unsigned long base, uint32_t ratio);
#endif
