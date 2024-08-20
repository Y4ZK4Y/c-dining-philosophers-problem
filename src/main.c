/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:26:43 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/20 12:18:44 by yasamankari   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->input.num_of_philos)
	{
		if (pthread_join(info->philos[i].thread, NULL) != 0)
			return (print_error("Joining threads failed."), 1);
		i++;
	}
	return (0);
}

static void	cleanup_threads(t_info *info, int num_philos_created)
{
	int	i;

	i = 0;
	info->end = true;
	while (i < num_philos_created)
	{
		pthread_join(info->philos[i].thread, NULL);
		i++;
	}
}

int	create_threads(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&info->start_lock);
	while (i < info->input.num_of_philos)
	{
		info->philos[i].philo_state = ACTIVE;
		if (pthread_create(&info->philos[i].thread, NULL, philo_life_cycle, \
		&info->philos[i]) != 0)
		{
			print_error("Creating threads failed.");
			cleanup_threads(info, i);
			pthread_mutex_unlock(&info->start_lock);
			return (1);
		}
		usleep(100);
		i++;
	}
	info->start_time = get_current_time();
	pthread_mutex_unlock(&info->start_lock);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info	info;

	memset(&info, 0, sizeof(t_info));
	if (get_input(&info.input, argc, argv) == 1)
		return (1);
	if (init(&info) == 1)
		return (cleanup(&info), 1); // cleanup mallocs for fork-philos(no mutexes, taken care of)
	if (create_threads(&info) == 1)
		return (program_end(&info), 1); // at this point, threads failed to create, been cleaned up, general cleanup left(mutexes, mallocs)
	if (join_threads(&info) == 1)
		return (program_end(&info), 1);
	monitor(&info);
	program_end(&info);

}
