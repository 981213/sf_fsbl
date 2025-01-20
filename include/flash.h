#ifndef __FLASH_H__
#define __FLASH_H__

#include <asm/types.h>
#define DDR_FW_LEN (64 * 1024)

int flash_init(void);
int flash_read(unsigned long addr, unsigned long size, unsigned char *buf);
unsigned int flash_uboot_offs(void);

#endif