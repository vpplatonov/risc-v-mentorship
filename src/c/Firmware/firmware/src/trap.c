#include "trap.h"
#include "uart.h"
#include "tohost.h"

void handle_trap(uint64_t mcause, uint64_t mepc, uint64_t mtval) {
    uart_puts("\n[CRITICAL] !!! HARDWARE TRAP ENCOUNTERED !!!\n");

    /* Evaluate if the trap event was triggered by an interrupt or an exception */
    if (mcause & (1ULL << 63)) {
        uart_puts("[TRAP INFO] Type: Asynchronous Hardware Interrupt\n");
    } else {
        uart_puts("[TRAP INFO] Type: Synchronous Exception\n");

        /* Decode specific exception vector reasons */
        uint64_t exception_code = mcause & 0x3F;
        switch (exception_code) {
            case TRAP_ILLEGAL_INSTRUCTION:
                uart_puts("[TRAP REASON] Cause: Illegal Instruction Execution Attempt.\n");
                break;
            case TRAP_BREAKPOINT:
                uart_puts("[TRAP REASON] Cause: Software Breakpoint (ebreak).\n");
                break;
            case TRAP_LOAD_ADDRESS_MISALIGNED:
            case TRAP_STORE_ADDRESS_MISALIGNED:
                uart_puts("[TRAP REASON] Cause: Memory Access Address Misalignment.\n");
                break;
            default:
                uart_puts("[TRAP REASON] Cause: Unclassified Hardware Exception Vector.\n");
                break;
        }
    }

    /* Stream exact execution context boundaries for debug auditing */
    uart_puts("[TRAP STATE] Faulting Instruction Address (mepc): 0x");
    /* Mock hexadecimal output placeholder for simplicity */
    uart_putc('0'); uart_putc('x');

    /* Terminate simulation immediately to prevent infinite CPU core fault loops */
    uart_puts("\n[TRAP LOCK] Aborting test runner operations due to hardware fault.\n");
    tohost_set_fail(1);
    while (1) {}
}

