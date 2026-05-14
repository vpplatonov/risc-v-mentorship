#include "trap.h"
#include "uart.h"

void trap_handler(void) {
  // TODO: read mcause/mepc/mtval and classify expected vs unexpected traps.
  uart_puts("trap: unhandled\n");
}
