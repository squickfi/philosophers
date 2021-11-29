#include "philosophers.h"

int	ft_atoi(char *str)
{
	ssize_t	num;
	
	num = 0;
	while (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num *= 10;
		num += *str - '0';
		if (num > 2147483647)
			return (-1);
		str++;
	}
	if (*str)
		return (-1);
	return (num);
}