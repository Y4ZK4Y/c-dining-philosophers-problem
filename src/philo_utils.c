/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ykarimi <ykarimi@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/21 17:10:38 by ykarimi       #+#    #+#                 */
/*   Updated: 2024/08/23 18:31:56 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	has_philo_died(t_info *info)
{
	bool	ret;

	pthread_mutex_lock(&info->end_lock);
	ret = info->philo_died;
	pthread_mutex_unlock(&info->end_lock);
	return (ret);
}

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
	info->philo_died = true;
	pthread_mutex_unlock(&info->end_lock);
}

/* do i need to lock it?? */
bool	is_philo_full(t_philo *philo)
{
	bool ret;

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

void	force_end(t_info *info)
{
	pthread_mutex_lock(&info->end_lock);
	info->end = true;
	pthread_mutex_unlock(&info->end_lock);
}


// #include <pthread.h>
// #include <stdbool.h>
// #include <unistd.h>
// #include "philo.h" // Assuming this header contains necessary declarations

// void *monitor(void *arg)
// {
//     t_meta *meta = (t_meta *)arg;
//     const bool monitor_eat = (meta->args.max_eat_count != ARG_NOT_SET);
//     int32_t done_eating_count;
//     int32_t i;
//     t_philo *p;

//     while (true)
//     {
//         done_eating_count = 0;
//         i = 0;
//         while (i < meta->args.philo_count)
//         {
//             p = &meta->philos[i];
//             if (monitor_eat && philo_get_eat_count(p) >= meta->args.max_eat_count)
//                 done_eating_count++;
//             if (has_died(p))
//                 return NULL;
//             i++;
//         }
//         if (done_eating_count >= meta->args.philo_count)
//         {
//             sim_set_stop(meta);
//             return NULL;
//         }
//         usleep(1000);
//     }
//     return NULL;
// }



// void	record_timestamp(t_info *info, long *time)
// {
// 	pthread_mutex_lock(&info->time_keeping_lock);
// 	if (time != NULL)
// 		*time =get_time();
// 	pthread_mutex_unlock(&info->time_keeping_lock);
// }

