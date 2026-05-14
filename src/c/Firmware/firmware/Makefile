CC      ?= riscv64-unknown-elf-gcc
OBJCOPY ?= riscv64-unknown-elf-objcopy
OBJDUMP ?= riscv64-unknown-elf-objdump

CFLAGS  ?= -Wall -Wextra -O2 -ffreestanding -nostdlib -nostartfiles -Iinclude -mcmodel=medany -march=rv64imac -mabi=lp64
LDFLAGS ?= -T linker.ld -nostdlib -nostartfiles

SRCS_C := src/main.c src/uart.c src/elf_loader.c src/trap.c src/tohost.c src/cache_sync.c src/platform_board.c
SRCS_S := start.S trap.S
OBJS   := $(SRCS_C:.c=.o) $(SRCS_S:.S=.o)

TARGET := firmware.elf
BIN    := firmware.bin

.PHONY: all clean

ifneq ($(filter clean,$(MAKECMDGOALS)),clean)
ifeq ($(findstring riscv,$(CC)),)
$(error CC='$(CC)' is not a RISC-V compiler. Use make CC=riscv64-unknown-elf-gcc)
endif
endif

all: $(TARGET) $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS) linker.ld
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(BIN): $(TARGET)
	$(OBJCOPY) -O binary $< $@

clean:
	rm -f $(OBJS) $(TARGET) $(BIN)
