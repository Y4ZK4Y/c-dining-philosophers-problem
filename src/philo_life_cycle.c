#include "philo.h"

int	right_index(t_philo *philo)
{
	int	index;

	index = philo->id;
	if (philo->id == philo->info->input.num_of_philos)
		index = 0;
	return (index);
}


int	pickup_forks(t_philo *philo)
{
	int	fork_index[2];

	fork_index[0] = philo->id - 1;
	fork_index[1] = right_index(philo);
	// check to see both forks are available to pick up(left then right)
	// if not, wait, change status to hungry
	// if forks available
	// lock forks
	log_message(philo, TAKEN_FORK);
	return 0;
}
// int	put_down_forks(t_philo *philo)
// {
// 	//unlock forks

// }
void	think(t_philo *philo)
{
	log_message(philo, THINKING);
}

void philo_sleep(t_philo *philo)
{
	// set status to sleeping
	log_message(philo, SLEEPING);
	usleep(philo->info->input.time_to_sleep * 1000);
}

void	eat(t_philo *philo)
{
	// set status to eating
	log_message(philo, EATING);
	philo->last_meal_time = get_current_time();
	philo->num_meals++;
	usleep(philo->info->input.time_to_eat * 1000);
}

// single_philo()
// {

// }

void	*philo_life_cycle(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (init_monitor(philo->info) == 1)
	{
		printf("init monitor got fugged\n");
		
	}
	while (philo->dead == false)
	{
		think(philo);
		pickup_forks(philo);
		eat(philo);
		//put_down_forks(philo);
		philo_sleep(philo);
		usleep(1000);
	}

	if (pthread_join(philo->info->monitor->thread, NULL) != 0)
	{
		printf("pthread create got fucked\n");
		
	}

	return (NULL);
}