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
#include <ctype.h>

/******************************************************************************/
/* Macros */




/******************************************************************************/
/* Data Structures */

typedef struct s_info	t_info;
typedef enum
{
					TAKEN_FORK,
					EATING,
					SLEEPING,
					THINKING,
					DEAD,
					HUNGRY,
					INACTIVE,
					ACTIVE,
					NUM_MESSAGES
}					msg_type;


enum philo_states
{
					//ALIVE,
					THINKING,
					EATING,
					SLEEPING,
					DEAD,
					//HUNGRY,
					//INACTIVE,
};

typedef struct t_fork
{
	int				index;
	pthread_mutex_t	fork;
}					t_fork;


typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	long				last_meal_time;
	enum philo_states	philo_state;
	t_info				*info;
	// t_fork				*left_fork;
	// t_fork				*right_fork;
	pthread_mutex_t		state_mutex;
}						t_philo;

/* Commandline arguments the program receives */
typedef struct s_input
{
	int					num_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
}						t_input;

/* One main struct to rule them all */
typedef struct s_info
{
	t_input				input;
	t_philo				*philos;
	pthread_t			monitor;
	t_fork				*forks;
	pthread_mutex_t		write_lock;
	long				start_time;
	bool				sim_end;
}						t_info;

/******************************************************************************/
/* Parsing */
int				get_input(t_input *input, int argc, char *argv[]);
int				parse_input(t_input *input, int argc, char *argv[]);

/* Initializing the program */
int				init(t_info *info);
void			init_philos(t_info *info);
int				init_mutexes(t_info *info);
//int				init_monitor(t_info *info);

/* Simulation */
//int				sim(t_info *info);
int				create_threads(t_info *info);
int				wait_for_threads(t_info *info);
void			*philo_life_cycle(void *arg);
void			eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			think(t_philo *philo);

/* Monitor */
void			*monitor(void	*arg);


// /* Queue functions */
// t_queue			*create_queue(t_queue *q, t_info *info);
// int				enqueue(t_queue *q, int philo_id);
// int				dequeue(t_queue *q, int philo_id);
// int				is_empty(t_queue* q);
// int				is_full(t_queue* q);
// int				front(t_queue *q);
// int				back(t_queue *q);
// void			free_queue(t_queue *q);


/* Utility Functions */
void			ft_bzero(void *s, size_t n);
size_t			ft_strlen(char *s);
void			ft_putstr_fd(char *s, int fd);
long			ft_strtol(const char *str, char **endptr, int base);


/* Log */
void			log_message(t_philo *philo, msg_type msgtype);


/* Time keeping functions */
struct timeval	get_current_time();
long			calculate_elapsed_time(struct timeval start, struct timeval end);

//int	right_index(t_philo *philo);
bool	is_philo_dead(t_info *info, int philo_index);
void	*ft_malloc(size_t bytes);
void	error_exit(const char *errmsg, int exit_status);



#endif