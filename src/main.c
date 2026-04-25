#include <signal.h>
#include <ncurses.h>
#include "str_utils.h"
#include "menu.h"
#include "game.h"
#include "display.h"
#include "state.h"
#include "grid.h"

volatile sig_atomic_t status = 0;

static void signal_handler(int signo)
{
    status = signo;
}

static void init_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTERM, signal_handler);
}

int	main(void)
{
	WINDOW	*window;
	int		key;
	int		menu_choice;
	// bool	end;
	int		state;
	t_grid	game;
	srand(time(NULL));

	init_signals();

	window = initscr();
	noecho();
	cbreak();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	set_escdelay(25);

	state = MENU;
	menu_choice = 0;
	while (status == 0)
	{
		if (state == MENU)
		{
			key = menu(window, &menu_choice);
			if (key == '\n')
				state = INIT_GAME;
			if (key == 27)
				break;
			continue;
		}

		if (state == INIT_GAME)
		{
			int size = 4;
			if (menu_choice == 1)
				size = 5;
			game.max_size = size;
			init_game(&game);
			state = GAME;
			display_game(window);
		}

		if (state == GAME)
		{
			display_game(window);
			if (gameover(game))
				break ;
			int key = getch();
			bool pressed_arrow = true;
			if (key == 27)
				break;
			reinitiate_attributes(&game);
			switch (key)
			{
				case KEY_UP:
					go_up(&game);
					break ;
				case KEY_DOWN:
					go_down(&game);
					break ;
				case KEY_RIGHT:
					go_right(&game);
					break ;
				case KEY_LEFT:
					go_left(&game);
					break ;
				default :
					pressed_arrow = false;
					break ;
			}
			if (!pressed_arrow || !game.movements_counter)
				continue ;
			get_next_number(&game);
		}
	}

	echo();
	nocbreak();
	curs_set(1);
	endwin();
	print_grid(&game);
	return (0);
}
