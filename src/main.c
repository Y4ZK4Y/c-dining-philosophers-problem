/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:26:43 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/19 19:07:49 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->input.num_of_philos)
	{
		if (pthread_join(info->philos[i].thread, NULL) != 0)
			error_exit("Joining threads failed.", ERROR, info, 0);
		i++;
	}
	if (pthread_join(info->monitor, NULL) != 0)
		error_exit("Creating threads failed.", ERROR, info, 0);
}

void	create_threads(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&info->start_lock);
	info->end = false;
	while (i < info->input.num_of_philos)
	{
		info->philos[i].philo_state = ACTIVE;
		if (pthread_create(&info->philos[i].thread, NULL, philo_life_cycle, \
		&info->philos[i]) != 0)
			error("Creating threads failed.", info, 0); // kill all the ones that alrady exist not the unborn ones
		info->threads_created++;
		usleep(100);
		i++;
	}
	info->start_time = get_current_time();
	pthread_mutex_unlock(&info->start_lock);
	// call monitor func
	if (pthread_create(&info->monitor, NULL, monitor, info->philos) != 0)
	{
		error("Creating threads failed.", info, 0);
	}
}

int	main(int argc, char *argv[])
{
	t_info	info;

	memset(&info, 0, sizeof(t_info));
	if (get_input(&info.input, argc, argv) == 1)
		return (1);
	if (init(&info) == 1)
		return (cleanup(info), 1);
	create_threads(&info);
	join_threads(&info);
	monitor();
	exit_program();
	//error_exit(NULL, &info, 0);
}
