# RISC-V Machine Mode (M-Mode) Firmware Framework

This repository serves as a low-level development and validation sandbox designed to explore bare-metal firmware development, hardware initialization, and architectural compliance testing on the RISC-V architecture. 

The goal of this project is to simulate and implement a minimal, autonomous firmware runner capable of bootloading, setting up exception vectors, and executing automated test suites directly in the highest privilege level (**Machine Mode**), bypassing standard rich operating systems or complex supervisor interfaces (SBI).

---

## 🛠️ System Architecture & Features

The framework is structured to decouple target-agnostic firmware logic from platform-specific hardware descriptions. It focuses on the following core embedded concepts:

*   **Zero-Dependency Bootstrapping (`firmware/`):** A custom assembly entry point (`start.S`) handling early hardware initialization, stack pointer (SP) alignment, and global pointer (GP) setup.
*   **Privileged Trap Handling:** Configuration of the Machine Trap-Vector Base-Address Register (`mtvec`) to capture and decode synchronous exceptions (e.g., illegal instructions, alignment faults) and asynchronous interrupts using `mcause` and `mstatus`.
*   **Memory-Mapped I/O (MMIO) Logging:** A lean, custom UART driver utilizing direct pointer manipulation (`volatile uint32_t*`) to stream boot logs and test telemetry over a serial interface without standard C library overhead.
*   **Architectural Compliance Verification (`act/`):** Integration hooks designed to interface with the **RISC-V Architectural Compliance Test (ACT)** framework, utilizing target signature generation for behavioral verification.

---

## 💻 Cross-Platform Development Environment

The development workspace is optimized for modern hardware-software co-design pipelines, utilizing a split-host translation environment on **Apple Silicon (macOS arm64)**:

1.  **Software Toolchain:** Cross-compilation via `riscv64-unknown-elf-gcc` and binary dissection utilizing GNU Binutils (`readelf`, `objdump`, `nm`) running natively on macOS.
2.  **Virtual Prototyping:** Simulation of a generic RISC-V platform using `qemu-system-riscv64` with `-machine virt -bios none` flags to enforce execution starting directly from the physical reset vector.
3.  **Hardware In-Circuit Emulation:** A secondary validation sandbox leveraging a **Terasic DE10-Nano (Intel Cyclone V SoC)** FPGA board. This setup is utilized to host open-source RISC-V soft-cores (e.g., NEORV32), mapping physical MMIO peripherals and routing UART signals via JTAG (USB-Blaster) to bridging tools like OpenOCD.

---

## 🚀 Building and Running

### Prerequisites
Ensure the RISC-V embedded toolchain and QEMU are installed on your host system:
```bash
# macOS (Homebrew)
brew tap riscv-software-src/riscv
brew install riscv-gnu-toolchain qemu
```

### Compilation
To compile the bare-metal firmware image and inspect its Executable and Linkable Format (ELF) structure:
```bash
# Build the target executable
make

# Verify ELF section headers and alignment
riscv64-unknown-elf-readelf -S firmware.elf

# Disassemble the binary to audit machine-instruction lowering
riscv64-unknown-elf-objdump -d firmware.elf > disassembly.txt
```

### Simulation
Execute the compiled firmware binary within the QEMU emulator to validate early-boot sequences and MMIO output:
```bash
qemu-system-riscv64 -M virt -bios none -display none -serial stdio -kernel firmware.elf
```

---

## 🎯 Research Objectives & LFX Mentorship Alignment

This project is actively maintained as a preparatory technical sandbox for the **RISC-V ACT Framework Enablement and M-Mode Firmware Validation** program. The ongoing architectural focus is centered around:
*   Resolving boot-chain privilege degradation issues (e.g., isolating runtime environments between SPL, OpenSBI, and U-Boot).
*   Implementing deterministic `tohost` / `fromhost` scratchpad register communication over physical memory boundaries.
*   Porting compliance test runners onto physical development boards to bridge the gap between pure ISA simulation and real silicon behavior.
