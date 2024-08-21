/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:31:43 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/20 21:21:58 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	calculate_elapsed_time(long start)
{
	long	current;

	current = get_current_time();
	return (current - start);
}

void	ft_usleep(long time, t_philo *philo)
{
	long	action_start;

	action_start = get_current_time();
	while (calculate_elapsed_time(action_start) < time && \
	philo->info->end == false)
		usleep(100);
}
