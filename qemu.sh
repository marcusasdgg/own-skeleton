#!/bin/sh
set -e
unset GTK_PATH
qemu-system-i386 -cdrom myos.iso -serial file:serial_output.txt
