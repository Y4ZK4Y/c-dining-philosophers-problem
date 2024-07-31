#include "philo.h"

void	*monitor(void	*arg)
{
	t_monitor	*monitor;
	t_philo		*philo;

	monitor = (t_monitor *)arg;
	while (!monitor->stop)// or while sim_on or philos alive
	{
		if (philo status inactive)
			break;
		pthread_mutex_lock(&monitor->turn_lock);
		if (monitor->queue_size > 0)
		{
			philo = dequeue(monitor);
			if (philo)
			{
				// Grant resources to the philosopher
				// (e.g., allow them to take forks and eat)
				// This part depends on your specific implementation
			}
		}
		pthread_mutex_unlock(&monitor->turn_lock);
		usleep(1000);
	}
	return NULL;
}


// /* Compare function to determine priority (e.g., based on hunger or wait time) */
// int	compare_philos(t_philo *a, t_philo *b)
// {
// 	return (a->num_meals - b->num_meals);
// }

// /* Insert a philosopher into the priority queue */
// void	enqueue(t_monitor *monitor, t_philo *philo)
// {
// 	t_philo	*temp;

// 	pthread_mutex_lock(&monitor->turn_lock);
// 	if (monitor->queue_size == monitor->queue_capacity)
// 	{
// 		// Resize the queue if necessary
// 		monitor->queue_capacity *= 2;
// 		monitor->queue = realloc(monitor->queue, sizeof(t_philo *) * monitor->queue_capacity);
// 	}
// 	monitor->queue[monitor->queue_size++] = philo;
// 	// Sort the queue based on priority
// 	for (int i = monitor->queue_size - 1; i > 0 && compare_philos(monitor->queue[i], monitor->queue[i - 1]) < 0; i--)
// 	{
// 		temp = monitor->queue[i];
// 		monitor->queue[i] = monitor->queue[i - 1];
// 		monitor->queue[i - 1] = temp;
// 	}
// 	pthread_mutex_unlock(&monitor->turn_lock);
// }

// /* Remove and return the highest priority philosopher from the queue */
// t_philo	*dequeue(t_monitor *monitor)
// {
// 	t_philo	*philo;

// 	pthread_mutex_lock(&monitor->turn_lock);
// 	if (monitor->queue_size == 0)
// 	{
// 		pthread_mutex_unlock(&monitor->turn_lock);
// 		return NULL;
// 	}
// 	philo = monitor->queue[--monitor->queue_size];
// 	pthread_mutex_unlock(&monitor->turn_lock);
// 	return (philo);
// }





void	*monitor(void *arg)
{
	t_monitor *monitor;
	monitor = arg;

	while (!monitor->stop)
	{
		if ()
	}
	
}