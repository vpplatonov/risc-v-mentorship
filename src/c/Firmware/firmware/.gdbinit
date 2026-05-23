set architecture riscv:rv64
set complaints 0

# reset redefine
define target hookpost-remote
  echo Hook: Overriding target reset for QEMU...\n
end