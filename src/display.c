#include <ncurses.h>
#include "grid.h"
#include "str_utils.h"

static void display_node_border(int x, int y, int node_size)
{
	attron(COLOR_PAIR(1));

	int x_start = x * node_size * 2;
	int y_start = y * node_size;
	int char_x = node_size * 2;
	int char_y = node_size;
	for (int i = 0; i < char_x; i++)
		mvprintw(y_start, x_start + i, "%c", ' ');

	for (int i = 0; i < char_x; i++)
		mvprintw(y_start + node_size, x_start + i, "%c", ' ');

	for (int j = 0; j < char_y + 1; j++)
	{
		mvprintw(y_start + j, x_start, "%c", ' ');
	}

	for (int j = 0; j < char_y + 1; j++)
	{
		mvprintw(y_start + j, x_start + char_x - 1, "%c", ' ');
	}

	attroff(COLOR_PAIR(1));
}

static void display_board_number(int x, int y, int node_size, int number)
{
	int x_start = x * node_size * 2;
	int y_start = y * node_size;
	int char_x = node_size * 2;
	int char_y = node_size;
	
	mvprintw(y_start + char_y / 2, x_start + char_x / 2, "%d", number);
}

static void display_board(t_grid *grid, int node_size)
{
	for (int i = 0; i < grid->max_size; i++)
	{
		for (int j = 0; j < grid->max_size; j++)
		{
			display_node_border(i, j, node_size);
			if (grid->grid[j][i].number != 0)
				display_board_number(i, j, node_size, grid->grid[j][i].number);
		}
	}
	return;
}

int calculate_node_size(int win_size_x, int win_size_y, int grid_size)
{
	int node_size;

	if ((win_size_x / 2) < win_size_y)
		node_size = (win_size_x / 2) / grid_size;
	else
		node_size = win_size_y / grid_size;
	if (node_size > 1)
		node_size -= 1;
	return node_size;
}

void	display_game(WINDOW	*screen, t_grid *grid)
{
	int size_x = 0;
	int size_y = 0;
	getmaxyx(screen, size_y, size_x);

	int node_size = calculate_node_size(size_x, size_y, grid->max_size);

	erase();

	display_board(grid, node_size);

	refresh();
}
