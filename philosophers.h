#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t	thread;
	int			philo_num;
	int			eat_times;
	int			left_fork;
	int			right_fork;
	long long	last_eat_time;
}				t_philo;

typedef struct s_philo_info
{
	long long		start_time;
	long long		end_time;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_to_eat;
	int				fed_philos;
	int				is_dead;
	t_philo			*philo;
	pthread_t		check_death;
	pthread_mutex_t	write_to_terminal;
	pthread_mutex_t	is_anyone_dead;
	pthread_mutex_t	*fork;
}		t_philo_info;

t_philo_info	g_info;

//time.c
int		get_time(void);

//util_funcs.c
int		ft_atoi(char *str);

//philo_living.c
void	*live(t_philo *philo);

//philosophers.c
int		init_info(char **argv);

#endif