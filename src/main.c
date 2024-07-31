#include "philo.h"

int	main(int argc, char *argv[])
{
	t_info	info;

	ft_bzero(&info, sizeof(t_info));
	if (get_input(&info.input, argc, argv) == 1)
	{
		printf("parsing func failed\n");
		return (1);
	}
	if (philo_init(info) == 1)
	{
		printf("init func failed\n");
		return (exit_cleanup(&info, 1));;
	}
	if (start_sim(info) == 1)
	{
		printf("sim funct failed\n");
		return (exit_cleanup(&info, 1));
	}
	return (exit_cleanup(&info, 0));
}