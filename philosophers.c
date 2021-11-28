#include "philosophers.h"

unsigned int	ft_unsigned_atoi(char *str)
{
	size_t	num;

	num = 0;
	if (*str == '+')
		str++;
	while (ft_isalpha(*str))
	{
		num *= 10;
		num += *str;
		if (num > 4294967295)
		{
			printf("Error: arguments must be unsigned ints.\n");
			exit(1);
		}
		str++;
	}
	if (*str)
	{
		printf("Error: arguments must be unsigned ints.\n");
		exit(1);
	}
	return ((unsigned int)num);
}

t_philo_info get_args(int argc, char **argv)
{
	t_philo_info	info;

	if (argc != 5 || argc != 6)
	{
		printf("Error: wrong number of arguments.\n");
		exit(1);
	}
	info.num_of_philos = ft_unsigned_atoi(argv[1]);
	info.time_to_die = ft_unsigned_atoi(argv[2]);
	info.time_to_eat = ft_unsigned_atoi(argv[3]);
	info.time_to_sleep = ft_unsigned_atoi(argv[4]);
	if (argv[5])
		info.num_of_times_to_eat = ft_unsigned_atoi(argv[5]);
	else
		info.num_of_times_to_eat = -1;
	return (info);
}

int	main(int argc, char **argv)
{
	t_philo_info	info;

	info = get_args(argc, argv);
}