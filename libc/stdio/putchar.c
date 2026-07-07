#include <stdio.h>

#ifdef __is_libk
#include <kernel/tty.h>
#endif

int
putchar(int ic)
{
#ifdef __libk_k
	char c;
	c = (char) ic;

	tty_putchar(c);

#else
	/*TODO*/
#endif
	return ic;
}