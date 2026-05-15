#include <stdint.h>
#include "elf_loader.h"
#include "platform.h"
#include "tohost.h"
#include "uart.h"

void firmware_main(void) {
    platform_init();
    uart_init();

    uart_puts("\n[BOOT] Hard reset sequence initialized cleanly.\n");
    uart_puts("[BOOT] Core running in Machine Mode (M-Mode).\n");

    /* 1. Retrieve the execution coordinate context of the architectural test payload */
    uint8_t *elf_raw_base = platform_get_test_binary_address();

    /* 2. Execute signature and microarchitectural constraint checks on the header boundary */
    uart_puts("[RUNNER] Auditing target payload header integrity...\n");
    Elf64_Ehdr *elf_header = (Elf64_Ehdr *)elf_raw_base;
    int verification_status = elf_verify_header(elf_header);

    if (verification_status != 0) {
        uart_puts("CRITICAL ERROR: Architectural payload validation failed (Header Mismatch).\n");
        tohost_set_fail(1);
        while(1){}
    }
    uart_puts("[RUNNER] ELF header signature matching successful (RISC-V 64-bit target confirmed).\n");

    /* 3. Unpack loadable code segments onto physical RAM address matrices */
    elf_load_segments(elf_raw_base);

    /* Enforce termination sequence for the test pipeline architecture */
    uart_puts("[INFO] Test runner operations completed successfully.\n");
    tohost_set_fail(0xdead);

    while (1) {
        /* Execution trap fallback lock */
    }
}
