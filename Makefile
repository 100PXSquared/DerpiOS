TARGET=i686-elf
SOURCE=$(wildcard kernel/*/*.c) $(wildcard kernel/*.c)
ASMSRC=$(filter-out kernel/kernel_entry.asm,$(wildcard kernel/*.asm))
OBJECT=$(SOURCE:.c=.o) $(ASMSRC:.asm=.o)

all: DerpiOS.iso

# ISO
DerpiOS.iso: ./iso/floppy.img
	xorriso -as mkisofs -quiet -V 'DERPIOS' -input-charset iso8859-1 -o $@ -b floppy.img -hide floppy.img ./iso/

# ISO floppy image
iso/floppy.img: ./build/bootsector.bin ./build/kernel.bin
	dd if=/dev/zero of=$@ bs=1024 count=1440
	dd if=./build/bootsector.bin of=$@ seek=0 count=1 conv=notrunc
	dd if=./build/kernel.bin of=$@ seek=1 conv=notrunc

# Kernel
build/kernel.bin: kernel/kernel_entry.o $(OBJECT)
	$(TARGET)-ld -o $@ -Ttext 0x7e00 $^ --oformat binary

.c.o:
	$(TARGET)-gcc -DDEBUG -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -ffreestanding -Tkernel -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

# Boot sector
build/bootsector.bin: ./bootsector/bootsector.asm
	nasm $< -f bin -o $@

# Commands
clean:
	find . -type f -name '*.o' -exec rm {} +
	rm ./iso/floppy.img ./DerpiOS.iso ./build/*

run: all
	qemu-system-i386 -cdrom ./DerpiOS.iso
