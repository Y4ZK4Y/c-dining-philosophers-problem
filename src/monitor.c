/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:27:46 by yasamankari   #+#    #+#                 */
<<<<<<< Updated upstream
/*   Updated: 2024/08/15 10:25:26 by ykarimi       ########   odam.nl         */
=======
/*   Updated: 2024/08/13 11:22:35 by ykarimi       ########   odam.nl         */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (philo->info->end == false)
	{
		if (philo->philo_state == INACTIVE)
			break ;
		//pthread_mutex_lock(&philo->info->turn_lock);
		if (calculate_elapsed_time(philo->last_meal_time) >= \
		philo->info->input.time_to_die)
		{
			philo->philo_state = DEAD;
			log_message(philo, philo->philo_state);
			philo->info->end = true;
		}
		//pthread_mutex_unlock(&philo->info->monitor->turn_lock);
		usleep(1000);
	}
	return (NULL);
}
