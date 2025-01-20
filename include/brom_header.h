#ifndef __BROM_HEADER_H__
#define __BROM_HEADER_H__

/* "sa18" reversed (because it's a little-endian chip) */
#define BROM_MAGIC 0x38316173

struct sf_brom_params {
	int _debug_mode;
	int uart_connected;
	int uart_rev_timeout;
	int uart_sync_timeout;
	unsigned int uart_baudrate;
	unsigned int retry_load_img;
	int _spi_ratio;
	unsigned int phy_reset_assert_ms;
	unsigned int phy_reset_deassert_ms;
	unsigned int phy_reset_gpio;
	int gmac_link_time_ms_check_max;
	int _ddr_type;
	int _ddr_freq;
	int _ddr_size;
	int _ddr_fw_addr;
	int _skip_download;
        unsigned int reserved[6];
};

/*
 * 16 bytes image header:
 * | -------------4-byte-image-size----------- |
 * | ---------------4-byte-magic-------------- |
 * | -----3-byte-flags------ | 1-byte-checksum |
 * | ----------4-byte-rom-patch-offset-------- |
 */
struct sf_brom_header {
	unsigned int ih_size;
	unsigned int ih_magic;
	struct {
		unsigned int ih_checksum:8;		/* bit[0:7] checksum */
		unsigned int reserved:2;		/* bit[10:9] reserved*/
		unsigned int secure_boot:1;		/* bit[11] bootup need secure boot*/
		unsigned int soft_rsa:1;		/* bit[12] use software rsa */
		unsigned int soft_sha:1;		/* bit[13] use software sha */
		unsigned int reserved1:2;		/* bit[14:15] reserved */
		unsigned int params_en:1;		/* bit[16] the flags to enable params filed */
		unsigned int reserved2:15;		/* bit[31:17] reserved */
	} flags;
	unsigned int reserved[3];			/* reserved */
	struct sf_brom_params params;			/* image@FBL params, controlled by [params_en] filed */
};

#endif /* __BROM_HEADER_H__*/
