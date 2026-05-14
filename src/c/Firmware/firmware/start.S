.section .text.init
.globl _start

_start:
  la sp, __stack_top
  call firmware_main
1:
  j 1b
