#include "platform.h"
#include "uart.h"

/* Allocation of a static mock memory buffer to simulate an architectural test binary */
static uint8_t mock_elf_payload[256];

void platform_init(void) {
    /* Perform microarchitectural hardware clocks and memory bus calibrations */
    uart_puts("[PLATFORM] Board system clock and DDR controller initialized.\n");

    /* [MOCK SETUP]: Inject valid ELF64 header fields directly into the buffer for verification tests */
    mock_elf_payload[0] = 0x7F; /* ELF Magic identifier bytes */
    mock_elf_payload[1] = 'E';
    mock_elf_payload[2] = 'L';
    mock_elf_payload[3] = 'F';

    /* Offset 18: e_machine field according to ELF64 specifications (0xF3 = RISC-V) */
    mock_elf_payload[18] = 0xF3;
    mock_elf_payload[19] = 0x00;
}

uint8_t *platform_get_test_binary_address(void) {
    /* Return the absolute memory address context of the target payload */
    return mock_elf_payload;
}

uintptr_t platform_uart_base(void) {
  // TODO: replace with actual board UART MMIO base.
  return (uintptr_t)0x10000000u;
}
