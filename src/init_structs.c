/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_structs.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:22:13 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/09/02 16:48:47 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	swap_forks(int *right, int *left)
{
	int	temp;

	temp = *right;
	*right = *left;
	*left = temp;
}

static void	assign_forks(t_philo *philo)
{
	if (philo->id == philo->info->input.num_philos)
		philo->right_fork = 0;
	else
		philo->right_fork = philo->id;
	philo->left_fork = philo->id - 1;
	if (philo->id % 2 == 0)
		swap_forks(&philo->right_fork, &philo->left_fork);
}

void	init_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->input.num_philos)
	{
		memset(&info->philos[i], 0, sizeof(t_philo));
		info->philos[i].id = i + 1;
		info->philos[i].last_meal_time = 0;
		info->philos[i].times_eaten = 0;
		info->philos[i].info = info;
		info->philos[i].status = joined;
		assign_forks(&info->philos[i]);
		i++;
	}
}

/* mallocs for forks and philos */
int	init(t_info *info)
{
	info->philos = malloc(info->input.num_philos * sizeof(t_philo));
	if (info->philos == NULL)
		return (print_error("Malloc failed."), ERROR);
	init_philos(info);
	info->forks = malloc(info->input.num_philos * sizeof(pthread_mutex_t));
	if (info->forks == NULL)
	{
		print_error("Malloc failed.");
		return (cleanup(info), ERROR);
	}
	if (init_locks(info) == ERROR)
	{
		print_error("Initializing mutexes failed.");
		return (cleanup(info), ERROR);
	}
	info->end = false;
	info->start_time = get_time();
	return (FINE);
}
