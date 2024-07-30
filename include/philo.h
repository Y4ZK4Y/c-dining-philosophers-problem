#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

/******************************************************************************/
/* Macros */

#define NUM_PHILOSOPHERS 5


/******************************************************************************/
/* Data Structures */

enum philo_states
{
	EATING,
	THINKING,
	SLEEPING,
	HUNGRY,
	DEAD,
};

typedef struct s_monitor
{
	pthread_t			thread;

}				t_monitor;

typedef struct s_forks
{
	pthread_mutex_t		fork;
	pthread_mutex_t		fork_plus;
}						t_forks;

typedef struct s_logging
{
	pthread_mutex_t		write_lock;
}						t_logging;


typedef struct s_philo
{
	int					id; // 1 to num_philo
	pthread_t			thread;
	int					last_meal_time;
	int					num_meals;
	enum philo_states	states;
	pthread_t			monitor; // in here or in info sstruct ?
	//t_info				*info;
	//pthread_mutex_t		lock;

} t_philo;

/* Commandline arguments the program receives */
typedef struct s_input
{
	int num_of_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep; // long long?
	//int num_times_to_eat; / optional
	int error;
}	t_input;


/* One main struct to rule them all*/
typedef struct s_info
{
	t_input				input;
	t_philo				*philos;
	t_forks				*forks;
	t_logging			*logs;
	// pthread_mutex_t		*fork;
	// pthread_mutex_t		*fork_plus; // or one mutex for both forks?
	int					lets_fuckin_go;
	bool				is_dead;
}						t_info;


/******************************************************************************/

/* Parsing */
int			get_input(t_input *input, int argc, char *argv[]);
int			parse_input(t_input *input, int argc, char *argv[]);

//void *func(void *arg);
// void* philosopher_routine(void* arg);

/* Utility Functions */

#endif