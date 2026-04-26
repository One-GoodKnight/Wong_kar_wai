#include <ncurses.h>
#include "grid.h"
#include "str_utils.h"
#include "stdbool.h"

static void display_node_border(int x, int y, int node_size, int grid_offset_x, int grid_offset_y)
{
	attron(COLOR_PAIR(1));

	int x_start = x * node_size * 2 + grid_offset_x;
	int y_start = y * node_size + grid_offset_y;
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

static int total_number_length(int number, const char *digits[10][5])
{
	int digit;
	int digit_x_len;
	int len = 0;
	
	while (number != 0)
	{
		digit = number % 10;
		digit_x_len = ft_strlen(digits[digit][0]);
		len += digit_x_len + 1;
		number /= 10;
	}
	return (len);
}

static void display_ascii_digit(int x, int y, const char **digit_ascii, int digit_ascii_len)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < digit_ascii_len; j++)
		{
			if (digit_ascii[i][j] == '#')
			{
				mvprintw(y + i, x + j, "%c", ' ');
			}
		}
	}
}

static bool display_ascii_number(int x, int y, int node_size, int number, const char *digits[10][5])
{
	int digits_in_number[4] = {-1, -1, -1, -1};
	int digit;
	int digit_x_len;
	int cur_digit_x_offset = 0;
	int number_x_offset = total_number_length(number, digits) / 2;

	if (total_number_length(number, digits) + 3 > node_size * 2 || (5 + 3) > node_size)
		return false;
	attron(COLOR_PAIR(2));
	int i = 3;
	while (number != 0 && i >= 0)
	{
		digit = number % 10;
		digits_in_number[i] = digit;
		number /= 10;
		i--;
	}
	for (i = 0; i < 4; i++)
	{
		digit = digits_in_number[i];
		if (digit == -1)
			continue;
		digit_x_len = ft_strlen(digits[digit][0]);
		display_ascii_digit(x + cur_digit_x_offset - number_x_offset, y - 2, digits[digit], digit_x_len);
		cur_digit_x_offset += digit_x_len + 1;
	}
	attroff(COLOR_PAIR(2));
	return true;
}

static int get_number_of_digits(int number)
{
	int	n = 1;

	while (number != 0)
	{
		n++;
		number /= 10;
	}
	return (n);
}

static void display_number(int x, int y, int node_size, int number, const char *digits[10][5], int grid_offset_x, int grid_offset_y)
{
	int x_start = x * node_size * 2 + grid_offset_x;
	int y_start = y * node_size + grid_offset_y;
	int char_x = node_size * 2;
	int char_y = node_size;
	
	bool displayed = display_ascii_number(x_start + char_x / 2, y_start + char_y / 2, node_size, number, digits);
	if (!displayed)
	{
		int number_of_digits = get_number_of_digits(number);
		number_of_digits = 2;
		mvprintw(y_start + char_y / 2, x_start + char_x / 2 - number_of_digits + 1, "%d", number);
	}
}

static void display_board(t_grid *grid, int node_size, const char *digits[10][5], int grid_offset_x, int grid_offset_y)
{
	for (int i = 0; i < grid->max_size; i++)
	{
		for (int j = 0; j < grid->max_size; j++)
		{
			display_node_border(i, j, node_size, grid_offset_x, grid_offset_y);
			if (grid->grid[j][i].number != 0)
				display_number(i, j, node_size, grid->grid[j][i].number, digits, grid_offset_x, grid_offset_y);
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

void	display_grid(WINDOW	*screen, t_grid *grid, const char *digits[10][5])
{
	int size_x = 0;
	int size_y = 0;
	getmaxyx(screen, size_y, size_x);

	int node_size = calculate_node_size(size_x, size_y, grid->max_size);
	int	grid_offset_x = size_x / 2 - node_size * 2 * grid->max_size / 2;
	int	grid_offset_y = size_y / 2 - node_size * grid->max_size / 2;

	erase();

	display_board(grid, node_size, digits, grid_offset_x, grid_offset_y);

	refresh();
}
