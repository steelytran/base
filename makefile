AS = i686-elf-as
CC = i686-elf-gcc
LD = i686-elf-gcc

CFLAGS = -std=c99 -ffreestanding -O2 -Wall -Wextra

BIN = test

.PHONY: all clean

all: boot.o kernel.o
	$(LD) -T link.ld -o $(BIN) -ffreestanding -O2 -nostdlib $^ -lgcc

boot.o: boot.s
	$(AS) $^ -o $@

kernel.o: kernel.c
	$(CC) -c $^ -o $@ $(CFLAGS)

clean:
	@rm *.o
	@rm $(BIN)
