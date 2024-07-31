#include "philo.h"


int	pickup_forks(t_philo *philo)
{
	log_message();

}
int	put_down_forks(t_philo *philo)
{

}
void	think(t_philo *philo)
{
	log_message(philo, THINKING);
}

void sleep(t_philo *philo)
{
	log(philo, SLEEPING);
	usleep(philo->info->input.time_to_sleep * 1000);
}



void	eat(t_philo *philo)
{
	log_message(philo, EATING);
	philo->last_meal_time = get_current_time();
	philo->num_meals++;
	usleep(philo->info->input.time_to_eat * 1000);
}

single_philo()
{

}

void	*philo_life_cycle(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (philo->info->sim_on)
	{
		think(philo);
		request_permission_to_eat(philo);
		pickup_forks(philo);
		eat(philo);
		put_down_forks(philo);
		sleep(philo);
		uspleep(1000);
	}
	pthread_join(monitor, NULL);

	return (NULL);
}