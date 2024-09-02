/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/21 17:10:38 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/09/02 17:15:24 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	has_philo_starved(t_philo *philo)
{
	bool	ret;

	pthread_mutex_lock(&philo->death_lock);
	ret = elapsed_time(philo->last_meal_time) >= philo->info->input.time_die;
	pthread_mutex_unlock(&philo->death_lock);
	return (ret);
}

void	declare_death(t_info *info)
{
	pthread_mutex_lock(&info->end_lock);
	info->end = true;
	pthread_mutex_unlock(&info->end_lock);
}

bool	is_philo_full(t_philo *philo)
{
	bool	ret;

	pthread_mutex_lock(&philo->death_lock);
	ret = philo->times_eaten == philo->info->input.num_meals;
	pthread_mutex_unlock(&philo->death_lock);
	return (ret);
}

bool	is_end(t_info *info)
{
	bool	ret;

	pthread_mutex_lock(&info->end_lock);
	ret = info->end;
	pthread_mutex_unlock(&info->end_lock);
	return (ret);
}

void	sync_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->start_lock);
	pthread_mutex_unlock(&philo->info->start_lock);
}
