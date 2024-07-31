#include "philo.h"

int	start_monitor(t_info *info)
{
	bzero(&info->monitor, sizeof(t_monitor));
	info->monitor->thread= malloc(1 * sizeof(pthread_t));
	if (info->monitor->thread == NULL)
	{
		printf("malloc for monitor in philo init dedd\n");
		return 1;
	}
	if (pthrad_mutex_init(&(info->monitor->turn_lock), NULL) != 0)
	{
		printf("init lock for monitor went bad\n");
		return 1;
	}
	init_queue(monitor, );
	monitor->stop = false;
	return 0;

}

void	*monitor(void	*arg)
{
		t_monitor *monitor = (t_monitor *)arg;
	while (!monitor->stop) {
		pthread_mutex_lock(&monitor->turn_lock);
		if (monitor->queue_size > 0) {
			t_philo *philo = dequeue(monitor);
			if (philo) {
				// Grant resources to the philosopher
				// (e.g., allow them to take forks and eat)
				// This part depends on your specific implementation
			}
		}
		pthread_mutex_unlock(&monitor->turn_lock);
		usleep(1000); // Sleep for a short period to prevent busy waiting
	}
	return NULL;
}


// Initialize the priority queue
void init_queue(t_monitor *monitor, int capacity)
{
    monitor->queue = malloc(sizeof(t_philo *) * capacity);
    monitor->queue_size = 0;
    monitor->queue_capacity = capacity;
}

// Compare function to determine priority (e.g., based on hunger or wait time)
int compare_philos(t_philo *a, t_philo *b)
{
    // Example: prioritize based on the number of meals (less meals = higher priority)
    return a->num_meals - b->num_meals;
}

// Insert a philosopher into the priority queue
void enqueue(t_monitor *monitor, t_philo *philo)
{
    pthread_mutex_lock(&monitor->turn_lock);
    if (monitor->queue_size == monitor->queue_capacity)
	{
        // Resize the queue if necessary
        monitor->queue_capacity *= 2;
        monitor->queue = realloc(monitor->queue, sizeof(t_philo *) * monitor->queue_capacity);
    }
    monitor->queue[monitor->queue_size++] = philo;
    // Sort the queue based on priority
    for (int i = monitor->queue_size - 1; i > 0 && compare_philos(monitor->queue[i], monitor->queue[i - 1]) < 0; i--) {
        t_philo *temp = monitor->queue[i];
        monitor->queue[i] = monitor->queue[i - 1];
        monitor->queue[i - 1] = temp;
    }
    pthread_mutex_unlock(&monitor->turn_lock);
}

// Remove and return the highest priority philosopher from the queue
t_philo *dequeue(t_monitor *monitor)
{
    pthread_mutex_lock(&monitor->turn_lock);
    if (monitor->queue_size == 0) {
        pthread_mutex_unlock(&monitor->turn_lock);
        return NULL;
    }
    t_philo *philo = monitor->queue[--monitor->queue_size];
    pthread_mutex_unlock(&monitor->turn_lock);
    return philo;
}