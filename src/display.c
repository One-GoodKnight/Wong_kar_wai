#include <ncurses.h>
#include "grid.h"
#include "str_utils.h"

static void display_node(int x, int y, int node_size)
{
	attron(COLOR_PAIR(1));

	for (int i = 0; i < node_size * 2; i++)
		mvprintw((y * node_size), (x * node_size * 2) + i, "%c", ' ');
	for (int i = 0; i < node_size * 2; i++)
		mvprintw((y * node_size) + node_size - 1, (x * node_size * 2) + i, "%c", ' ');

	for (int j = 0; j < node_size; j++)
		mvprintw((y * node_size) + j, (x * node_size * 2), "%c", ' ');
	for (int j = 0; j < node_size; j++)
		mvprintw((y * node_size) + j, (x * node_size * 2) + (node_size * 2 - 1), "%c", ' ');

	attroff(COLOR_PAIR(1));
}

static void display_board(t_grid *grid, int node_size)
{
	for (int i = 0; i < grid->max_size; i++)
	{
		for (int j = 0; j < grid->max_size; j++)
		{
			display_node(i, j, node_size);
		}
	}
	return;
}

int calculate_node_size(int win_size_x, int win_size_y, int grid_size)
{
	int node_size;

	if (win_size_x < win_size_y)
		node_size = win_size_x / grid_size;
	else
		node_size = win_size_y / grid_size;
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
