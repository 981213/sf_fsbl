CROSS_COMPILE ?= riscv64-unknown-elf-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS := -c -O2 -g -Iinclude -Ilibfdt -mcpu=c908 -mcmodel=medany -ffunction-sections -fdata-sections -mcmodel=medany

SOC ?= sf21h8898
DRAM_MBITS ?= 4096
DRAM_TYPE ?= ddr3

ifeq ($(DRAM_TYPE), ddr3)
CFLAGS += -DDRAM_DDR3
else
CFLAGS += -DDRAM_DDR4
endif

CFLAGS += -DDRAM_MBITS=$(DRAM_MBITS)

ifeq ($(SOC), sf21h8898)
SOC := sf21
CFLAGS += -DSF21H8898
endif

ifeq ($(SOC), sf21a6826)
SOC := sf21
endif

LDFLAGS := -nostdlib -nostartfiles -static -mcpu=c908 -T soc/$(SOC)/linker.ldS -Wl,-Map=fsbl.map -Wl,--gc-sections -mcmodel=medany

CSOURCES := uart.c qspi.c crt.c main.c
CSOURCES += $(wildcard soc/$(SOC)/*.c)
CSOURCES += spi-nor.c

ASOURCES := start.S

CFLAGS += -Wall -Werror=implicit-function-declaration -Werror=sizeof-pointer-div -Wint-conversion -Werror=return-type

COBJECTS=$(CSOURCES:.c=.o)
AOBJECTS=$(ASOURCES:.S=.o)

fsbl: $(COBJECTS) $(AOBJECTS)
	$(CC) $(LDFLAGS) $(AOBJECTS) $(COBJECTS) -o fsbl.elf
	$(OBJCOPY) -O binary fsbl.elf fsbl.bin
.c.o:
	$(CC) $(CFLAGS) $< -o $@
.S.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -f $(COBJECTS) $(AOBJECTS) fsbl.elf fsbl.bin fsbl.map
