/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:22:13 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/15 11:30:59 by ykarimi       ########   odam.nl         */
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
		info->philos[i].left_fork_index = -1;
		info->philos[i].right_fork_index = -1;
		// assign forks here
		assign_forks(&info->philos[i]);
		i++;
	}
	info->end = false;
}

/*
1 write_lock for logs
1 for each fork
1 for philo state
*/
void	init_mutexes(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->input.num_of_philos)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			error_exit("Initializing mutexes failed.", ERROR, info, 1);
		if (pthread_mutex_init(&info->philos[i].state_mutex, NULL) != 0)
			error_exit("Initializing mutexes failed.", ERROR, info, 1);
		i++;
	}
	if (pthread_mutex_init(&info->write_lock, NULL) != 0)
		error_exit("Initializing mutexes failed.", ERROR, info, 1);
	if (pthread_mutex_init(&info->start_lock, NULL) != 0)
		error_exit("Initializing mutexes failed.", ERROR, info, 1);
}

void	init(t_info *info)
{
	info->philos = ft_malloc(info->input.num_of_philos * sizeof(t_philo), info);
	init_philos(info);
	info->forks = ft_malloc(info->input.num_of_philos * \
	sizeof(pthread_mutex_t), info);
	init_mutexes(info);
}
// no exit()