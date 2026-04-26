#include "str_utils.h"
#include "grid.h"
#include <signal.h>

static void	merge(t_node *current, t_node *neighbor, t_grid *game)
{
	neighbor->number *= 2;
	current->number = 0;
	neighbor->merged = 1;
	game->total_score += neighbor->number;
	if (neighbor->number > game->max_number)
		game->max_number = neighbor->number;
}

int	go_right(t_grid *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->max_size)
	{
		j = game->max_size - 2;
		while (j >= 0)
		{
			if (game->grid[i][j].merged == 1 || j == game->max_size - 1
				|| game->grid[i][j].number == 0)
				j--;
			else if (game->grid[i][j + 1].number == 0)
			{
				game->grid[i][j + 1].number = game->grid[i][j].number;
				game->grid[i][j].number = 0;
				game->movements_counter++;
				j++;
			}
			else if (game->grid[i][j + 1].number == game->grid[i][j].number
				&& game->grid[i][j + 1].merged == 0)
			{
				merge(&game->grid[i][j], &game->grid[i][j + 1], game);
				game->movements_counter++;
				j++;
			}
			else
				j--;
		}
		i++;
	}
	return (game->movements_counter);
}

int	go_left(t_grid *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->max_size)
	{
		j = 1;
		while (j < game->max_size)
		{
			if (game->grid[i][j].merged == 1 || j == 0
				|| game->grid[i][j].number == 0)
				j++;
			else if (game->grid[i][j - 1].number == 0)
			{
				game->grid[i][j - 1].number = game->grid[i][j].number;
				game->grid[i][j].number = 0;
				game->movements_counter++;
				j--;
			}
			else if (game->grid[i][j - 1].number == game->grid[i][j].number
				&& game->grid[i][j - 1].merged == 0)
			{
				merge(&game->grid[i][j], &game->grid[i][j - 1], game);
				game->movements_counter++;
				j--;
			}
			else
				j++;
		}
		i++;
	}
	return (game->movements_counter);
}

int	go_up(t_grid *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->max_size)
	{
		j = 1;
		while (j < game->max_size)
		{
			if (game->grid[j][i].merged == 1 || j == 0
				|| game->grid[j][i].number == 0)
				j++;
			else if (game->grid[j - 1][i].number == 0)
			{
				game->grid[j - 1][i].number = game->grid[j][i].number;
				game->grid[j][i].number = 0;
				game->movements_counter++;
				j--;
			}
			else if (game->grid[j - 1][i].number == game->grid[j][i].number
				&& game->grid[j - 1][i].merged == 0)
			{
				merge(&game->grid[j][i], &game->grid[j - 1][i], game);
				game->movements_counter++;
				j--;
			}
			else
				j++;
		}
		i++;
	}
	return (game->movements_counter);
}

int	go_down(t_grid *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->max_size)
	{
		j = game->max_size - 2;
		while (j >= 0)
		{
			if (game->grid[j][i].merged == 1 || j == game->max_size - 1
				|| game->grid[j][i].number == 0)
				j--;
			else if (game->grid[j + 1][i].number == 0)
			{
				game->grid[j + 1][i].number = game->grid[j][i].number;
				game->grid[j][i].number = 0;
				game->movements_counter++;
				j++;
			}
			else if (game->grid[j + 1][i].number == game->grid[j][i].number
				&& game->grid[j + 1][i].merged == 0)
			{
				merge(&game->grid[j][i], &game->grid[j + 1][i], game);
				game->movements_counter++;
				j++;
			}
			else
				j--;
		}
		i++;
	}
	return (game->movements_counter);
}
