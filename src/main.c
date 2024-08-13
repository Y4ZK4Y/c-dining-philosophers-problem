/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:26:43 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/13 10:29:48 by ykarimi       ########   odam.nl         */
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
	// if (pthread_join(info->monitor, NULL) != 0)
	// 	error_exit("Creating threads failed.", ERROR, info, 0);
}

void	create_threads(t_info *info)
{
	int	i;

	i = 0;
	info->lets_fuckin_go = false;
	while (i < info->input.num_of_philos)
	{
		info->philos[i].philo_state = ACTIVE;
		if (pthread_create(&info->philos[i].thread, NULL, philo_life_cycle, \
		&info->philos[i]) != 0)
			error_exit("Creating threads failed.", ERROR, info, 0);
		usleep(100);
		i++;
	}
	// if (pthread_create(&info->monitor, NULL, monitor, info->philos) != 0)
	// {
	// 	error_exit("Creating threads failed.", ERROR, info, 0);
	// }
	info->start_time = get_current_time();
	info->lets_fuckin_go = true;
}

int	main(int argc, char *argv[])
{
	t_info	info;

	memset(&info, 0, sizeof(t_info));
	get_input(&info.input, argc, argv);
	init(&info);
	create_threads(&info);
	join_threads(&info);
	error_exit(NULL, FINE, &info, 0);
}
