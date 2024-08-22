/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/21 17:10:38 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/08/22 14:44:48 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	has_philo_died(t_info *info)
{
	pthread_mutex_lock(&info->end_lock);
	if (info->philo_died == true)
	{
		pthread_mutex_unlock(&info->end_lock);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&info->end_lock);
		return (false);
	}
}
enum e_states philo_state(t_philo *philo)
{
	enum e_states state;

	pthread_mutex_lock(&philo->death_lock);
	state = philo->state;
	pthread_mutex_unlock(&philo->death_lock);
	return (state);
}


bool	has_philo_starved(t_philo *philo)
{
	pthread_mutex_lock(&philo->death_lock);
	if (elapsed_time(philo->last_meal_time) >= philo->info->input.time_die)
	{
		pthread_mutex_unlock(&philo->death_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->death_lock);
	return (false);
}

void	declare_death(t_info *info)
{
	pthread_mutex_lock(&info->end_lock);
	info->philo_died = true;
	pthread_mutex_unlock(&info->end_lock);
}