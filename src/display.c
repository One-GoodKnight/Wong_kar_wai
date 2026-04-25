#include <ncurses.h>

static void display_board()
{
	return;
}

void	display_game(WINDOW	*screen)
{
	int size_x = 0;
	int size_y = 0;
	getmaxyx(screen, size_y, size_x);

	erase();

	display_board();

	refresh();
}
