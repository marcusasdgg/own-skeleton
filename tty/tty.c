#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "../string.h"

#include "../tty.h"
#include "../io.h"

#include "vga.h"

#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_setcursor(size_t x, size_t y);

void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_setcursor(terminal_row,terminal_column);
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcursor(size_t x, size_t y){
	uint16_t cursor = y*80 + x;
	out_b(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	out_b(FB_DATA_PORT, cursor >> 8);
	out_b(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    out_b(FB_DATA_PORT, cursor);
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
	unsigned char uc = c;
	if (c == '\n'){
		terminal_column = 0;
		terminal_row++;
		terminal_setcursor(terminal_column,terminal_row);
		return;
	}
	if (c == '\0')
		return;
	terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
	terminal_setcursor(terminal_column,terminal_row);
}

