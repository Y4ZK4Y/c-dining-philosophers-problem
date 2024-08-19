/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_life_cycle.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:28:52 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/19 14:59:58 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"


void	pickup_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->left_fork_index]);
	pthread_mutex_lock(&philo->info->forks[philo->right_fork_index]);
	philo->philo_state = TAKEN_FORK;
	log_message(philo, philo->philo_state);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_mutex);
	philo->philo_state = EATING;
	pthread_mutex_unlock(&philo->state_mutex);
	
	philo->last_meal_time = get_current_time();
	log_message(philo, philo->philo_state);
	ft_usleep(philo->info->input.time_to_eat, philo);

	pthread_mutex_unlock(&philo->info->forks[philo->info->philos->left_fork_index]);
	pthread_mutex_unlock(&philo->info->forks[philo->info->philos->right_fork_index]);
	}
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_mutex);
	philo->philo_state = THINKING;
	pthread_mutex_unlock(&philo->state_mutex);
	log_message(philo, philo->philo_state);

	usleep(1000);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_mutex);
	philo->philo_state = SLEEPING;
	log_message(philo, philo->philo_state);
	pthread_mutex_unlock(&philo->state_mutex);
	ft_usleep(philo->info->input.time_to_sleep, philo);
}

static void	*loner_philo(t_philo *philo)
{
	philo->philo_state = TAKEN_FORK;
	log_message(philo, philo->philo_state);
	ft_usleep(philo->info->input.time_to_die, philo);
	return (NULL);
}

/*
	wait all phil, synchro start
	endless loop philo

*/
void	*philo_life_cycle(void *arg)
{
	t_philo	*philo;

	philo = arg;
	// set a lets_fuckin_go bolean (check it)
	if (philo->info->input.num_of_philos == 1)
		return (loner_philo(philo), NULL);
	if (philo->id % 2 == 0)
		usleep(1000);
	philo->last_meal_time = get_current_time();
	while (1)
	{
		if ((philo->info->end) == true)
		{
			pthread_mutex_lock(&philo->state_mutex);
			philo->philo_state = DEAD;
			pthread_mutex_unlock(&philo->state_mutex);
			log_message(philo, DEAD);
			break ;
		}
		pickup_forks(philo);
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	philo->philo_state = INACTIVE;
	return (NULL);
}
