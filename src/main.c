#include <signal.h>
#include <ncurses.h>
#include "str_utils.h"
#include "menu.h"
#include "game.h"
#include "display.h"
#include "state.h"

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
	bool	end;
	int		state;

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
			//init grid
			state = GAME;
		}

		if (state == GAME)
		{
			end = game_loop();
			if (end)
				break;
			display_game(window);
		}
			

	}

	echo();
	nocbreak();
	curs_set(1);

	printf("hi");
	return (0);
}
