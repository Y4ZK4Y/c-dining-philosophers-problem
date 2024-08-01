#include "philo.h"

void	init_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->input.num_of_philos)
	{
		info->philos[i].id = i + 1;
		info->philos[i].info = info;
		info->philos[i].last_meal_time = 0;
		// info->philos[i].left_fork = &(info->forks[i]);
		// info->philos[i].right_fork = &(info->forks[(i+1)% info->input.num_of_philos]);
		info->philos[i].philo_state = INACTIVE;
		i++;
	}
}

int	init_mutexes(t_info *info)
{
	int	i;

	i = 0;
	info->forks = ft_malloc(info->input.num_of_philos * sizeof(pthread_mutex_t));
	
	while (i < info->input.num_of_philos)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
		{
			printf("mutex got fucekd\n");
			return 1;
		}
		if (thread_mutex_init(&info->philos[i].state_mutex, NULL) != 0)
		{
			printf("mutex got fucekd\n");
			return 1;
		}
		info->forks[i].index = 0;
		i++;
	}
	if (pthread_mutex_init(&info->write_lock, NULL) != 0)
	{
		printf("log mutex fugged\n");
		return 1;
	}
	return 0;
}


int	init(t_info *info)
{
	info->philos = ft_malloc(info->input.num_of_philos * sizeof(t_philo));
	init_philos(info);
	if (init_mutexes(info) == 1)
		error_exit("init forks got fugged", 1);

	if (create_threads(info) == 1)
		error_exit("create philos func faield", 1);
	
	if (wait_for_threads(info) == 1)
		error_exit("wait func faield", 1);

	return 0;
}
