#include <ncurses.h>
#include "grid.h"
#include "display.h"

void	display_score(int n, const char *digits[10][5])
{
	attron(COLOR_PAIR(2));
	int x_offset = total_number_length(n, digits) / 2;
	display_ascii_number(x_offset + 2, 4, 0, n, digits, true);
	attroff(COLOR_PAIR(2));
}
