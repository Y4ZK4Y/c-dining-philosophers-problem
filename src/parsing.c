/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:23:14 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/09/02 17:23:18 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_input(t_input *input, int argc, char *argv[])
{
	int		i;
	int		input_array[5];
	long	num;
	char	*endptr;

	i = 0;
	memset(input, 0, sizeof(t_input));
	while (i++ < argc - 1)
	{
		errno = 0;
		num = ft_strtol(argv[i], &endptr, 10);
		if (errno != 0 || *endptr != '\0' || num < 0 || num > INT_MAX)
			return (print_error("Invalid input."), ERROR);
		input_array[i - 1] = num;
	}
	input->num_philos = input_array[0];
	if (input->num_philos > 200)
		return (print_error("Can't have more than 200 freeloaders."), ERROR);
	input->time_die = input_array[1];
	input->time_eat = input_array[2];
	input->time_sleep = input_array[3];
	if (argc == 6)
		input->num_meals = input_array[4];
	return (FINE);
}

/* accept 5 or 6 arguments, less than 200 philosophers */
int	get_input(t_input *input, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (print_error("Invalid argument count."), ERROR);
	if (parse_input(input, argc, argv) == ERROR)
		return (ERROR);
	if (input->num_philos <= 0)
		return (print_error("Can't host a party with no peeps."), ERROR);
	return (FINE);
}
