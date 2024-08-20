/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:27:46 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/20 12:18:39 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(t_info *info)
{
	while (info->end == false)
	{
		if (info->philos->philo_state == INACTIVE)
			break ;
		if (calculate_elapsed_time(info->philos->last_meal_time) >= \
		info->input.time_to_die)
		{
			info->philos->philo_state = DEAD;
			log_message(info->philos, info->philos->philo_state);
			info->end = true;
		}
		usleep(1000);
	}
	return (NULL);
}
