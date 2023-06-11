#include "k210_uarths.h"

int main(void)
{
	k210_putc('K');
	k210_putc('2');
	k210_putc('1');
	k210_putc('0');
	k210_putc('\r');
	k210_putc('\n');
	return 0;
}
