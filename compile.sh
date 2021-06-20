#!/bin/bash

DIR=$(dirname "$0")
TARGET=i686-elf

# Assemble boot sector and kernel entry
nasm "$DIR/bootsector/bootsector.asm" -f bin -o "$DIR/build/bootsector.bin"
nasm "$DIR/kernel/kernel_entry.asm" -f elf -o "$DIR/build/kernel_entry.o"

# Compile and link kernel
$TARGET-gcc -ffreestanding -c "$DIR/kernel/kernel.c" -o "$DIR/build/kernel.o"
$TARGET-ld -o "$DIR/build/kernel.bin" -Ttext 0x7e00 "$DIR/build/kernel_entry.o" "$DIR/build/kernel.o" --oformat binary

# Combine boot sector and kernel into floppy image
#cat "$DIR/build/bootsector.bin" "$DIR/build/kernel.bin" > "$DIR/DerpiOS.img"
dd if=/dev/zero of="$DIR/iso/floppy.img" bs=1024 count=1440
dd if="$DIR/build/bootsector.bin" of="$DIR/iso/floppy.img" seek=0 count=1 conv=notrunc
dd if="$DIR/build/kernel.bin" of="$DIR/iso/floppy.img" seek=1 conv=notrunc

# Make ISO
xorriso -as mkisofs -quiet -V 'DERPIOS' -input-charset iso8859-1 -o "$DIR/DerpiOS.iso" -b floppy.img -hide floppy.img "$DIR/iso/"
