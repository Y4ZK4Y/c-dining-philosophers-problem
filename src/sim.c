#include "philo.h"

int	wait_for_everybody(t_info *info)
{
	int	i;
	i = 0;
	int	philo_count;
	philo_count = info->input.num_of_philos;
	while (i < philo_count)
	{
		if (pthread_join(info->philos[i].thread, NULL) != 0)
		{
			printf("pthread create got fucked\n");
			return 1;
		}
		i++;
	}
	return 0;
}

int	create_philo(t_info *info)
{
	int	i;
	int	philo_count;

	i = 0;
	philo_count = info->input.num_of_philos;
	while (i < philo_count)
	{
		info->philos[i].state = ALIVE;
		if (pthread_create(&info->philos->thread[i], NULL, philo_life_cycle, &info->philos[i]) != 0)
		{
			printf("creating threads got fucked\n"); // handle errors
			return 1;
		}
		usleep(100);
		i++;
	}
	//data->lets_fuckin_go = get_time();
	info->sim_on = true; 
	return 0;
}

int	sim(t_info *info)
{
	if (create_philos(info) == 1)
	{
		printf("create philos func faield\n");
		return 1;
	}
	if (wait_for_everybody(info) == 1)
	{
		printf("wait func faield\n");
		return 1;
	}
	return 0;
}
