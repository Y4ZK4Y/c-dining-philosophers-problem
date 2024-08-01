#include "philo.h"

// int	right_index(t_philo *philo)
// {
// 	int	index;

// 	index = philo->id;
// 	if (philo->id == philo->info->input.num_of_philos)
// 		index = 0;
// 	return (index);
// }

int	pickup_forks(t_philo *philo)
{
	// int	fork_index[2];

	// fork_index[0] = philo->id - 1;
	// fork_index[1] = right_index(philo);
	// check to see both forks are available to pick up(left then right)
	// if not, wait, change status to hungry
	// if forks available
	// lock forks

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);

	log_message(philo, TAKEN_FORK);
	return 0;
}

int	put_down_forks(t_info *info)
{
	pthread_mutex_unlock(info->philos->left_fork);
	pthread_mutex_unlock(info->philos->right_fork);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_mutex);
	philo->philo_state = THINKING;
	log_message(philo, THINKING);
	pthread_mutex_unlock(&philo->state_mutex);
	usleep(1000);
}

void philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->state_mutex);
	philo->philo_state = SLEEPING;
	log_message(philo, SLEEPING);
	pthread_mutex_unlock(&philo->state_mutex);
	usleep(philo->info->input.time_to_sleep * 1000);
}

void	eat(t_philo *philo)
{
	philo->philo_state = EATING;
	log_message(philo, EATING);
	philo->last_meal_time = get_current_time();
	usleep(philo->info->input.time_to_eat * 1000);
}


bool is_philo_dead(t_info *info, int philo_index)
{
    struct timeval current_time = get_current_time();
    long elapsed_time = calculate_elapsed_time(info->philos[philo_index].last_meal_time, current_time);

    if (elapsed_time > info->input.time_to_die)
        return true;
    else
        return false;
}

void	*philo_life_cycle(void *arg)
{
	t_philo	*philo;

	philo = arg;

	while (1)
	{
		if (is_philo_dead(philo->info) == true)
		{
			pthread_mutex_lock(&philo->state_mutex);
			philo->philo_state = DEAD;
			log_message(philo, DEAD);
			pthread_mutex_unlock(&philo->state_mutex);
			return (NULL);
		}
		think(philo);
		pickup_forks(philo);
		eat(philo);
		put_down_forks(philo);
		philo_sleep(philo);
		usleep(1000);
	}
	return (NULL);
}
