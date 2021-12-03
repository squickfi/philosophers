/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 02:24:07 by squickfi          #+#    #+#             */
/*   Updated: 2021/12/04 02:32:30 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_philo_info *data, int i)
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
		init_philo(data, i);
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

void	*live(t_philo *philo)
{
	while (philo->eat_times != philo->data->num_of_times_to_eat && \
		!philo->data->is_anyone_dead)
	{
		pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
		print_massage(TAKING_FORK, philo);
		pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
		print_massage(TAKING_FORK, philo);
		print_massage(EATING, philo);
		user_usleep(philo->data->time_to_eat);
		philo->last_eat_time = get_time();
		philo->eat_times++;
		pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
		if (philo->eat_times == philo->data->num_of_times_to_eat)
			break ;
		print_massage(SLEEPING, philo);
		user_usleep(philo->data->time_to_sleep);
		print_massage(THINKING, philo);
	}
	philo->data->fed_philos++;
	return (NULL);
}
