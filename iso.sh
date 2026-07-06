#!/bin/sh
set -e

mkdir -p iso/boot/grub

cp sysroot/boot/specialk iso/boot/specialk
cat > iso/boot/grub/grub.cfg << EOF
menuentry "spk" {
	multiboot /boot/specialk
}
EOF
i686-elf-grub-mkrescue -o spk.iso iso