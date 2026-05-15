#ifndef TRAP_H
#define TRAP_H

#include <stdint.h>

/* Synchronous exception cause codes defined by RISC-V Privileged ISA */
#define TRAP_INSTRUCTION_ADDRESS_MISALIGNED 0
#define TRAP_INSTRUCTION_ACCESS_FAULT       1
#define TRAP_ILLEGAL_INSTRUCTION            2
#define TRAP_BREAKPOINT                     3
#define TRAP_LOAD_ADDRESS_MISALIGNED        4
#define TRAP_LOAD_ACCESS_FAULT              5
#define TRAP_STORE_ADDRESS_MISALIGNED       6
#define TRAP_STORE_ACCESS_FAULT             7

/* Functional interfaces for the microarchitectural trap subsystem */
void trap_init(void);
void handle_trap(uint64_t mcause, uint64_t mepc, uint64_t mtval);

#endif /* TRAP_H */

