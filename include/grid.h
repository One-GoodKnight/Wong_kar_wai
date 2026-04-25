#ifndef GRID_H
# define GRID_H

typedef struct s_node
{
	int	number;
	int	merged;
}	t_node;

typedef struct s_grid
{
	int		max_size;
	int		movements_counter;
	int		empty_cells;
	int		chosen_x;
	int		chosen_y;
	t_node	grid[5][5];
}	t_grid;

// movement
int		go_right(t_grid *game);
int		go_left(t_grid *game);
int		go_up(t_grid *game);
int		go_down(t_grid *game);

// random
void	get_next_number(t_grid *game);
void	choose_empty_cell(t_grid *game);
int		choose_number(void);

// utils
int		count_empty_cells(t_grid *game);
void	reinitiate_attributes(t_grid *game);
int		gameover(t_grid copy_game);

void	print_grid(t_grid *game);
void	init_game(t_grid *game);

#endif
