/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:22:13 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/19 15:31:11 by ykarimi       ########   odam.nl         */
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

/*
	1 write_lock mutex for logs
	1 mutex for each fork
	1 mutex for philo_state
*/
void	init_mutexes(t_info *info)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&info->write_lock, NULL) != 0)
		error("Initializing mutexes failed.", info, 0);
	if (pthread_mutex_init(&info->start_lock, NULL) != 0)
		error("Initializing mutexes failed.", info, 0);
	while (i < info->input.num_of_philos)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			error("Initializing mutexes failed.", info, i);
		if (pthread_mutex_init(&info->philos[i].state_mutex, NULL) != 0)
			error("Initializing mutexes failed.", info, i);
		i++;
	}
}

void	init(t_info *info)
{
	info->philos = ft_malloc(info->input.num_of_philos * sizeof(t_philo), info);
	init_philos(info);
	info->forks = ft_malloc(info->input.num_of_philos * \
	sizeof(pthread_mutex_t), info);
	init_mutexes(info);
	info->end = false;
}