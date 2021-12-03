/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 02:24:04 by squickfi          #+#    #+#             */
/*   Updated: 2021/12/04 02:29:31 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print_massage2(int flag, t_philo *philo)
{
	if (flag == SLEEPING)
	{
		printf("%ld %d is sleeping\n", (unsigned long)(get_time() - \
			philo->data->start_time), philo->philo_num);
		sem_post(philo->data->write);
		return ;
	}
	if (flag == THINKING)
	{
		printf("%ld %d is thinking\n", (unsigned long)(get_time() - \
			philo->data->start_time), philo->philo_num);
		sem_post(philo->data->write);
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
	sem_wait(philo->data->write);
	if (flag == TAKING_FORK)
	{
		printf("%ld %d has taken a fork\n", (unsigned long)(get_time() - \
			philo->data->start_time), philo->philo_num);
		sem_post(philo->data->write);
		return ;
	}
	if (flag == EATING)
	{
		printf("%ld %d is eating\n", (unsigned long)(get_time() - \
			philo->data->start_time), philo->philo_num);
		sem_post(philo->data->write);
		return ;
	}
	print_massage2(flag, philo);
}

void	close_semaphores(t_philo_info *data)
{
	if (data->write != SEM_FAILED)
	{
		sem_unlink("p_write");
		sem_close(data->write);
	}
	if (data->forks != SEM_FAILED)
	{
		sem_unlink("p_forks");
		sem_close(data->forks);
	}
	if (data->kill != SEM_FAILED)
	{
		sem_unlink("p_kill");
		sem_close(data->kill);
	}
}

void	init_semaphores(t_philo_info *data)
{
	sem_unlink("p_write");
	data->write = sem_open("p_write", O_CREAT | O_EXCL, 0664, 1);
	if (data->write == SEM_FAILED)
	{
		close_semaphores(data);
		exit(1);
	}
	sem_unlink("p_kill");
	data->kill = sem_open("p_kill", O_CREAT | O_EXCL, 0664, 0);
	if (data->kill == SEM_FAILED)
	{
		close_semaphores(data);
		exit(1);
	}
	sem_unlink("p_forks");
	data->forks = sem_open("p_forks", O_CREAT | O_EXCL, 0664, \
		data->num_of_philos);
	if (data->kill == SEM_FAILED)
	{
		close_semaphores(data);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_philo_info	data;
	int				i;
	int				philos_status;

	if (get_args(argc, argv, &data))
		return (1);
	init_semaphores(&data);
	data.start_time = get_time();
	create_philos(&data);
	close_semaphores(&data);
	return (0);
}
