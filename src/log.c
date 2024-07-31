#include "philo.h"



void	log_message(t_philo *philo, msg_type msgtype)
{
	pthread_mutex_lock(&philo->info->logs->write_lock); // error check
	printf("%s\n", messages[msgtype]);
	pthread_mutex_unlock(&philo->info->logs->write_lock);
}

void	log_destroy()
{
	pthread_mutex_destroy(logs->write_lock); // error check
}