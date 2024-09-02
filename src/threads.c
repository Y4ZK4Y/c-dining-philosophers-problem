/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:51 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/09/02 17:14:44 by ykarimi       ########   odam.nl         */
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
			return (print_error("Joining threads failed."), ERROR);
		i++;
	}
	return (FINE);
}

static void	destroy_threads(t_info *info, int philos_created)
{
	int	i;

	i = 0;
	info->end = true;
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
	info->start = false;
	pthread_mutex_lock(&info->start_lock);
	while (i < info->input.num_philos)
	{
		info->philos[i].status = active;
		if (pthread_create(&info->philos[i].thread, NULL, philo_routine, \
		&info->philos[i]) != 0)
		{
			print_error("Creating threads failed.");
			destroy_threads(info, i);
			pthread_mutex_unlock(&info->start_lock);
			return (ERROR);
		}
		usleep(100);
		i++;
	}
	info->start_time = get_time();
	info->start = true;
	pthread_mutex_unlock(&info->start_lock);
	return (FINE);
}
