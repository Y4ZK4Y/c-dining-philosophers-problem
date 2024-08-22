/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:51 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/22 15:24:32 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	join_threads(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->input.num_philos)
	{
		if (pthread_join(info->philos[i].thread, NULL) != 0)
			return (print_error("Joining threads failed."), 1);
		i++;
	}
	return (0);
}

static void	destroy_threads(t_info *info, int philos_created)
{
	int	i;

	i = 0;
	info->philo_died = true;
	pthread_mutex_lock(&info->end_lock);
	info->end = true;
	pthread_mutex_unlock(&info->end_lock);
	while (i < philos_created)
	{
		if (pthread_join(info->philos[i].thread, NULL) != 0)
			print_error("Joining threads failed");
		i++;
	}
}

int	create_threads(t_info *info)
{
	int	i;

	i = 0;
	info->started = false;
	pthread_mutex_lock(&info->start_lock);
	while (i < info->input.num_philos)
	{
		if (pthread_create(&info->philos[i].thread, NULL, philo_routine, \
		&info->philos[i]) != 0)
		{
			print_error("Creating threads failed.");
			destroy_threads(info, i);
			pthread_mutex_unlock(&info->start_lock);
			return (1);
		}
		usleep(100);
		i++;
	}
	info->start_time = get_time();
	info->started = true;
	pthread_mutex_unlock(&info->start_lock);
	return (0);
}