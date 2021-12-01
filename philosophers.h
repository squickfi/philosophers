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
	unsigned long			last_eat_time;
	struct s_philo_info *data;
}				t_philo;

typedef struct s_philo_info
{
	unsigned long		start_time;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_to_eat;
	int				fed_philos;
	int				is_anyone_dead;
	t_philo			*philo;
	pthread_mutex_t	write_to_terminal;
	pthread_mutex_t	*fork;
}		t_philo_info;

//philosophers.c

#endif