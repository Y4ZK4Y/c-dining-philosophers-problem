#include "philo.h"

void	log_message(t_philo *philo, msg_type msgtype)
{
	long	current_time_ms;
	struct timeval current_time;
	const char *messages[NUM_MESSAGES] =
	{
		"timestamp:%ld, philo %d has taken a fork.\n",
		"timestamp:%ld, philo %d is eating.\n",
		"timestamp:%ld, philo %d is sleeping.\n",
		"timestamp:%ld, philo %d is thinking.\n",
		"timestamp:%ld, philo %d died.\n"
	};

	current_time = get_current_time();
    current_time_ms = calculate_elapsed_time(philo->info->start, current_time);
	pthread_mutex_lock(&philo->info->write_lock); // error check
	printf(messages[msgtype], current_time_ms, philo->id);
	pthread_mutex_unlock(&philo->info->write_lock);
}
