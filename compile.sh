#!/bin/bash

DIR=$(dirname "$0")
TARGET=i686-elf

# Assemble boot sector and kernel entry
nasm "$DIR/bootsector/bootsector.asm" -f bin -o "$DIR/build/bootsector.bin"
nasm "$DIR/kernel/kernel_entry.asm" -f elf -o "$DIR/build/kernel_entry.o"

# Compile and link kernel
$TARGET-gcc -ffreestanding -c "$DIR/kernel/kernel.c" -o "$DIR/build/kernel.o"
$TARGET-ld -o "$DIR/build/kernel.bin" -Ttext 0x7e00 "$DIR/build/kernel_entry.o" "$DIR/build/kernel.o" --oformat binary

# Combine boot sector and kernel
cat "$DIR/build/bootsector.bin" "$DIR/build/kernel.bin" > "$DIR/DerpiOS.img"

dd if=/dev/zero of="$DIR/DerpiOS.img" bs=1 count=1 seek=653312