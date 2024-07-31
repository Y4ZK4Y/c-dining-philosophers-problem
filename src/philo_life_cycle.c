#include "philo.h"


int	pickup_forks()
{
	log_message();

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

void	*philo_life_cycle(void *ptr)
{
	t_philo	*philo;
	philo = ptr;

	init_monitor(philo->info->monitor);
	while (philo alive)
	{
		think();
		pickup_forks();
		eat();
		sleep();
		//uspleep(1000);
	}
	pthread_join(monitor, NULL);


	
	return (NULL);
}