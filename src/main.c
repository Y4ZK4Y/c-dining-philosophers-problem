/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:26:43 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/09/02 16:42:47 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	program_end(t_info *info)
{
	destroy_mutex(info);
	cleanup(info);
}

int	main(int argc, char *argv[])
{
	t_info	info;

	memset(&info, 0, sizeof(t_info));
	if (get_input(&info.input, argc, argv) == 1)
		return (ERROR);
	if (init(&info) == ERROR)
		return (cleanup(&info), ERROR);
	if (create_threads(&info) == ERROR)
		return (program_end(&info), ERROR);
	if (join_threads(&info) == ERROR)
		return (program_end(&info), ERROR);
	program_end(&info);
	return (FINE);
}
