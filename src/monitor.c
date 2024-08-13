/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:27:46 by yasamankari   #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2024/08/13 10:24:09 by ykarimi       ########   odam.nl         */
=======
/*   Updated: 2024/08/12 17:23:50 by yasamankari   ########   odam.nl         */
>>>>>>> e507436b114563853af6faf015a3bf49aea133d1
/*                                                                            */
/* ************************************************************************** */

// #include "philo.h"

// void	*monitor(void *arg)
// {
// 	t_philo	*philo;

// 	philo = arg;
// 	while (philo->info->end == false)
// 	{
// 		if (philo->philo_state == INACTIVE)
// 			break ;
// 		//pthread_mutex_lock(&philo->info->turn_lock);
// 		if (calculate_elapsed_time(philo->last_meal_time) >= \
// 		philo->info->input.time_to_die)
// 		{
// 			philo->philo_state = DEAD;
// 			log_message(philo, philo->philo_state);
// 			philo->info->end = true;
// 		}
// 		//pthread_mutex_unlock(&philo->info->monitor->turn_lock);
// 		usleep(1000);
// 	}
// 	return (NULL);
// }
