/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 02:24:06 by squickfi          #+#    #+#             */
/*   Updated: 2021/12/04 02:34:59 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

# define SUCCESS 0
# define ERROR 1
# define DEAD 2
# define FED 3

# define TAKING_FORK 10
# define EATING 11
# define SLEEPING 12
# define THINKING 13

typedef struct s_philo
{
	pthread_t			dead;
	int					philo_num;
	int					eat_times;
	unsigned long		last_eat_time;
	struct s_philo_info	*data;
}						t_philo;

typedef struct s_philo_info
{
	unsigned long	start_time;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_to_eat;
	int				fed_philos;
	struct s_philo	*philo;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*kill;
}					t_philo_info;

//philo_utils.c
int				ft_atoi(char *str);
unsigned long	get_time(void);
int				check_args(t_philo_info *data);
int				get_args(int argc, char **argv, t_philo_info *data);

//living.c
void			*check_death(t_philo *philo);
void			user_usleep(int	time_to_wait);
void			life_cycle(t_philo *philo);
void			*live(t_philo_info *data, int i);

//creating_processes.c
void			fork_philos(t_philo_info *data, int *pid);
void			fork_kill_pid(t_philo_info *data, \
					int kill_pid, int i, int *pid);
void			create_philos(t_philo_info *data);

//philosophers.c
void			init_semaphores(t_philo_info *data);
void			close_semaphores(t_philo_info *data);
void			print_massage2(int flag, t_philo *philo);
void			print_massage(int flag, t_philo *philo);

#endif