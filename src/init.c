#include "philo.h"

int	init_philos(t_info *info)
{
	int	i;
	int	philo_count;
	i = 0;
	philo_count = info->input.num_of_philos;
	bzero(&info->philos, sizeof(t_philo));
	while (i < philo_count)
	{
		info->philos[i].id = i + 1;
		info->philos[i].info = info;
		info->philos[i].last_meal_time = get_current_time();
		info->philos[i].state = INACTIVE;
		info->philos->thread = malloc(philo_count * sizeof(pthread_t));
		if (info->philos->thread == NULL)
		{
			printf("malloc for threads in philo init failed\n");
			return 1;
		}
		i++;
		
	}
}


int	init_forks(t_info *info)
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
	info->monitor->thread= malloc(1 * sizeof(pthread_t));
	if (info->monitor->thread == NULL)
	{
		printf("malloc for monitor in philo init dedd\n");
		return 1;
	}
	return 0;

}

int	init_log(t_info *info)
{
	bzero(&info->logs, sizeof(t_log));
	if (pthread_mutex_init(&info->logs->write_lock, NULL) != 0)
	{
		printf("log mutex fugged\n");
		return 1;
	}
	return (0);
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
	// if (init_monitor(info) == 1)
	// {
	// 	printf("init monitor got fugged\n");
	// 	return 1;
	// }
	if (init_forks(&info) == 1)
	{
		printf("init forks got fugged\n");
		return 1;
	}
	if (init_log(&info) == 1)
	{
		printf("init log got fugged\n");
		return 1;
	}
	//info->lets_fuckin_go = get_time();



}