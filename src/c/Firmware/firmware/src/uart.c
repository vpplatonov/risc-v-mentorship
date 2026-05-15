// #include "platform.h"
// #include "uart.h"
//
// void uart_init(void) {
//   // TODO: configure board UART if required.
// }
//
// void uart_putc(char c) {
//   volatile unsigned int *tx = (volatile unsigned int *)platform_uart_base();
//   *tx = (unsigned int)c;
// }
//
// void uart_puts(const char *s) {
//   while (*s) {
//     uart_putc(*s++);
//   }
// }

#include <stdint.h>
#include "uart.h"

/* Physical base address for the QEMU 'virt' NS16550A UART controller */
#define UART_BASE_ADDR 0x10000000

/* Microarchitectural register offsets for standard 16550 UART */
#define UART_RBR_THR   0 /* Receive Buffer / Transmitter Holding Register */
#define UART_IER       1 /* Interrupt Enable Register */
#define UART_FCR       2 /* FIFO Control Register */
#define UART_LCR       3 /* Line Control Register */
#define UART_MCR       4 /* Modem Control Register */
#define UART_LSR       5 /* Line Status Register */

/* Bit 5 of LSR: Transmitter Holding Register Empty flag */
#define UART_LSR_TX_EMPTY (1 << 5)

/* Direct MMIO volatile pointer cast macro to prevent compiler caching */
#define UART_REG(offset) (*((volatile uint8_t *)(UART_BASE_ADDR + offset)))

void uart_init(void) {
    /* Disable interrupts, set 8-bit word length, and activate internal FIFO */
    UART_REG(UART_IER) = 0x00;
    UART_REG(UART_LCR) = 0x03;
    UART_REG(UART_FCR) = 0x07;
    UART_REG(UART_MCR) = 0x00;
}

void uart_putc(char c) {
    /* Poll the status register until hardware is ready to accept a byte */
    while ((UART_REG(UART_LSR) & UART_LSR_TX_EMPTY) == 0) {
        /* Hardware spinlock: waiting for transmitter buffer readiness */
    }
    /* Write character byte directly to transmission hardware queue */
    UART_REG(UART_RBR_THR) = (uint8_t)c;
}

void uart_puts(const char *s) {
    /* Stream the buffer sequentially until null-terminator is hit */
    while (*s) {
        uart_putc(*s++);
    }
}
