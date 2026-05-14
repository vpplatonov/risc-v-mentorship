#include "elf_loader.h"

int elf_load(const void *image, size_t size, uintptr_t *entry_out) {
  (void)image;
  (void)size;
  if (entry_out) {
    *entry_out = 0;
  }
  // TODO: parse ELF header, load PT_LOAD segments, return entry address.
  return -1;
}
