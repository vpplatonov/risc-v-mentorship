#ifndef ELF_LOADER_H
#define ELF_LOADER_H

#include <stddef.h>
#include <stdint.h>

int elf_load(const void *image, size_t size, uintptr_t *entry_out);

#endif
