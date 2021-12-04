/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 02:24:08 by squickfi          #+#    #+#             */
/*   Updated: 2021/12/04 23:28:58 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	print_massage2(int flag, t_philo *philo)
{
	if (flag == SLEEPING)
	{
		printf("%ld %d is sleeping\n", (unsigned long)(get_time() - \
			philo->data->start_time), philo->philo_num);
		return (0);
	}
	if (flag == THINKING)
	{
		printf("%ld %d is thinking\n", (unsigned long)(get_time() - \
			philo->data->start_time), philo->philo_num);
		return (0);
	}
	if (flag == DEAD)
	{
		printf("%ld %d is dead\n", (unsigned long)(get_time() - \
			philo->data->start_time), philo->philo_num);
		return (0);
	}
	return (0);
}

int	print_massage(int flag, t_philo *philo)
{
	if (philo->data->is_anyone_dead && flag != DEAD)
		return (1);
	if (flag == TAKING_FORK)
	{
		printf("%ld %d has taken a fork\n", (unsigned long)(get_time() - \
			philo->data->start_time), philo->philo_num);
		return (0);
	}
	if (flag == EATING)
	{
		printf("%ld %d is eating\n", (unsigned long)(get_time() - \
			philo->data->start_time), philo->philo_num);
		return (0);
	}
	return (print_massage2(flag, philo));
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
