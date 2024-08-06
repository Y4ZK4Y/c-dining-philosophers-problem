/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:31:43 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/03 20:32:49 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

struct timeval	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv);
}

long	calculate_elapsed_time(struct timeval start)
{
	struct timeval	current;
	long			seconds;
	long			mseconds;

	current = get_current_time();
	seconds = current.tv_sec - start.tv_sec;
	mseconds = current.tv_usec - start.tv_usec;
	return (seconds * 1000 + mseconds / 1000);
}

void	ft_usleep(long time, t_philo *philo)
{
	struct timeval	action_start;

	action_start = get_current_time();
	while (calculate_elapsed_time(action_start) < time && \
	philo->info->end == false)
		usleep(100);
}
