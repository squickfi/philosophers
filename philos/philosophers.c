/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 02:24:09 by squickfi          #+#    #+#             */
/*   Updated: 2021/12/04 02:32:48 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_massage2(int flag, t_philo *philo)
{
	if (flag == SLEEPING)
	{
		printf("%ld %d is sleeping\n", (unsigned long)(get_time() - \
			philo->data->start_time), philo->philo_num);
		pthread_mutex_unlock(&philo->data->write_to_terminal);
		return ;
	}
	if (flag == THINKING)
	{
		printf("%ld %d is thinking\n", (unsigned long)(get_time() - \
			philo->data->start_time), philo->philo_num);
		pthread_mutex_unlock(&philo->data->write_to_terminal);
		return ;
	}
	if (flag == DEAD)
	{
		printf("%ld %d is dead\n", (unsigned long)(get_time() - \
			philo->data->start_time), philo->philo_num);
		return ;
	}
}

void	print_massage(int flag, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write_to_terminal);
	if (flag == TAKING_FORK)
	{
		printf("%ld %d has taken a fork\n", (unsigned long)(get_time() - \
			philo->data->start_time), philo->philo_num);
		pthread_mutex_unlock(&philo->data->write_to_terminal);
		return ;
	}
	if (flag == EATING)
	{
		printf("%ld %d is eating\n", (unsigned long)(get_time() - \
			philo->data->start_time), philo->philo_num);
		pthread_mutex_unlock(&philo->data->write_to_terminal);
		return ;
	}
	print_massage2(flag, philo);
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
		pthread_detach(data->philo[i].thread);
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < data->num_of_philos)
	{
		pthread_create(&data->philo[i].thread, NULL, (void *)&live, \
			&data->philo[i]);
		pthread_detach(data->philo[i].thread);
		i += 2;
	}
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
	data.start_time = get_time();
	create_threads(&data);
	philos_status = check_death(&data);
	i = 0;
	while (i < data.num_of_philos)
	{
		pthread_mutex_destroy(&data.fork[i]);
		i++;
	}
	free(data.fork);
	free(data.philo);
	pthread_mutex_unlock(&data.write_to_terminal);
	pthread_mutex_destroy(&data.write_to_terminal);
	return (philos_status);
}
