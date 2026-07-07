#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

size_t tty_row;
size_t tty_col;
uint8_t tty_color;
uint16_t* tty_buffer = (uint16_t*) VGA_TEXT_MEMORY;

void
tty_init(void)
{
	size_t i, j;
	size_t offset;

	tty_col = 0;
	tty_row = 0;
	tty_color = vga_entry_color(VGA_YELLOW, VGA_RED);

	for(i = 0; i < VGA_TEXT_HEIGHT; i++){
		for(j = 0; j < VGA_TEXT_WIDTH; j++){
			offset = i * VGA_TEXT_WIDTH + j;
			tty_buffer[offset] = vga_entry(' ', tty_color);	
		}
	}
}
void
tty_setentry(char c, uint8_t color, size_t x, size_t y)
{
	size_t offset;

	offset = y * VGA_TEXT_WIDTH + x;
	tty_buffer[offset] = vga_entry(c, color);
}

void
tty_scroll(void)
{
	size_t i, j;
	size_t offset;

	for(i = 0; i < VGA_TEXT_HEIGHT - 1; i++){
		for(j = 0; j < VGA_TEXT_WIDTH; j++){
			offset = i * VGA_TEXT_WIDTH + j;
			tty_buffer[offset] = tty_buffer[offset + VGA_TEXT_WIDTH];
		}
	}
}

void
tty_newline(void)
{
	tty_col = 0;
	if(tty_row+1 == VGA_TEXT_HEIGHT)
		tty_scroll();
	else tty_row++;
}

void
tty_putchar(char c)
{
	if(c == '\n')
		tty_newline();
	else {
		tty_setentry(c, tty_color, tty_col, tty_row);
		if(++tty_col == VGA_TEXT_WIDTH)
			tty_newline();
	}
}

void
tty_print(const char* string)
{
	size_t i;
	size_t size;

	size = strlen(string);

	for(i = 0; i < size; i++) {
		tty_putchar(string[i]);
	}
}
