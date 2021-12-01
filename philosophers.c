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
			return (-2);
		str++;
	}
	if (*str)
		return (-2);
	if (num == 0)
		return (-2);
	return (num);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	check_args(t_philo_info *data)
{
	if (data->num_of_philos == -2 || data->time_to_die == -2 || \
		data->time_to_eat == -2 || data->time_to_sleep == -2 || \
		data->num_of_times_to_eat == -2)
	{
		printf("All arguments must be positive ints.\n");
		return (1);
	}
	if (data->num_of_philos > 200)
	{
		printf("Too many philosoohers, try 200 or less.\n");
		return (1);
	}
	return (0);
}

int	get_args(int argc, char **argv, t_philo_info *data)
{
	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of arguments.\n");
		return (1);
	}
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->num_of_times_to_eat = ft_atoi(argv[5]);
	else
		data->num_of_times_to_eat = -1;
	if (check_args(data))
		return (1);
	data->fed_philos = 0;
	data->is_anyone_dead = 0;
	return (0);
}

int	init_philos_and_forks(t_philo_info *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philo)
		return (1);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->fork)
	{
		free(data->philo);
		return (1);
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		data->philo[i].philo_num = i + 1;
		data->philo[i].left_fork = i;
		if (i == data->num_of_philos - 1)
			data->philo[i].right_fork = 0;
		else
			data->philo[i].right_fork = i + 1;
		data->philo[i].data = data;
		data->philo[i].eat_times = 0;
		data->philo[i].last_eat_time = get_time();
		i++;
	}
	return (0);
}

void	user_usleep(int	time_to_wait)
{
	unsigned long	time;

	time = get_time();
	while (get_time() < time + (unsigned long)time_to_wait)
		usleep(100);
}

void	print_massage(int flag, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write_to_terminal);
	if (flag == TAKING_FORK)
	{
		printf("%ld %d has taken a fork\n", (unsigned long)(get_time() - philo->data->start_time), philo->philo_num);
		pthread_mutex_unlock(&philo->data->write_to_terminal);
		return ;
	}
	if (flag == EATING)
	{
		printf("%ld %d is eating\n", (unsigned long)(get_time() - philo->data->start_time), philo->philo_num);
		pthread_mutex_unlock(&philo->data->write_to_terminal);
		return ;
	}
	if (flag == SLEEPING)
	{
		printf("%ld %d is sleeping\n", (unsigned long)(get_time() - philo->data->start_time), philo->philo_num);
		pthread_mutex_unlock(&philo->data->write_to_terminal);
		return ;
	}
	if (flag == THINKING)
	{
		printf("%ld %d is thinking\n", (unsigned long)(get_time() - philo->data->start_time), philo->philo_num);
		pthread_mutex_unlock(&philo->data->write_to_terminal);
		return ;
	}
	if (flag == DEAD)
	{
		printf("%ld %d id dead\n", (unsigned long)(get_time() - philo->data->start_time), philo->philo_num);
		return ;
	}
}

void	*live(t_philo *philo)
{
	while (philo->eat_times != philo->data->num_of_times_to_eat && !philo->data->is_anyone_dead)
	{
		pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
		print_massage(TAKING_FORK, philo);
		pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
		print_massage(TAKING_FORK, philo);
		philo->last_eat_time = get_time();
		print_massage(EATING, philo);
		user_usleep(philo->data->time_to_eat);
		philo->eat_times++;
		pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
		print_massage(SLEEPING, philo);
		user_usleep(philo->data->time_to_sleep);
		print_massage(THINKING, philo);
	}
	philo->data->fed_philos++;
	return (NULL);
}

int	check_death(t_philo_info *data)
{
	int			i;
	unsigned long	time;

	i = 0;
	while (1)
	{
		// if (i == data->num_of_philos - 1)
			i = 0;
		while (i < data->num_of_philos)
		{
			time = get_time();
			if (time - data->philo[i].last_eat_time >= (unsigned long)data->time_to_die)
			{
				data->is_anyone_dead = 1;
				print_massage(DEAD, &data->philo[i]);
				return (DEAD);
			}
			// printf("!!!!!!!%d\n", i);
			if (data->fed_philos == data->num_of_times_to_eat)
				return (FED);
			i++;
		}
		usleep(1000);
	}
	return (ERROR);
}

int	main(int argc, char **argv)
{
	t_philo_info	data;
	int				i;
	int				philos_status;

	if (get_args(argc, argv, &data))
		return (1);
	if (init_philos_and_forks(&data))
		return (1);
	pthread_mutex_init(&data.write_to_terminal, NULL);
	// printf("%d\n", data.num_of_times_to_eat);
	// return (0);
	data.start_time = get_time();
	i = 0;
	while (i < data.num_of_philos)
	{
		pthread_create(&data.philo[i].thread, NULL, (void *)&live, &data.philo[i]);
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < data.num_of_philos)
	{
		pthread_create(&data.philo[i].thread, NULL, (void *)&live, &data.philo[i]);
		i += 2;
	}
	philos_status = check_death(&data);
	i = 0;
	while (i < data.num_of_philos)
	{
		pthread_detach(data.philo[i].thread);
		pthread_mutex_destroy(&data.fork[i]);
		i++;
	}
	pthread_mutex_unlock(&data.write_to_terminal);
	pthread_mutex_destroy(&data.write_to_terminal);
	return (philos_status);
}