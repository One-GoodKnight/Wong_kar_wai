#include "str_utils.h"
#include <signal.h>

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
	init_signals();
	while (status == 0)
	{
		continue;
	}
	printf("hi");
	return (0);
}
