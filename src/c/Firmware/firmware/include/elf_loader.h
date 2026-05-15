// #ifndef ELF_LOADER_H
// #define ELF_LOADER_H
//
// #include <stddef.h>
// #include <stdint.h>
//
// int elf_load(const void *image, size_t size, uintptr_t *entry_out);
//
// #endif
#ifndef ELF_LOADER_H
#define ELF_LOADER_H

#include <stdint.h>

/* Standard ELF Magic identifier: 0x7F followed by 'E', 'L', 'F' */
#define ELF_MAGIC 0x464C457FU  /* Little-endian representation of 0x7F 'E' 'L' 'F' */

/* Target definitions for RISC-V 64-bit ELF Executable Headers */
typedef struct {
    uint8_t  e_ident[16];   /* ELF Identification marks */
    uint16_t e_type;        /* Object file type */
    uint16_t e_machine;     /* Architecture target (Expected: 0xF3 for RISC-V) */
    uint32_t e_version;     /* Object file version */
    uint64_t e_entry;       /* Entry point virtual address */
    uint64_t e_phoff;       /* Program header table file offset */
    uint64_t e_shoff;       /* Section header table file offset */
    uint32_t e_flags;       /* Processor-specific flags */
    uint16_t e_ehsize;      /* ELF header size in bytes */
    uint16_t e_phentsize;   /* Program header table entry size */
    uint16_t e_phnum;       /* Program header table entry count */
    uint16_t e_shentsize;   /* Section header table entry size */
    uint16_t e_shnum;       /* Section header table entry count */
    uint16_t e_shstrndx;    /* Section header string table index */
} Elf64_Ehdr;

/* Target definitions for RISC-V 64-bit ELF Program Headers (Segments) */
typedef struct {
    uint32_t p_type;        /* Segment type (e.g., PT_LOAD for executable code) */
    uint32_t p_flags;       /* Segment flags (Execute, Read, Write permissions) */
    uint64_t p_offset;      /* Segment file offset */
    uint64_t p_vaddr;       /* Segment virtual address in RAM */
    uint64_t p_paddr;       /* Segment physical address (identical in M-Mode) */
    uint64_t p_filesz;      /* Segment size inside the binary file payload */
    uint64_t p_memsz;       /* Segment size inside the physical RAM allocation */
    uint64_t p_align;       /* Segment alignment boundaries */
} Elf64_Phdr;

/* Segment type identifier for loadable segments */
#define PT_LOAD 1

/* Functional interface boundaries */
int elf_verify_header(const Elf64_Ehdr *hdr);
void elf_load_segments(const uint8_t *elf_raw_base);

#endif /* ELF_LOADER_H */
