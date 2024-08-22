/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_keeping.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:31:43 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/22 15:21:20 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	elapsed_time(long start)
{
	long	current;

	current = get_time();
	return (current - start);
}

void	ft_usleep(long time, t_philo *philo)
{
	long	action_start;

	action_start = get_time();
	pthread_mutex_lock(&philo->info->end_lock);
	while (elapsed_time(action_start) < time && \
	has_philo_died(philo->info) == false)
		usleep(100);
	pthread_mutex_unlock(&philo->info->end_lock);
}
