/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 02:24:00 by squickfi          #+#    #+#             */
/*   Updated: 2021/12/04 02:29:37 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*check_death(t_philo *philo)
{
	unsigned long	time;

	while (1)
	{
		time = get_time();
		if (time - philo->last_eat_time >= \
			(unsigned long)philo->data->time_to_die)
		{
			sem_post(philo->data->kill);
			print_massage(DEAD, philo);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	user_usleep(int	time_to_wait)
{
	unsigned long	time;

	time = get_time();
	while (get_time() < time + (unsigned long)time_to_wait)
		usleep(100);
}

void	life_cycle(t_philo *philo)
{
	while (philo->eat_times != philo->data->num_of_times_to_eat)
	{
		sem_wait(philo->data->forks);
		print_massage(TAKING_FORK, philo);
		sem_wait(philo->data->forks);
		print_massage(TAKING_FORK, philo);
		print_massage(EATING, philo);
		user_usleep(philo->data->time_to_eat);
		philo->last_eat_time = get_time();
		philo->eat_times++;
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		if (philo->eat_times == philo->data->num_of_times_to_eat)
			exit (0);
		print_massage(SLEEPING, philo);
		user_usleep(philo->data->time_to_sleep);
		print_massage(THINKING, philo);
	}
}

void	*live(t_philo_info *data, int i)
{
	t_philo	philo;

	philo.philo_num = i + 1;
	philo.data = data;
	philo.eat_times = 0;
	philo.last_eat_time = get_time();
	pthread_create(&philo.dead, NULL, (void *)&check_death, &philo);
	pthread_detach(philo.dead);
	life_cycle(&philo);
	exit(0);
}
