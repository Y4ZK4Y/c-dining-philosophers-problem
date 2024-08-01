#include "philo.h"

int	main(int argc, char *argv[])
{
	t_info	info;

	memset(&info, 0, sizeof(t_info));
	if (get_input(&info.input, argc, argv) == 1)
	{
		printf("parsing func failed\n");
		return (1);
	}
	if (init(&info) == 1)
	{
		printf("init func failed\n");
		return 1;
		//return (exit_cleanup(&info, 1));;
	}
	if (sim(&info) == 1)
	{
		printf("sim funct failed\n");
		return 1;
		//return (exit_cleanup(&info, 1));
	}
	//return (exit_cleanup(&info, 0));
	return 0;
}