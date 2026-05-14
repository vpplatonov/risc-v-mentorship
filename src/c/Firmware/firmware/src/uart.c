#include "platform.h"
#include "uart.h"

void uart_init(void) {
  // TODO: configure board UART if required.
}

void uart_putc(char c) {
  volatile unsigned int *tx = (volatile unsigned int *)platform_uart_base();
  *tx = (unsigned int)c;
}

void uart_puts(const char *s) {
  while (*s) {
    uart_putc(*s++);
  }
}
