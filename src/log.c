/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   log.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:24:38 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/20 21:22:58 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_message(t_philo *philo, enum e_philo_states philo_state)
{
	long				elapsed_time;
	static const char	*messages[] = {
		"%ld, philo %d has taken a fork.\n",
		"%ld, philo %d is eating.\n",
		"%ld, philo %d is sleeping.\n",
		"%ld, philo %d is thinking.\n",
		"%ld, philo %d died.\n"
	};
	if (philo_state < 0 || philo_state >= sizeof(messages) / sizeof(messages[0]))
    	return ;
	pthread_mutex_lock(&philo->info->write_lock); // error check
	if (philo->info->end == false)
	{
		elapsed_time = calculate_elapsed_time(philo->info->start_time);
		printf(messages[philo_state], elapsed_time, philo->id);
		pthread_mutex_lock(&philo->state_mutex);
		if (philo_state == DEAD)
			philo->info->end = true;
		pthread_mutex_unlock(&philo->state_mutex);
	}
	pthread_mutex_unlock(&philo->info->write_lock);
}
