# RISC-V ACT Framework Enablement and M-Mode Firmware Validation

This folder contains the scaffold for the second mentorship challenge.

## Structure

- `docs/` design and bring-up notes
- `firmware/` M-mode runtime, loader, and platform code
- `act/` ACT environment and DUT config
- `scripts/` generation, execution, and reporting helpers
- `ci/` smoke checks
- `examples/` user configuration templates
- `reports/` generated outputs

## Quick Start (Scaffold Stage)

```bash
cd src/c/Firmware/firmware
make
```

Use `scripts/` once board-specific logic is implemented.

## Run

Build:

```bash
cd ~/workspace/"RISC-V High Precision"
make -C "src/c/Firmware/firmware" clean
make -C "src/c/Firmware/firmware" CC=riscv64-unknown-elf-gcc
```

Inspect artifacts:

```bash
riscv64-unknown-elf-readelf -h "src/c/Firmware/firmware/firmware.elf"
riscv64-unknown-elf-nm -n "src/c/Firmware/firmware/firmware.elf" | head -40
riscv64-unknown-elf-objdump -d "src/c/Firmware/firmware/firmware.elf" | head -120
```

Demonstrate in QEMU:

```bash
brew install qemu
qemu-system-riscv64 \
  -machine virt -nographic -bios none \
  -kernel "src/c/Firmware/firmware/firmware.elf"
```

Expected behavior:

- Prints `firmware: scaffold build` on the terminal.
- Keeps running in an infinite loop (current scaffold behavior).

Exit QEMU:

- Press `Ctrl+A`, then `X`.

## Status

Scaffold only: files are placeholders with TODO markers.
