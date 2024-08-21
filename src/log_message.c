/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   log_message.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:24:38 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/21 17:32:46 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_message(t_philo *philo, enum e_states philo_state)
{
	long				time_passed;
	static const char	*messages[] = {
		"%ld, philo %d has taken a fork.\n",
		"%ld, philo %d is eating.\n",
		"%ld, philo %d is sleeping.\n",
		"%ld, philo %d is thinking.\n",
		"%ld, philo %d died.\n"
	};
	//if (philo_state < 0 || philo_state >= sizeof(messages) / sizeof(messages[0]))
    //	return ;
	pthread_mutex_lock(&philo->info->write_lock); // error check
	//pthread_mutex_lock(&philo->info->end_lock);
	if (!has_philo_died(philo->info) )
	//if (philo->info->end == false)
	{
		time_passed = elapsed_time(philo->info->start_time);
		printf(messages[philo_state], elapsed_time, philo->id);
		//pthread_mutex_lock(&philo->death_mutex);
		//if (philo_state == DEAD)
		//	philo->info->end = true;
		//pthread_mutex_unlock(&philo->death_mutex);
		pthread_mutex_lock(&philo->info->end_lock);
		if (philo_state == DEAD)
			philo->info->philo_died = true;
		pthread_mutex_unlock(&philo->info->end_lock);
	}
	//pthread_mutex_unlock(&philo->info->end_lock);
	pthread_mutex_unlock(&philo->info->write_lock);
}
