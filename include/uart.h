#ifndef _UART_H
#define _UART_H
#include <stdint.h>

void uart_init(unsigned long base, uint32_t uart_clk, uint32_t baudrate);
void uart_putchar(int ch);
void uart_wait_tx();
int uart_getchar_nonblock();
int uart_getchar();

#endif
