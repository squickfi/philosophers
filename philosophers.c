#include "philosophers.h"

void	*check_philos(void)
{
	int	i;

	while (1)
	{
		write(1, "...\n", 4);
		i = 0;
		pthread_mutex_lock(&g_info.is_anyone_dead);
		g_info.end_time = get_time();
		while (i < g_info.num_of_philos)
		{
			if (get_time() - g_info.philo[i].last_eat_time > (long long)g_info.time_to_die)
			{
				printf("%lld %d died.\n", get_time() - g_info.start_time, i);
				g_info.is_dead = 1;
				pthread_mutex_unlock(&g_info.is_anyone_dead);
				return (NULL);
			}
			if (g_info.philo[i].eat_times == g_info.num_of_times_to_eat)
				g_info.fed_philos++;
			if (g_info.fed_philos == g_info.num_of_philos)
				// return (NULL);
			i++;
		}
		pthread_mutex_unlock(&g_info.is_anyone_dead);
		usleep(1000);/////!!!!
	}
}

int	init_info(char **argv)
{
	g_info.num_of_philos = ft_atoi(argv[1]);
	g_info.time_to_die = ft_atoi(argv[2]);
	g_info.time_to_eat = ft_atoi(argv[3]);
	g_info.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		g_info.num_of_times_to_eat = ft_atoi(argv[5]);
	else
		g_info.num_of_times_to_eat = 0;
	g_info.fed_philos = 0;
	g_info.is_dead = 0;
	g_info.philo = malloc(sizeof(t_philo) * g_info.num_of_philos);
	if (!g_info.philo)
		return (1);
	g_info.fork = malloc(sizeof(pthread_mutex_t) * g_info.num_of_philos);
	if (!g_info.fork)
	{
		free(g_info.philo);
		return (1);
	}
	return (0);
}

void	init_forks(void)
{
	int	i;

	i = 0;
	while (i < g_info.num_of_philos)
	{
		pthread_mutex_init(&g_info.fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < g_info.num_of_philos)
	{
		g_info.philo[i].philo_num = i + 1;
		g_info.philo[i].left_fork = i;
		if (i == g_info.num_of_philos - 1)
			g_info.philo[i].right_fork = 0;
		else
			g_info.philo[i].right_fork = i + 1;
		g_info.philo[i].last_eat_time = get_time();
		g_info.philo[i].eat_times = 0;
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		write(2, "Wrong number of arguments.\n", 27);
		return (1);
	}
	if (init_info(argv))
		return (1);
	i = 0;
	printf("%lld\n", get_time());
	init_forks();
	pthread_mutex_init(&g_info.write_to_terminal, NULL);
	pthread_mutex_init(&g_info.is_anyone_dead, NULL);
	g_info.start_time = get_time();
	pthread_create(&g_info.check_death, NULL, check_philos, NULL);
	while (i < g_info.num_of_philos)
	{
		if (!g_info.philo[i].philo_num % 2)
			usleep(200);
		pthread_create(&g_info.philo[i].thread, NULL, &live, &g_info.philo[i]);
		pthread_detach(g_info.philo[i].thread);
		i++;
	}
	// i = 0;
	// while (i < g_info.num_of_philos)
	// {
	// 	pthread_detach(g_info.philo[i].thread);
	// 	i++;
	// }
	pthread_join(g_info.check_death, NULL);
	write(1, "!!!\n", 4);
	return (0);
}