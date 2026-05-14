#include "elf_loader.h"
#include "platform.h"
#include "tohost.h"
#include "uart.h"

void firmware_main(void) {
  platform_init();
  uart_init();
  uart_puts("firmware: scaffold build\n");

  // TODO: load ACT test ELF from transport/storage and execute entrypoint.
  tohost_set_fail(0xdead);
  while (1) {}
}
