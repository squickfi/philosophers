#include "philosophers.h"

void	init_info(t_philo_info *info, char **argv)
{
	info->num_of_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		info->num_of_times_to_eat = ft_atoi(argv[5]);
	else
		info->num_of_times_to_eat = 0;
}

int	main(int argc, char **argv)
{
	t_philo_info	info;

	if (argc != 5 && argc != 6)
	{
		write(2, "Wrong number of arguments.\n", 27);
		return (1);
	}
	init_info(&info, argv);
}