/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:27:46 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/09/02 16:50:50 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_monitor(t_philo *philo)
{
	if (pthread_create(&philo->monitor, NULL, monitor_routine, philo) != 0)
	{
		declare_death(philo->info);
		return (ERROR);
	}
	return (FINE);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (!is_end(philo->info))
	{
		pthread_mutex_lock(&philo->death_lock);
		if (philo->status == inactive)
		{
			pthread_mutex_unlock(&philo->death_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->death_lock);
		pthread_mutex_lock(&philo->death_lock);
		if (elapsed_time(philo->last_meal_time) >= philo->info->input.time_die)
			log_message(philo, DEAD);
		pthread_mutex_unlock(&philo->death_lock);
		usleep(1000);
	}
	return (NULL);
}
