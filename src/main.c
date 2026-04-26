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
	int		state;
	t_grid	game = {0};

	const char *digits[10][5] = {
		{
			"#####\0",
			"## ##\0",
			"## ##\0",
			"## ##\0",
			"#####\0",
		},
		{
			"#### \0",
			"  ## \0",
			"  ## \0",
			"  ## \0",
			"#####\0",
		},
		{
			"#####\0",
			"   ##\0",
			"#####\0",
			"##   \0",
			"#####\0",
		},
		{
			"#####\0",
			"   ##\0",
			"#####\0",
			"   ##\0",
			"#####\0",
		},
		{
			"##   \0",
			"##   \0",
			"#####\0",
			"   ##\0",
			"   ##\0",
		},
		{
			"#####\0",
			"##   \0",
			"#####\0",
			"   ##\0",
			"#####\0",
		},
		{
			"#####\0",
			"##   \0",
			"#####\0",
			"## ##\0",
			"#####\0",
		},
		{
			"#####\0",
			"   ##\0",
			"   ##\0",
			"   ##\0",
			"   ##\0",
		},
		{
			"#####\0",
			"## ##\0",
			"#####\0",
			"## ##\0",
			"#####\0",
		},
		{
			"#####\0",
			"## ##\0",
			"#####\0",
			"    #\0",
			"#####\0",
		},
	};

	const char *dragon[27] = {
        "                     \\\\     \\\\                        \0",
        "                   ) \\ \\  ) \\ \\                       \0",
        "                  \\   \\  \\____ \\                      \0",
        "                  ) \\ /  __    __\\                    \0",
        "                 \\   /  (_@\\   \\_@)                   \0",
        "                   \\(             \\                   \0",
        "               /^\\   \\     <<     _\\_                 \0",
        "             / //\\ \\   \\___  \\\\       \\               \0",
        "           // //  \\__\\/     \\  \\\\   ^ ^)              \0",
        "         //  // /            (___\\/\\  /               \0",
        "       //   // |         |          /   /-\\           \0",
        "     //   //__/       |           \\ | /     \\         \0",
        "   // __ /  /        /|  |         \\ \\ />   |         \0",
        "  /    /  (        /  |             \\ \\/   /          \0",
        " /          \\     <   |  |           \\    /           \0",
        "              \\     \\ |               \\  /            \0",
        "               |      \\  |             \\/             \0",
        "              /       |                 \\             \0",
        "      /-------\\   <---(  |               )            \0",
        "    /          \\__\\_\\(   (       *    )   )           \0",
        "  /      /-----/   / \\(__  (_________)   )            \0",
        " |      |         /    |                )             \0",
        " |      |       /       \\               /             \0",
        " |      \\____/           \\     |^|     |              \0",
        " |                     ___\\    / \\     /__            \0",
        " |              /-\\__/          \\/        \\__/-\\      \0",
        "  \\__________/-//\\_____/\\______/  \\_____/\\____/\\\\     \0",
	};

	time_t cur_time = time(NULL);
	srand(cur_time);
	int win_value = get_victory_number();

	init_signals();

	window = initscr();
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLUE); //borders
	init_pair(2, COLOR_YELLOW, COLOR_YELLOW); //numbers
	init_pair(3, COLOR_GREEN, COLOR_BLACK); //dragon
	init_pair(4, COLOR_WHITE, COLOR_WHITE); //dragon borders
	noecho();
	cbreak();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	set_escdelay(25);

	time_t start_win_message = 0;
	bool win_message_shown = false;
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
		}

		if (state == GAME)
		{
			if (game.max_number == 2048)
				break ;
			if (gameover(game))
				break;
			erase();
			display_grid(window, &game, digits);
			if (win_value > 0 && game.max_number >= win_value && !win_message_shown)
			{
				if (start_win_message == 0)
					start_win_message = time(NULL);
				display_win(window, dragon);
				if (time(NULL) - 4 >= start_win_message)
					win_message_shown = true;
			}
			refresh();
			int key = getch();
			if (game.max_number == 2048 || key == 27 || gameover(game))
			{
				save_file(game);
				break ;
			}
			reinitiate_attributes(&game);
			bool pressed_arrow = true;
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
	print_grid(&game); /////////////////////// erase later
	return (0);
}
