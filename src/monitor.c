/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:27:46 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/20 15:47:41 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(t_info *info)
{
	int	i;

	while (info->end == false)
	{
		i = 0;
		while (i < info->input.num_of_philos)
		{
			pthread_mutex_lock(&info->philos[i].state_mutex);
			if (info->philos[i].philo_state != INACTIVE && (calculate_elapsed_time(info->philos[i].last_meal_time) >= info->input.time_to_die))
			{
				info->philos[i].philo_state = DEAD;
				pthread_mutex_unlock(&info->philos[i].state_mutex);
				log_message(&info->philos[i], DEAD);
				info->end = true;
				break ;
			}
			pthread_mutex_unlock(&info->philos[i].state_mutex);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
