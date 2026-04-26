#ifndef DISPLAY_H
# define DISPLAY_H

#include <ncurses.h>
#include "grid.h"

void	display_grid(WINDOW	*screen, t_grid *grid, const char *digits[10][5]);

#endif
