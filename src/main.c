/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:26:43 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/21 17:14:56 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	program_end(&info);
	return (0);
}
