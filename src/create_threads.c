/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_threads.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 21:23:51 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/20 21:24:02 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup_threads(t_info *info, int num_philos_created)
{
	int	i;

	i = 0;
	info->end = true;
	while (i < num_philos_created)
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
	pthread_mutex_lock(&info->start_lock);
	while (i < info->input.num_of_philos)
	{
		info->philos[i].philo_state = ACTIVE;
		if (pthread_create(&info->philos[i].thread, NULL, philo_life_cycle, \
		&info->philos[i]) != 0)
		{
			print_error("Creating threads failed.");
			cleanup_threads(info, i);
			pthread_mutex_unlock(&info->start_lock);
			return (1);
		}
		usleep(100);
		i++;
	}
	info->start_time = get_current_time();
	pthread_mutex_unlock(&info->start_lock);
	return (0);
}