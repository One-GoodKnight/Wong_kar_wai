<<<<<<< HEAD
#include <stdbool.h>

bool game_loop(void)
{
	return false;
=======
#include "str_utils.h"
#include "grid.h"
#include <signal.h>

void	init_game(t_grid *game)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < game->max_size)
	{
		j = 0;
		while (j < game->max_size)
		{
			game->grid[i][j].number = 2; ///////////// change to 0 after
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
	printf("=========================================\n");
}

int	main(void)
{
	t_grid	game;
	srand(time(NULL));
	int		i = 0; ////////////////////////erase later

	game.max_size = 4; // it can be 4 or 5, get this value from menu
	init_game(&game);
	while (i < 5) ///////////// change to !gameover(game)
	{
		reinitiate_attributes(&game);
		while (!go_right(&game) && i < 5) /////////// change to users decision
		{
			printf("Cant move\n"); ////////// erase this later
			i++; ///////////////////// erase this later
			continue ;
		}
		get_next_number(&game);
		print_grid(&game);
	}
>>>>>>> b223fbd (game logic)
}
