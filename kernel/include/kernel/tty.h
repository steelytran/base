#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

void tty_init(void);
void tty_scroll(void);
void tty_newline(void);
void tty_putchar(char);
void tty_print(const char*);

#endif
