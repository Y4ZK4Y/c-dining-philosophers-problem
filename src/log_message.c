/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   log_message.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:24:38 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/22 14:41:01 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_message(t_philo *philo, enum e_states state)
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
	if (!has_philo_died(philo->info) )
	{
		time_passed = elapsed_time(philo->info->start_time);
		printf(messages[state], elapsed_time, philo->id);

		pthread_mutex_lock(&philo->info->end_lock);
		if (philo_state(philo) == DEAD)
			declare_death(philo->info);
		pthread_mutex_unlock(&philo->info->end_lock);
	}
	pthread_mutex_unlock(&philo->info->write_lock);
}
