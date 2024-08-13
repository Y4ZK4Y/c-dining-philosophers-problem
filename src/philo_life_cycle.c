/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_life_cycle.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:28:52 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/13 10:34:00 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo)
{
	philo->left_fork_index = philo->id - 1;
	philo->right_fork_index = philo->id;
	if (philo->id == philo->info->input.num_of_philos)
		philo->right_fork_index = 0;
}

void	pickup_forks(t_philo *philo)
{
	assign_forks(philo);
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->info->forks[philo->right_fork_index]);
		pthread_mutex_lock(&philo->info->forks[philo->left_fork_index]);
	}
	else
	{
		pthread_mutex_lock(&philo->info->forks[philo->left_fork_index]);
		pthread_mutex_lock(&philo->info->forks[philo->right_fork_index]);
	}
	philo->philo_state = TAKEN_FORK;
	log_message(philo, philo->philo_state);
}

void	eat(t_philo *philo)
{
	//pthread_mutex_lock(&philo->state_mutex);
	philo->philo_state = EATING;
	philo->last_meal_time = get_current_time();
	philo->philo_state = EATING;
	log_message(philo, philo->philo_state);
	ft_usleep(philo->info->input.time_to_eat, philo);
	//pthread_mutex_unlock(&philo->state_mutex);
	if (philo->id % 2)
	{
		pthread_mutex_unlock(&philo->info->forks \
		[philo->info->philos->right_fork_index]);
		pthread_mutex_unlock(&philo->info->forks \
		[philo->info->philos->left_fork_index]);
	}
	else
	{
		pthread_mutex_unlock(&philo->info->forks \
		[philo->info->philos->left_fork_index]);
		pthread_mutex_unlock(&philo->info->forks \
		[philo->info->philos->right_fork_index]);
	}
}

void	think(t_philo *philo)
{
	//pthread_mutex_lock(&philo->state_mutex);
	philo->philo_state = THINKING;
	log_message(philo, philo->philo_state);
	//pthread_mutex_unlock(&philo->state_mutex);
	usleep(1000);
}

void	philo_sleep(t_philo *philo)
{
	//pthread_mutex_lock(&philo->state_mutex);
	philo->philo_state = SLEEPING;
	log_message(philo, philo->philo_state);
	//pthread_mutex_unlock(&philo->state_mutex);
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
	if (philo->info->input.num_of_philos == 1)
		return (loner_philo(philo), NULL);
	if (philo->id % 2 == 0)
		usleep(1000);
	philo->last_meal_time = get_current_time();
	// if (pthread_create(&philo->info->monitor, NULL, monitor, philo) != 0)
	// 	error_exit("Creating threads failed.", ERROR, philo->info, 0);
	while (1)
	{
		if ((philo->info->end) == true)
		{
			//pthread_mutex_lock(&philo->state_mutex);
			philo->philo_state = DEAD;
			log_message(philo, DEAD);
			//pthread_mutex_unlock(&philo->state_mutex);
			break ;
		}
		pickup_forks(philo);
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	philo->philo_state = INACTIVE;
	// pthread_join(philo->info->monitor, NULL);
	return (NULL);
}
