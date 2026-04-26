#include "str_utils.h"
#include "grid.h"
#include <signal.h>

void	get_next_number(t_grid *game)
{
	choose_empty_cell(game);
	game->grid[game->chosen_x][game->chosen_y].number = choose_number();
}

void	choose_empty_cell(t_grid *game)
{
	int	rand_num;
	int	i;
	int	j;
	int	index;

	i = 0;
	j = 0;
	index = 0;
	count_empty_cells(game);
	rand_num = rand() % (game->empty_cells);
	while (i < game->max_size)
	{
		j = 0;
		while (j < game->max_size)
		{
			if (game->grid[i][j].number == 0)
			{
				if (index == rand_num)
				{
					game->chosen_x = i;
					game->chosen_y = j;
					return ;
				}
				index++;
			}
			j++;
		}
		i++;
	}
}

int	choose_number(void)
{
	int	rand_num;
	int	new_number;

	rand_num = rand() % 5;
	if (rand_num < 3)
		new_number = 2;
	else
		new_number = 4;
	return (new_number);
}
