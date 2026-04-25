#include "str_utils.h"
#include <ncurses.h>

static void display_menu(WINDOW *window, int choice)
{
	const char *options[] = { "4x4 grid", "5x5 grid (Ur weird)" };
	const char *header = "Choose grid size :";
	int size_x = 0;
	int size_y = 0;
	getmaxyx(window, size_y, size_x);
	int mid_y = size_y / 2;
	int mid_x = size_x / 2;

	//erase();
	mvprintw(mid_y - 3, mid_x - ft_strlen(header) / 2, "%s", header);
	for (int i = 0; i < 2; i++)
	{
		if (i == choice)
			attron(A_REVERSE);
		mvprintw(mid_y + (i * 2), mid_x - ft_strlen(options[i]) / 2, "%s", options[i]);
		if (i == choice)
			attroff(A_REVERSE);
	}
	refresh();
}

int menu(WINDOW *window, int *choice)
{
	int ch;

	display_menu(window, *choice);
	ch = getch();
	switch (ch)
	{
		case KEY_UP:
			*choice = (*choice + 2 - 1) % 2;
			break;
		case KEY_DOWN:
			*choice = (*choice + 1) % 2;
			break;
		case '\n':
			return '\n';
		case 27:
			return 27;
	}

	return (0);
}

/*
int show_mode_menua()
{
	const char *options[] = { "4x4 grid", "5x5 grid (Ur weird)" };
	int choice = 0;
	int ch;

	nodelay(stdscr, FALSE);
	while (1)
	{
		erase();
		int mid_y = LINES / 2;
		int mid_x = COLS / 2;
		mvprintw(mid_y - 3, mid_x - 10, "Choose game mode:");
		for (int i = 0; i < 2; i++)
		{
			if (i == choice)
				attron(A_REVERSE);
			mvprintw(mid_y - 1 + i * 2, mid_x - (int)strlen(options[i]) / 2, "%s", options[i]);
			if (i == choice)
				attroff(A_REVERSE);
		}
		mvprintw(mid_y + 4, mid_x - 16, "Use UP/DOWN, Enter to select, Esc to cancel");
		refresh();

		ch = getch();
		switch (ch)
		{
			case KEY_UP:
				choice = (choice + 2 - 1) % 2;
				break;
			case KEY_DOWN:
				choice = (choice + 1) % 2;
				break;
			case 10:
			case KEY_ENTER:
				nodelay(stdscr, TRUE);
				return choice;
			case 27:
				nodelay(stdscr, TRUE);
				return 0;
		}
	}
}
*/
