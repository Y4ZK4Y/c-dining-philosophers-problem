/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:22:13 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/19 19:10:25 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static swap_forks(int *right, int *left)
{
	int temp;
	temp = *right;
	*right = *left;
	*left = temp;
}

// make sure you're assigning right
static void	assign_forks(t_philo *philo)
{
	if (philo->id == philo->info->input.num_of_philos)
		philo->right_fork_index = 0; // check if you need to  do the same for loner philo
	philo->left_fork_index = philo->id - 1;
	philo->right_fork_index = philo->id;
	if (philo->id % 2 == 0)
		swap_forks(&philo->right_fork_index, philo->left_fork_index);
}

void	init_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->input.num_of_philos)
	{
		info->philos[i].id = i + 1;
		info->philos[i].last_meal_time = (struct timeval){0};
		info->philos[i].philo_state = INACTIVE;
		info->philos[i].info = info;
		assign_forks(&info->philos[i]); // check
		i++;
	}
}

static void	destroy_mutexes(t_info *info, int num_mutex)
{
	int	i;
	int	index;

	i = num_mutex - 1;
	while (i >= 0)
	{
		if (i < 2)
		{
			if (i == 0)
				pthread_mutex_destroy(&info->write_lock);
			else if (i == 1)
				pthread_mutex_destroy(&info->start_lock);
		}
		else
		{
			index = (i - 2) / 2;
			if ((i - 2) % 2 == 0)
				pthread_mutex_destroy(&info->forks[index]);
			else
				pthread_mutex_destroy(&info->philos[index].state_mutex);
		}
		i--;
	}
}

int	init_mutexes(t_info *info)
{
	int	i;
	int	num_mutex;
	pthread_mutex_t	*mutexes[] = { &info->write_lock, &info->start_lock};

	i = 0;
	while (i < 2)
	{
		if (pthread_mutex_init(mutexes[i], NULL) != 0)
			return (destroy_mutexes(info, i), 1);
		i++;
	}
	i = 0;
	while (i < info->input.num_of_philos)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (destroy_mutexes(info, 2 + i * 2), 1);
		if (pthread_mutex_init(&info->philos[i], NULL) != 0)
			return (destroy_mutexes(info, 2 + i * 2 + 1), 1);
		i++;
	}
	return (0);
}

int	init(t_info *info)
{
	info->philos = malloc(info->input.num_of_philos * sizeof(t_philo));
	if (info->philos == NULL)
		return (print_error("Malloc failed."), 1);
	init_philos(info);
	info->forks = malloc(info->input.num_of_philos * sizeof(pthread_mutex_t));
	if (info->philos == NULL)
		return (print_error("Malloc failed."), 1);
	if (init_mutexes(info) == 1)
		return (print_error("Initializing mutexes failed."), 1);
	info->end = false;
	return (0);
}
