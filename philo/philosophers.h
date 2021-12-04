/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squickfi <squickfi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 02:32:52 by squickfi          #+#    #+#             */
/*   Updated: 2021/12/04 23:35:35 by squickfi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

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
	pthread_t			thread;
	int					philo_num;
	int					eat_times;
	int					left_fork;
	int					right_fork;
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
	int				is_anyone_dead;
	t_philo			*philo;
	pthread_mutex_t	*fork;
}					t_philo_info;

//philo_utils.c
int				ft_atoi(char *str);
int				print_massage2(int flag, t_philo *philo);
int				print_massage(int flag, t_philo *philo);
int				check_args(t_philo_info *data);
int				get_args(int argc, char **argv, t_philo_info *data);

//living.c
void			init_philo(t_philo_info *data, int i);
int				init_philos_and_forks(t_philo_info *data);
void			user_usleep(int	time_to_wait);
int				life_cycle(t_philo *philo);
void			*live(t_philo *philo);

//philosophers.c
unsigned long	get_time(void);
int				check_death(t_philo_info *data);
void			create_threads(t_philo_info *data);
void			join_threads_and_destroy_mutexes(t_philo_info *data);

#endif