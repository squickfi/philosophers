/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 02:24:09 by squickfi          #+#    #+#             */
/*   Updated: 2021/12/04 23:35:26 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	check_death(t_philo_info *data)
{
	int				i;
	unsigned long	time;

	while (1)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			if (data->fed_philos == data->num_of_philos)
				return (FED);
			time = get_time();
			if (time - data->philo[i].last_eat_time >= \
				(unsigned long)data->time_to_die)
			{
				data->is_anyone_dead = 1;
				print_massage(DEAD, &data->philo[i]);
				return (DEAD);
			}
			i++;
		}
		usleep(1000);
	}
	return (ERROR);
}

void	create_threads(t_philo_info *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_create(&data->philo[i].thread, NULL, (void *)&live, \
			&data->philo[i]);
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < data->num_of_philos)
	{
		pthread_create(&data->philo[i].thread, NULL, (void *)&live, \
			&data->philo[i]);
		i += 2;
	}
}

void	join_threads_and_destroy_mutexes(t_philo_info *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo_info	data;
	int				philos_status;

	if (get_args(argc, argv, &data))
		return (1);
	if (init_philos_and_forks(&data))
		return (1);
	data.start_time = get_time();
	create_threads(&data);
	philos_status = check_death(&data);
	join_threads_and_destroy_mutexes(&data);
	free(data.fork);
	free(data.philo);
	return (philos_status);
}
