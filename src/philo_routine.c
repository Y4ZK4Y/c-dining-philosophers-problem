/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:28:52 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/23 18:27:27 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	pickup_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->left_fork]);
	log_message(philo, TAKEN_FORK);
	pthread_mutex_lock(&philo->info->forks[philo->right_fork]);
	log_message(philo, TAKEN_FORK);
}

void	eat(t_philo *philo)
{
	//pthread_mutex_lock(&philo->info->time_keeping_lock);
	//record_timestamp(philo->info, &philo->last_meal_time);
	philo->last_meal_time = get_time(); // or mutex?? update_meal_time 
	//pthread_mutex_unlock(&philo->info->time_keeping_lock);
	
	log_message(philo, EATING);
	ft_usleep(philo->info->input.time_eat, philo);

	
	pthread_mutex_unlock(&philo->info->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->right_fork]);

	//pthread_mutex_lock(&philo->info->time_keeping_lock);
	philo->times_eaten += 1; // or mutex?
	//pthread_mutex_unlock(&philo->info->time_keeping_lock);
}


void	philo_sleep(t_philo *philo)
{
	log_message(philo, SLEEPING);
	ft_usleep(philo->info->input.time_sleep, philo);
}

static void	*loner_philo(t_philo *philo)
{
	log_message(philo, TAKEN_FORK);
	ft_usleep(philo->info->input.time_die, philo);
	return (NULL);
}


void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;

	pthread_mutex_lock(&philo->info->start_lock);
	pthread_mutex_unlock(&philo->info->start_lock);

	if (philo->info->input.num_philos == 1)
		return (loner_philo(philo), NULL);

	if (philo->id % 2 == 0)
		usleep(1000);

	philo->last_meal_time = get_time();

	if (init_monitor(philo) == ERROR)
		return (NULL);
	
	while (!is_end(philo->info)) 
	{
		pickup_forks(philo);
		eat(philo);
		if(is_philo_full(philo) == true)
			break ;
		philo_sleep(philo);
		log_message(philo, THINKING);
		usleep(1000);
	}
	//philo->active = false;
	pthread_join(philo->monitor, NULL);
	return (NULL);
}
