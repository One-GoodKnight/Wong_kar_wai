#ifndef DISPLAY_H
# define DISPLAY_H

#include <ncurses.h>
#include "grid.h"

void	display_grid(WINDOW	*screen, t_grid *grid, const char *digits[10][5]);
void	display_win(WINDOW	*screen, const char *dragon[27]);
bool	display_ascii_number(int x, int y, int node_size, int number, const char *digits[10][5], bool score);
void	display_score(int n, const char *digits[10][5]);
int		total_number_length(int number, const char *digits[10][5]);

#endif
