#include "philo.h"

void	log_message(t_philo *philo, msg_type msgtype)
{
	long	current_time_ms;
	struct timeval current_time;
	const char *messages[NUM_MESSAGES] =
	{
		"%ld %d has taken a fork.",
		"%ld %d is eating.",
		"%ld %d is sleeping",
		"%ld %d is thinking.",
		"%ld %d died."
	};

	current_time = get_current_time();
    current_time_ms = calculate_elapsed_time(philo->info->start, current_time);	pthread_mutex_lock(&philo->info->write_lock); // error check
	printf(messages[msgtype], current_time, philo->id);
	pthread_mutex_unlock(&philo->info->write_lock);
}

// void	log_destroy()
// {
// 	pthread_mutex_destroy(logs->write_lock); // error check
// }