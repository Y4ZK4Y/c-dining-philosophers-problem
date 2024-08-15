/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   log.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:24:38 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/15 11:28:56 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_message(t_philo *philo, enum e_philo_states philo_state)
{
	long				elapsed_time;
	static const char	*messages[] = {
		"timestamp:%ld, philo %d has taken a fork.\n",
		"timestamp:%ld, philo %d is eating.\n",
		"timestamp:%ld, philo %d is sleeping.\n",
		"timestamp:%ld, philo %d is thinking.\n",
		"timestamp:%ld, philo %d died.\n"
	};

	//elapsed_time = calculate_elapsed_time(philo->info->start_time); // move to line 30 
	pthread_mutex_lock(&philo->info->write_lock); // error check
	if (philo->info->end == false)
	{
		elapsed_time = calculate_elapsed_time(philo->info->start_time);
		printf(messages[philo_state], elapsed_time, philo->id);
		if (philo_state == DEAD)
			philo->info->end = true;
	} // thatd be communication
	pthread_mutex_unlock(&philo->info->write_lock);
}
