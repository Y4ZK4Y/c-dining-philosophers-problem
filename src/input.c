/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:23:14 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/19 15:31:53 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse_input(t_input *input, int argc, char *argv[])
{
	int		i;
	int		input_array[argc];
	long	num;
	char	*endptr;

	i = 0;
	memset(input, 0, sizeof(t_input));
	while (i++ < argc - 1)
	{
		errno = 0;
		num = ft_strtol(argv[i], &endptr, 10);
		if (errno != 0 || *endptr != '\0' || num < 0 || num > INT_MAX)
			error("Invalid input.", NULL, 0);
		input_array[i - 1] = num;
	}
	input->num_of_philos = input_array[0];
	input->time_to_die = input_array[1];
	input->time_to_eat = input_array[2];
	input->time_to_sleep = input_array[3];
}

void	get_input(t_input *input, int argc, char *argv[])
{
	if (argc != 5)
		error("Invalid argument count.", NULL, 0);
	parse_input(input, argc, argv);
	if (input->num_of_philos <= 0)
		error("Can't host a party with no peeps.", NULL, 0);
}
