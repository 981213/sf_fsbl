#include <soc.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <uart.h>

#define UART_BAUD 115200

int main()
{
	soc_init();

	return 0;
}
