#include "grid.h"
#include "str_utils.h"

static int	ft_negative(int nb, int fd)
{
	if (nb == -2147483648)
	{
		write(fd, "-214748364", 10);
		nb = 8;
	}
	else if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	return (nb);
}

static void	ft_putnbr_fd(int n, int fd)
{
	int		count;
	int		a;
	char	nb;

	n = ft_negative(n, fd);
	count = 1;
	a = n;
	while (a / 10 > 0)
	{
		a = a / 10;
		count = count * 10;
	}
	while (count > 1)
	{
		nb = n / count + '0';
		write(fd, &nb, 1);
		n = n % count;
		count = count / 10;
	}
	nb = n + '0';
	write(fd, &nb, 1);
	write(fd, "\n", 1);
}

void	save_file(t_grid game)
{
	int	fd;

	fd = open("best_scores.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return ;
	ft_putnbr_fd(game.total_score, fd);
	close(fd);
}
