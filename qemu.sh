#!/bin/sh
set -e

qemu-system-i386 -cdrom myos.iso -serial file:serial_output.txt
