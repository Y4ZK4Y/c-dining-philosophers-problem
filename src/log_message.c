/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   log_message.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:24:38 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/09/02 16:50:09 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_message(t_philo *philo, enum e_message msg)
{
	long				time_passed;
	static const char	*messages[] = {
		"%ld, philo %d has taken a fork.\n",
		"%ld, philo %d is eating.\n",
		"%ld, philo %d is sleeping.\n",
		"%ld, philo %d is thinking.\n",
		"%ld, philo %d died.\n"
	};

	pthread_mutex_lock(&philo->info->write_lock);
	if (!is_end(philo->info))
	{
		time_passed = elapsed_time(philo->info->start_time);
		printf(messages[msg], time_passed, philo->id);
		if (msg == DEAD)
			declare_death(philo->info);
	}
	pthread_mutex_unlock(&philo->info->write_lock);
}
