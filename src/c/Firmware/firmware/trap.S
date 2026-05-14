.section .text
.globl trap_entry

trap_entry:
  addi sp, sp, -16
  sw ra, 12(sp)
  call trap_handler
  lw ra, 12(sp)
  addi sp, sp, 16
  mret
