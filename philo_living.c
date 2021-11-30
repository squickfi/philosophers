#include "philosophers.h"

int	taking_forks(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(&g_info.is_anyone_dead);
	printf("%d !\n", philo->philo_num);
	if (g_info.is_dead)
		return (1);
	pthread_mutex_unlock(&g_info.is_anyone_dead);
	pthread_mutex_lock(&g_info.fork[philo->left_fork]);
	pthread_mutex_lock(&g_info.write_to_terminal);
	printf("%lld %d has_taken a fork.\n", get_time() - g_info.start_time, philo->philo_num);
	pthread_mutex_unlock(&g_info.write_to_terminal);
	pthread_mutex_lock(&g_info.fork[philo->right_fork]);
	pthread_mutex_lock(&g_info.write_to_terminal);
	printf("%lld %d has_taken a fork.\n", get_time() - g_info.start_time, philo->philo_num);
	pthread_mutex_unlock(&g_info.write_to_terminal);
	return (0);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&g_info.is_anyone_dead);
	if (g_info.is_dead)
		return (1);
	pthread_mutex_unlock(&g_info.is_anyone_dead);
	pthread_mutex_lock(&g_info.write_to_terminal);
	printf("%lld %d is eating.\n", get_time() - g_info.start_time, philo->philo_num);
	pthread_mutex_unlock(&g_info.write_to_terminal);
	usleep(g_info.time_to_eat * 1000);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&g_info.fork[philo->left_fork]);
	pthread_mutex_unlock(&g_info.fork[philo->right_fork]);
	return (0);
}

int	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&g_info.is_anyone_dead);
	if (g_info.is_dead)
		return (1);
	pthread_mutex_unlock(&g_info.is_anyone_dead);
	pthread_mutex_lock(&g_info.write_to_terminal);
	printf("%lld %d is sleeping.\n", get_time() - g_info.start_time, philo->philo_num);
	pthread_mutex_unlock(&g_info.write_to_terminal);
	usleep(g_info.time_to_sleep * 1000);
	return (0);
}

int	thinking(t_philo *philo)
{
	pthread_mutex_lock(&g_info.is_anyone_dead);
	if (g_info.is_dead)
		return (1);
	pthread_mutex_unlock(&g_info.is_anyone_dead);
	pthread_mutex_lock(&g_info.write_to_terminal);
	printf("%lld %d is thinking.\n", get_time() - g_info.start_time, philo->philo_num);
	pthread_mutex_unlock(&g_info.write_to_terminal);
	return (0);
}

void	*live(t_philo *philo)
{
	while (1)
	{
		if (taking_forks(philo))
			return (NULL);
		if (eating(philo))
			return (NULL);
		write(1, "!..\n", 4);
		if (philo->eat_times == g_info.num_of_times_to_eat)
			return (NULL);
		if (sleeping(philo))
			return (NULL);
		if (thinking(philo))
			return (NULL);
	}
	return (NULL);
}
