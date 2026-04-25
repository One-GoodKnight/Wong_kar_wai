#include "str_utils.h"

int ft_strlen(const char *str)
{
	size_t i = 0;

	while (str[i])
		i++;
	return (i);
}
