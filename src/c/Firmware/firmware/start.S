.section .text.init
.globl _start
.globl trap_entry

_start:
    /* Setup the initial stack pointer register root boundary */
    la sp, __stack_top

    /* [TRAP CONFIGURATION]: Map the assembly vector entry handler to mtvec */
    la t0, trap_entry
    csrw mtvec, t0

    /* Transfer execution context directly to the C main node */
    call firmware_main

1:
    /* Standard trapped execution loop fallback */
    j 1b

/*
 * [ARCHITECTURAL ENTRY POINT FOR HARDWARE TRAPS]
 * When an exception hits, the hardware jumps here automatically.
 */
.align 4
trap_entry:
    /* Read exact hardware CSR states into active argument registers (a0, a1, a2) */
    csrr a0, mcause  /* Parameter 1: Trap cause identification */
    csrr a1, mepc    /* Parameter 2: Faulting instruction pointer */
    csrr a2, mtval   /* Parameter 3: Bad address or instruction value payload */

    /* Jump directly into the high-level C trap processing node */
    call handle_trap

    /* Safe execution return point (mret instruction fallback) */
    mret
