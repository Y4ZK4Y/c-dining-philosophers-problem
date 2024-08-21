/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/21 17:10:38 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/08/21 17:39:14 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	has_philo_died(t_info *info)
{
	bool ret;

	ret = false;
	pthread_mutex_lock(&info->end_lock);
	if (info->philo_died == true)
		ret = true;
	else if (info->philo_died == false)
		ret = false;
	pthread_mutex_unlock(&info->end_lock);
	return (ret);
}
enum e_states philo_state(t_philo *philo)
{
	enum e_states state;

	pthread_mutex_lock(&philo->death_mutex);
	state = philo->philo_state;
	pthread_mutex_unlock(&philo->death_mutex);
	return (state);

}