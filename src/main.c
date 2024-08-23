/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:26:43 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/23 13:53:20 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_info	info;

	memset(&info, 0, sizeof(t_info));
	if (get_input(&info.input, argc, argv) == 1)
		return (ERROR);
	if (init(&info) == ERROR)
		return (cleanup(&info), ERROR); // cleanup mallocs for fork-philos(no mutexes, taken care of)
	if (create_threads(&info) == ERROR)
		return (program_end(&info), ERROR); // at this point, threads failed to create, been cleaned up, general cleanup left(mutexes, mallocs)
	if (join_threads(&info) == ERROR)
		return (program_end(&info), ERROR);
	program_end(&info);
	return (FINE);
}
