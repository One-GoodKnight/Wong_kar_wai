#include <stdbool.h>
#include "str_utils.h"
#include "grid.h"
#include "state.h"
#include <signal.h>

void	init_game(t_grid *game)
{
	int	count;
	int	i;
	int	j;

	game->max_number = 0;
	game->total_score = 0;
	i = 0;
	while (i < game->max_size)
	{
		j = 0;
		while (j < game->max_size)
		{
			game->grid[i][j].number = 0;
			game->grid[i][j].merged = 0;
			j++;
		}
		i++;
	}
	count = 0;
	while (count < 2 && count_empty_cells(game))
	{
		choose_empty_cell(game);
		game->grid[game->chosen_x][game->chosen_y].number = choose_number();
		count++;
	}
	game->movements_counter = 0;
	i = 0;
	while (i < game->max_size)
	{
		j = 0;
		while (j < game->max_size)
		{
			if (game->grid[i][j].number > game->max_number)
				game->max_number = game->grid[i][j].number;
			j++;
		}
		i++;
	}
}

void	print_grid(t_grid *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->max_size)
	{
		j = 0;
		while (j < game->max_size)
		{
			printf("%d\t|", game->grid[i][j].number);
			j++;
		}
		printf("\n");
		printf("-----------------------------------------\n");
		i++;
	}
	if (i > 0)
		printf("=========================================\n");
}
