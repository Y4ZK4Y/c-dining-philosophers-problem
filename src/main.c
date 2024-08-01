#include "philo.h"

int	main(int argc, char *argv[])
{
	t_info	info;

	memset(&info, 0, sizeof(t_info));
	if (get_input(&info.input, argc, argv) == 1)
		error_exit("parsing func failed", 1);
	if (init(&info) == 1)
		error_exit("init func failed", 1);
	// for (int i = 0; i < &info.input.num_of_philos; i++)
	// {
    //     pthread_mutex_destroy(&info.forks[i]);
    //     pthread_mutex_destroy(&info.philos[i].philo_state);
    // }
    // pthread_mutex_destroy(&info.write_lock);

    // free(info.philos);
    // free(info.forks);

	return 0;
}
