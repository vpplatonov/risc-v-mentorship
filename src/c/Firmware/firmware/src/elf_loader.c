// #include "elf_loader.h"
//
// int elf_load(const void *image, size_t size, uintptr_t *entry_out) {
//   (void)image;
//   (void)size;
//   if (entry_out) {
//     *entry_out = 0;
//   }
//   // TODO: parse ELF header, load PT_LOAD segments, return entry address.
//   return -1;
// }
#include "elf_loader.h"
#include "uart.h"

int elf_verify_header(const Elf64_Ehdr *hdr) {
    /* Cast the first 4 bytes of e_ident directly to validate against ELF_MAGIC */
    uint32_t *magic_check = (uint32_t *)hdr->e_ident;

    if (*magic_check != ELF_MAGIC) {
        return -1; /* Header signature mismatch */
    }

    /* Enforce 64-bit RISC-V architecture constraint check (Machine code 0xF3) */
    if (hdr->e_machine != 0xF3) {
        return -2; /* Target architecture mismatch */
    }

    return 0; /* Header verified successfully */
}

void elf_load_segments(const uint8_t *elf_raw_base) {
    const Elf64_Ehdr *hdr = (const Elf64_Ehdr *)elf_raw_base;

    /* Locate the absolute starting coordinate of the Program Header Table */
    const Elf64_Phdr *phdr_table = (const Elf64_Phdr *)(elf_raw_base + hdr->e_phoff);

    uart_puts("[LOADER] Parsing ELF Program Headers...\n");

    /* Iterate sequentially through every segment entry defined in the header table */
    for (uint16_t i = 0; i < hdr->e_phnum; i++) {
        const Elf64_Phdr *segment = &phdr_table[i];

        /* Evaluate if the segment is flagged as loadable (PT_LOAD) */
        if (segment->p_type == PT_LOAD) {
            uint8_t *dest_ram = (uint8_t *)segment->p_paddr;
            const uint8_t *src_payload = elf_raw_base + segment->p_offset;

            /* High-precision raw byte copy loop bypassing standard memcpy */
            for (uint64_t byte_idx = 0; byte_idx < segment->p_filesz; byte_idx++) {
                dest_ram[byte_idx] = src_payload[byte_idx];
            }

            /* [BSS HANDLING]: Zero-fill any remaining uninitialized memory gaps */
            if (segment->p_memsz > segment->p_filesz) {
                for (uint64_t zero_idx = segment->p_filesz; zero_idx < segment->p_memsz; zero_idx++) {
                    dest_ram[zero_idx] = 0x00;
                }
            }
        }
    }
    uart_puts("[LOADER] Executable code blocks mapped to destination physical target RAM.\n");
}
