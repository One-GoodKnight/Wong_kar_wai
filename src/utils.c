#include "str_utils.h"
#include "grid.h"
#include <signal.h>

void	reinitiate_attributes(t_grid *game)
{
	int		i;
	int		j;

	i = 0;
	game->movements_counter = 0;
	while (i < game->max_size)
	{
		j = 0;
		while (j < game->max_size)
		{
			game->grid[i][j].merged = 0;
			j++;
		}
		i++;
	}
}

int	gameover(t_grid copy_game)
{
	if (go_up(&copy_game) || go_right(&copy_game)
		|| go_left(&copy_game) || go_down(&copy_game))
		return (0);
	return (1);
}

int	count_empty_cells(t_grid *game)
{
	int		i;
	int		j;

	i = 0;
	game->empty_cells = 0;
	while (i < game->max_size)
	{
		j = 0;
		while (j < game->max_size)
		{
			if (game->grid[i][j].number == 0)
				game->empty_cells++;
			j++;
		}
		i++;
	}
	return (game->empty_cells);
}
