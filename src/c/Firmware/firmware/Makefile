# --- Microarchitectural Build Blueprint (Complete Monolithic Core) ---

CC      = riscv64-unknown-elf-gcc
OBJCOPY = riscv64-unknown-elf-objcopy

TARGET  = firmware.elf
BIN     = firmware.bin

OBJ_DIR = obj
INC_DIR = include
SRC_DIR = src

CFLAGS  = -Wall -Wextra -O2 -g -march=rv64g -mabi=lp64d -mcmodel=medany -nostdlib -fno-builtin -I$(INC_DIR)
LDFLAGS = -T linker.ld -nostdlib

# Complete list of objects defining the final runtime state machine footprint
OBJS    = $(OBJ_DIR)/start.o $(OBJ_DIR)/main.o $(OBJ_DIR)/uart.o $(OBJ_DIR)/platform_board.o $(OBJ_DIR)/tohost.o $(OBJ_DIR)/elf_loader.o $(OBJ_DIR)/trap.o

.PHONY: all clean run

all: $(OBJ_DIR) $(TARGET) $(BIN)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/start.o: start.S
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/uart.o: $(SRC_DIR)/uart.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/platform_board.o: $(SRC_DIR)/platform_board.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/tohost.o: $(SRC_DIR)/tohost.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/elf_loader.o: $(SRC_DIR)/elf_loader.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/trap.o: $(SRC_DIR)/trap.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

$(BIN): $(TARGET)
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(BIN)
	rm -f $(SRC_DIR)/*.o
	rm -f *.o

run: all
	qemu-system-riscv64 -machine virt -nographic -bios none -kernel $(TARGET)
