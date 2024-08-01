#include "philo.h"

void	log_message(t_philo *philo, msg_type msgtype)
{
	const char *messages[NUM_MESSAGES] =
	{
		"%d %d has taken a fork.",
		"%d %d is eating.",
		"%d %d is sleeping",
		"%d %d is thinking.",
		"%d %d died."
	};
	pthread_mutex_lock(philo->info->write_lock); // error check
	printf("%s\n", messages[msgtype]);
	pthread_mutex_unlock(philo->info->write_lock);
}

// void	log_destroy()
// {
// 	pthread_mutex_destroy(logs->write_lock); // error check
// }