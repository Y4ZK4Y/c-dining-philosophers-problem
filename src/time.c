#include "philo.h"

struct timeval	get_current_time()
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv);
}

long	calculate_elapsed_time(struct timeval start, struct timeval end)
{
	long	seconds;
	long	mseconds;

	seconds = end.tv_sec - start.tv_sec;
	mseconds = end.tv_usec - start.tv_usec;
	return (seconds * 1000 + mseconds / 1000);
}