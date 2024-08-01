#include "philo.h"


void	*monitor(void *arg)
{
	t_philo *philo;
	philo = arg;
	struct timeval current_time;

	while (!philo->dead == false)
	{
		pthread_mutex_lock(&philo->info->monitor->turn_lock);
		gettimeofday(&current_time, NULL);
		if (calculate_elapsed_time(philo->last_meal_time, current_time) >= philo->info->input.time_to_die)
			log_message(philo, DIED);
		pthread_mutex_unlock(&philo->info->monitor->turn_lock);
		usleep(1000);
	}
	return NULL;
	
}