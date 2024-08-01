#include "philo.h"

int	wait_for_threads(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->input.num_of_philos)
	{
		if (pthread_join(info->philos[i].thread, NULL) != 0)
		{
			printf("pthread create got fucked\n");
			return 1;
		}
		i++;
	}
	if (pthread_join(info->monitor, NULL) != 0)
	{
		printf("pthread create got fucked\n");
	}
	return 0;
}

int	create_threads(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->input.num_of_philos)
	{
		info->philos[i].philo_state = THINKING;
		if (pthread_create(info->philos[i].thread, NULL, philo_life_cycle, &info->philos[i]) != 0)
		{
			printf("creating threads got fucked\n"); // handle errors
			return 1;
		}
		usleep(100);
		i++;
	}
	if (pthread_create(&info->monitor, NULL, monitor, &info) != 0)
	{
		printf("creating monitor thread got fucked\n"); // handle errors
		return 1;
	}
	//info->start_time = get_current_time();
	return 0;
}
