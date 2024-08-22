/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_locks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/21 17:07:57 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/08/22 14:20:35 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void	destroy_locks(t_info *info, int num_lock)
{
	int	i;
	int	index;

	i = num_lock - 1;
	while (i >= 0)
	{
		if (i < 3)
		{
			if (i == 0)
				pthread_mutex_destroy(&info->write_lock);
			else if (i == 1)
				pthread_mutex_destroy(&info->start_lock);
			else if (i == 2)
				pthread_mutex_destroy(&info->end_lock);
		}
		else
		{
			index = (i - 2) / 2;
			if ((i - 2) % 2 == 0)
				pthread_mutex_destroy(&info->forks[index]);
			else
				pthread_mutex_destroy(&info->philos[index].death_lock);
		}
		i--;
	}
}

int	init_locks(t_info *info)
{
	int				i;
	pthread_mutex_t	*mutexes[3] = { &info->write_lock, &info->start_lock, &info->end_lock};

	i = 0;
	while (i < 3)
	{
		if (pthread_mutex_init(mutexes[i], NULL) != 0)
			return (destroy_locks(info, i), 1);
		i++;
	}
	i = 0;
	while (i < info->input.num_philos)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (destroy_locks(info, 2 + i * 2), 1);
		if (pthread_mutex_init(&info->philos[i].death_lock, NULL) != 0)
			return (destroy_locks(info, 2 + i * 2 + 1), 1);
		i++;
	}
	return (0);
}