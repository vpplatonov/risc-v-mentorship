#include "platform.h"

void platform_init(void) {
  // TODO: board-specific clock/memory/peripheral init.
}

uintptr_t platform_uart_base(void) {
  // TODO: replace with actual board UART MMIO base.
  return (uintptr_t)0x10000000u;
}
