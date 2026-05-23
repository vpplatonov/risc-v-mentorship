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

## 🛠 Development and Debugging in CLion (macOS)

### 1. Debugger Installation
The standard Homebrew toolchain for RISC-V does not include GDB by default. Install the system multi-architecture GDB:
```bash
brew install gdb
```
*Note: Codesigning the `gdb` binary via macOS developer certificates is not required since debugging is performed remotely via a QEMU TCP socket.*

### 2. `.gdbinit` Configuration
Create a `.gdbinit` file in the root directory containing the `Makefile` (`src/c/Firmware/firmware/.gdbinit`). This automatically configures the target architecture and bypasses false reset errors triggered by the CLion UI:

```text
# Set target architecture
set architecture riscv:rv64
set complaints 0

# Hook to override the "unknown command: 'reset'" error in CLion
define target hookpost-remote
  echo Hook: Overriding target reset for QEMU...\n
end
```

### 3. GDB Command Cheat Sheet for RISC-V
Execute these commands inside the **GDB Console** tab in CLion for rapid CPU state analysis:


| Command | Description |
| :--- | :--- |
| `info reg r` | Compact table of general-purpose registers (`x0`-`x31`, `pc`) |
| `info reg f` | View floating-point registers (if `-march=rv64g` is active) |
| `info all-registers` | Dump all registers, including CSRs (Control and Status Registers) |
| `p/x $mepc` | Print a specific CSR register (e.g., `mepc`) in HEX format |
| `p/x *(uint32_t*)0x80000000` | Read a 32-bit value from a specific memory address |

### 4. Graphical Register Monitoring (GUI)
To track critical registers on the main debug screen without relying on the console:
1. Navigate to the **Threads & Variables** tab.
2. In the variables pane, click **`+`** (or press `Cmd + N`).
3. Add the required registers using the `$` prefix (e.g., `$pc`, `$ra`, `$sp`).
4. Right-click the added register -> **View as** -> **Hex**.
