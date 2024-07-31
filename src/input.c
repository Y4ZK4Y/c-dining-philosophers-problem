#include "philo.h"

int	parse_input(t_input *input, int argc, char *argv[])
{
	int	i;
	int input_array[argc];
	long num;
	char *endptr;
	i = 0;
	while (i++ < argc - 1)
	{
		errno = 0;
		num = strtol(argv[i], &endptr, 10);
		if (errno != 0 || *endptr != '\0' || num < 0 || num > INT_MAX)
		{
			printf("Invalid input: %s\n", argv[i]);
			input->error = 1;
			return 1;
		}
		input_array[i - 1] = num;
		printf("arg[%d]: %d (converted to %ld)\n", i, input_array[i - 1], num);
	}
	input->num_of_philos = input_array[0];
	input->time_to_die = input_array[1];
	input->time_to_eat = input_array[2];
	input->time_to_sleep = input_array[3];
	return 0;

}

int	get_input(t_input *input, int argc, char *argv[])
{
	if (argc != 5) // account for the optional arg (&& argc != 6)
		return (printf("invalid argument count")); // send error to stderr
	if (parse_input(input, argc, argv) == 1)
	{
		printf("parsing got fuuuucked\n");
	}
	if (input->num_of_philos <= 0)
	{
		printf("too few philos tf\n"); //  send to stderr
	}
	return (0);
}
