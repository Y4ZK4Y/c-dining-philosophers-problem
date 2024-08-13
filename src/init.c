/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:22:13 by yasamankari   #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2024/08/13 10:25:01 by ykarimi       ########   odam.nl         */
=======
/*   Updated: 2024/08/12 17:24:48 by yasamankari   ########   odam.nl         */
>>>>>>> e507436b114563853af6faf015a3bf49aea133d1
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->input.num_of_philos)
	{
		info->philos[i].id = i + 1;
		info->philos[i].last_meal_time = (struct timeval){0};
		info->philos[i].philo_state = INACTIVE;
		info->philos[i].info = info;
		info->philos[i].left_fork_index = -1;
		info->philos[i].right_fork_index = -1;
		i++;
	}
	info->end = false;
}

/*
1 write_lock for logs
1 for each fork
1 for philo state
*/
void	init_mutexes(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->input.num_of_philos)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			error_exit("Initializing mutexes failed.", ERROR, info, 1);
		// if (pthread_mutex_init(&info->philos[i].state_mutex, NULL) != 0)
		// 	error_exit("Initializing mutexes failed.", ERROR, info, 1);
		i++;
	}
	if (pthread_mutex_init(&info->write_lock, NULL) != 0)
		error_exit("Initializing mutexes failed.", ERROR, info, 1);
}

void	init(t_info *info)
{
	info->philos = ft_malloc(info->input.num_of_philos * sizeof(t_philo), info);
	init_philos(info);
	info->forks = ft_malloc(info->input.num_of_philos * \
	sizeof(pthread_mutex_t), info);
	init_mutexes(info);
}
