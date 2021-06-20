TARGET=i686-elf

all: DerpiOS.iso

# ISO
DerpiOS.iso: ./iso/floppy.img
	xorriso -as mkisofs -quiet -V 'DERPIOS' -input-charset iso8859-1 -o $@ -b floppy.img -hide floppy.img ./iso/

# ISO floppy image
./iso/floppy.img: ./build/bootsector.bin ./build/kernel.bin
	dd if=/dev/zero of=$@ bs=1024 count=1440
	dd if=./build/bootsector.bin of=$@ seek=0 count=1 conv=notrunc
	dd if=./build/kernel.bin of=$@ seek=1 conv=notrunc

# Kernel
./build/kernel.bin: ./build/kernel_entry.o ./build/kernel.o
	$(TARGET)-ld -o $@ -Ttext 0x7e00 $^ --oformat binary

./build/kernel.o: ./kernel/kernel.c
	$(TARGET)-gcc -ffreestanding -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -c $< -o $@

./build/kernel_entry.o: ./kernel/kernel_entry.asm
	nasm $< -f elf -o $@

# Boot sector
./build/bootsector.bin: ./bootsector/bootsector.asm
	nasm $< -f bin -o $@

clean:
	rm ./build/*