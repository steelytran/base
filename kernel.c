#include <stddef.h>
#include <stdint.h>

#define VGA_TEXT_WIDTH 80
#define VGA_TEXT_HEIGHT 25
#define VGA_TEXT_MEMORY 0xB8000

enum
{
	VGA_BLACK = 0,
	VGA_BLUE,
	VGA_GREEN,
	VGA_CYAN,
	VGA_RED,
	VGA_MAGENTA,
	VGA_BROWN,
	VGA_LIGHT_GREY,
	VGA_DARK_GREY,
	VGA_LIGHT_BLUE,
	VGA_LIGHT_GREEN,
	VGA_LIGHT_CYAN,
	VGA_LIGHT_RED,
	VGA_LIGHT_MAGENTA,
	VGA_YELLOW,
	VGA_WHITE
};

static inline uint8_t vga_entry_color(uint8_t, uint8_t);
static inline uint16_t vga_entry(unsigned char, uint8_t);

size_t strlen(const char*);

void term_init(void);
void term_setentry(char, uint8_t, size_t, size_t);
void kputchar(char);
void printk(const char*);
void kernel_main(void);

size_t term_row;
size_t term_col;
uint8_t term_color;
uint16_t* term_buffer = (uint16_t*) VGA_TEXT_MEMORY;

static
inline
uint8_t
vga_entry_color(uint8_t fg, uint8_t bg)
{
	return fg | bg << 4;
}

static
inline
uint16_t
vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t
strlen(const char* str)
{
	size_t len;

	len = 0;
	while(str[len])
		len++;

	return len;
}

void
term_init(void)
{
	size_t i, j;
	size_t offset;

	term_col = 0;
	term_row = 0;
	term_color = vga_entry_color(VGA_WHITE, VGA_BLACK);

	for(i = 0; i < VGA_TEXT_HEIGHT; i++){
		for(j = 0; j < VGA_TEXT_WIDTH; j++){
			offset = i * VGA_TEXT_WIDTH + j;
			term_buffer[offset] = vga_entry(' ', term_color);	
		}
	}
}

void
term_setentry(char c, uint8_t color, size_t x, size_t y)
{
	size_t offset;

	offset = y * VGA_TEXT_WIDTH + x;
	term_buffer[offset] = vga_entry(c, color);
}

void
kputchar(char c)
{
	if(c == '\n'){
		term_col = 0;
		term_row++;
	} else {
		term_setentry(c, term_color, term_col, term_row);
	
		if(++term_col == VGA_TEXT_WIDTH){
			term_col = 0;
			if(++term_row == VGA_TEXT_HEIGHT)
				term_row = 0;
		}
	}
}

void
printk(const char* string)
{
	size_t i;
	size_t size;

	size = strlen(string);

	for(i = 0; i < size; i++) {
		kputchar(string[i]);
	}
}

void 
kernel_main(void)
{
	term_init();
	printk("asdfsadjkh\n");
	printk("gfgdsf");
}
