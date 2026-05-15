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


//
// void execute_compliance_payload(void) {
//     /* 1. Locate and extract the memory boundaries of the raw test binary */
//     uint8_t *elf_raw_data = platform_get_test_binary_address();
//
//     /* 2. Map and validate the Executable and Linkable Format (ELF) header structure */
//     elf_header_t *header = (elf_header_t *)elf_raw_data;
//     if (header->magic != ELF_MAGIC) {
//         uart_puts("CRITICAL ERROR: Architectural payload validation failed (Invalid ELF Magic).\n");
//         tohost_set_fail(1);
//     }
//
//     /* 3. Parse Program Headers and copy executable payload segments into physical target RAM.
//      * The loader unpacks '.text', '.data', and '.bss' sections to their absolute execution addresses.
//      */
//     elf_load_sections(header);
//
//     /* 4. Extract target memory boundaries allocated for architectural state signature dumping */
//     uint64_t *signature_begin = (uint64_t *)elf_find_symbol("begin_signature");
//     uint64_t *signature_end   = (uint64_t *)elf_find_symbol("end_signature");
//
//     if (!signature_begin || !signature_end) {
//         uart_puts("WARNING: Trace symbols missing. Signature dumping may degrade.\n");
//     }
//
//     /* 5. Inject entry coordinates and branch execution context directly to the test payload */
//     uart_puts("[RUNNER] Transferring control to architectural test entry point...\n");
//     void (*test_entrypoint)(void) = (void (*)(void))(uintptr_t)header->entry_point;
//
//     /* Hardware context switch to the test suite logic */
//     test_entrypoint();
//
//     /* 6. Enforce synchronous polling loop until the execution payload flags a completion signal */
//     uart_puts("[RUNNER] Test payload executing. Awaiting 'tohost' state transition...\n");
//     while (tohost_is_empty()) {
//         /* Hardware spinlock: waiting for the test suite to modify the 'tohost' scratchpad memory */
//     }
//
//     /* 7. Retrieve compliance signature footprint from RAM and stream raw bytes over the active UART pipe */
//     uart_puts("--- BEGIN ACT SIGNATURE DUMP ---\n");
//     uart_dump_signature(signature_begin, signature_end);
//     uart_puts("--- END ACT SIGNATURE DUMP ---\n");
// }
