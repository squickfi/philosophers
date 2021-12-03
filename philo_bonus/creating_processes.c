/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 02:24:02 by squickfi          #+#    #+#             */
/*   Updated: 2021/12/04 02:29:24 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	fork_philos(t_philo_info *data, int *pid)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			perror("Error");
			while (i >= 0)
			{
				kill(pid[i], SIGKILL);
				i--;
			}
			exit(1);
		}
		if (pid[i] == 0)
			live(data, i);
		i++;
	}
}

void	fork_kill_pid(t_philo_info *data, int kill_pid, int i, int *pid)
{
	if (kill_pid == 0)
	{
		sem_wait(data->kill);
		while (i < data->num_of_philos)
		{
			kill(pid[i], SIGKILL);
			i++;
		}
		exit(0);
	}
}

void	create_philos(t_philo_info *data)
{
	int	i;
	int	*pid;
	int	kill_pid;

	i = 0;
	pid = malloc(sizeof(int) * data->num_of_philos);
	if (!pid)
		exit(1);
	fork_philos(data, pid);
	kill_pid = fork();
	fork_kill_pid(data, kill_pid, i, pid);
	while (i < data->num_of_philos)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	sem_post(data->kill);
	waitpid(kill_pid, NULL, 0);
	free(pid);
}
