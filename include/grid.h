#ifndef GRID_H
# define GRID_H

# inc

# define SIZE 4

typedef struct s_grid
{
	t_node grid[SIZE][SIZE];
}	t_grid;

typedef struct s_node
{
	int number;
	bool merged;
}	t_node;

#endif
