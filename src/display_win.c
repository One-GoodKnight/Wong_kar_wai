#include <ncurses.h>
#include "grid.h"
#include "str_utils.h"

static void display_border(int x, int y, int size)
{
	int height = 27;

	for (int i = 0; i < size + 2; i++)
		mvprintw(y, x + i, "%c", ' ');

	for (int i = 0; i < size + 2; i++)
		mvprintw(y + height, x + i, "%c", ' ');

	for (int i = 0; i < height + 1; i++)
		mvprintw(y + i, x - 1, "%s", "  ");

	for (int i = 0; i < height + 1; i++)
		mvprintw(y + i, x + size, "%s", "  ");
}

static void	display_message(int x, int y)
{
	mvprintw(y, x, "%s", "GG, you won.");
}

void	display_win(WINDOW	*screen, const char *dragon[27])
{
	int line_len = ft_strlen(dragon[0]);
	int size_x = 0;
	int size_y = 0;
	getmaxyx(screen, size_y, size_x);
	int start_x = size_x / 2 - line_len / 2;
	int start_y = size_y / 2 - 27 / 2;

	attron(COLOR_PAIR(3));
	for (int i = 0; i < 27; ++i)
	{
		line_len = ft_strlen(dragon[i]);
		for (int j = 0; j < line_len; j++)
		{
			mvprintw(start_y + i, start_x + j, "%c", dragon[i][j]);
		}
	}
	display_message(start_x + line_len - 13, start_y + 9);
	attroff(COLOR_PAIR(3));
	attron(COLOR_PAIR(4));
	display_border(start_x - 1, start_y - 1, line_len);
	attroff(COLOR_PAIR(4));
}
