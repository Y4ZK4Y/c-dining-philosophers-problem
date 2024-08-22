/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:27:46 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/22 15:17:49 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void *monitor(t_info *info)
// {
// 	int	i;
// 	pthread_mutex_lock(&info->end_lock);
// 	while (info->end == false)
// 	{
// 		pthread_mutex_unlock(&info->end_lock);
// 		i = 0;
// 		while (i < info->input.num_of_philos)
// 		{
// 			pthread_mutex_lock(&info->philos[i].death_mutex);
// 			if (info->philos[i].philo_state != INACTIVE && (calculate_elapsed_time(info->philos[i].last_meal_time) >= info->input.time_to_die))
// 			{
// 				info->philos[i].philo_state = DEAD;
// 				pthread_mutex_unlock(&info->philos[i].death_mutex);
// 				log_message(&info->philos[i], DEAD);
// 				pthread_mutex_lock(&info->end_lock);
// 				info->end = true;
// 				pthread_mutex_unlock(&info->end_lock);
// 				break ;
// 			}
// 			pthread_mutex_unlock(&info->philos[i].death_mutex);
// 			i++;
// 		}
// 		usleep(1000);
// 		pthread_mutex_lock(&info->end_lock);
// 	}
// 	pthread_mutex_unlock(&info->end_lock);
// 	return (NULL);
// }


int	init_monitor(t_philo *philo)
{
	int	ret;

	ret = pthread_create(&philo->monitor, NULL, monitor_routine, philo);
	if (ret != 0)
	{
		declare_death(philo->info);
		return (1);
	}
	return (0);
}

// void	*monitor_routine(void *arg)
// {
// 	t_philo	*philo;

// 	philo = arg;
// 	while (!has_philo_died(philo->info))
// 	{
// 		pthread_mutex_lock(&philo->death_lock);
// 		if (elapsed_time(philo->last_meal_time) >= philo->info->input.time_die)
// 			log_message(philo, DEAD);
// 		pthread_mutex_unlock(&philo->death_lock);
// 		usleep(1000);
// 	}
// 	return (NULL);
// }



void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (!has_philo_died(philo->info))
	{
		if (has_philo_starved(philo) == true)
			log_message(philo, DEAD);
		usleep(1000);
	}
	return (NULL);
}