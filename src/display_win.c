#include <ncurses.h>
#include "grid.h"
#include "str_utils.h"

void	display_win(WINDOW	*screen, const char *dragon[27])
{
	int size_x = 0;
	int size_y = 0;
	getmaxyx(screen, size_y, size_x);

	(void)dragon;
	refresh();
}
