/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:23:14 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/21 17:20:09 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_input(t_input *input, int argc, char *argv[])
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
			return (1);
		input_array[i - 1] = num;
	}
	input->num_philos = input_array[0];
	input->time_die = input_array[1];
	input->time_eat = input_array[2];
	input->time_sleep = input_array[3];
	return (0);
}
// you can add more input checks and maybe account for the optional arg
int	get_input(t_input *input, int argc, char *argv[])
{
	if (argc != 5)
		return (print_error("Invalid argument count."), 1);
	if (parse_input(input, argc, argv) == 1)
		return (print_error("Invalid input."), 1);
	if (input->num_philos <= 0)
		return (print_error("Can't host a party with no peeps."), 1);
	return (0);
}
