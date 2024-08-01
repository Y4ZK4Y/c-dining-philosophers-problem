#include "philo.h"

int	init_philos(t_info *info)
{
	int	i;
	int	philo_count;

	i = 0;
	philo_count = info->input.num_of_philos;
	ft_bzero(&info->philos, sizeof(t_philo));
	while (i < philo_count)
	{
		info->philos[i].id = i + 1;
		info->philos[i].info = info;
		// info->philos[i].last_meal_time = 0;
		info->philos[i].state = INACTIVE;
		info->philos->dead = false;
		info->philos->thread = malloc(1 * sizeof(pthread_t));
		if (info->philos->thread == NULL)
		{
			printf("malloc for threads in philo init failed\n");
			return 1;
		}
		i++;
	}
	return (0);
}


int	init_mutexes(t_info *info)
{
	int	i;
	int	philo_count;

	i = 0;
	philo_count = info->input.num_of_philos;
	while (i < philo_count)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
		{
			printf("mutex got fucekd\n");
			return 1;
		}
		i++;
	}
	if (pthread_mutex_init(info->write_lock, NULL) != 0)
	{
		printf("log mutex fugged\n");
		return 1;
	}
	return 0;
}

int	init_monitor(t_info *info)
{
	ft_bzero(&info->monitor, sizeof(t_monitor));
	info->monitor->thread= malloc(1 * sizeof(pthread_t));
	if (info->monitor->thread == NULL)
	{
		printf("malloc for monitor in philo init dedd\n");
		return 1;
	}
	if (pthread_create(info->monitor->thread, NULL, monitor, &info->philos) != 0)
	{
		printf("creating monitor thread got fucked\n"); // handle errors
		return 1;
	}
	if (pthread_mutex_init(&info->monitor->turn_lock, NULL) != 0)
	{
		printf("monitor mutex got fucekd\n");
		return 1;
	}
	return 0;
}


int	init(t_info *info)
{
	info->philos = malloc(info->input.num_of_philos * sizeof(t_philo));
	if (info->philos == NULL)
	{
		printf("philo init went rouge\n");
		return 1;
	}
	if (init_philos(info) == 1)
	{
		printf("init philos got fucked\n");
		return 1;
	}
	
	if (init_mutexes(info) == 1)
	{
		printf("init forks got fugged\n");
		return 1;
	}
	return 0;
}