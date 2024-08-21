/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:35:23 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/21 17:56:54 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <string.h>
# include <errno.h>
# include <limits.h>

/******************************************************************************/
/* Macros */


/******************************************************************************/
/* Data Structures */

typedef struct s_info	t_info;

enum e_states
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
};

typedef struct s_philo
{
	t_info				*info;
	int					id;
	pthread_t			thread;
	pthread_t			monitor;
	long				last_meal_time;
	enum e_states		philo_state;
	pthread_mutex_t		death_mutex;
	int					left_fork;
	int					right_fork;

}						t_philo;

/* Commandline arguments the program receives */
typedef struct s_input
{
	int					num_philos;
	long				time_die;
	int					time_eat;
	int					time_sleep;
}						t_input;

/* One main struct to rule them all */
typedef struct s_info
{
	t_input				input;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		start_lock; // for a synchronized start
	pthread_mutex_t		end_lock; // for when someone dies - protects philo_died flag
	long				start_time;
	int					philo_died;
	//int					started;
}						t_info;

/******************************************************************************/
/* Parsing */
int				get_input(t_input *input, int argc, char *argv[]);
int				parse_input(t_input *input, int argc, char *argv[]);

/* Initializing the program */
int				init(t_info *info);
void			init_philos(t_info *info);
int				init_locks(t_info *info);

/* Threads */
int				create_threads(t_info *info);
int				join_threads(t_info *info);

/* Philosophers routine */
void			*philo_routine(void *arg);
void			pickup_forks(t_philo *philo);
void			eat(t_philo *philo);
void			philo_sleep(t_philo *philo);

/* Monitor thread */
void			*monitor_routine(void *arg);
int				init_monitor(t_philo *philo);

/* Log */
void			log_message(t_philo *philo, enum e_states philo_state);

/* Time keeping functions */
long			get_time(void);
long			elapsed_time(long start);
void			ft_usleep(long time, t_philo *philo);

/* Error Handling */
void			print_error(char *errmsg);
void			cleanup(t_info *info);
void			program_end(t_info *info);

/* Philo utils (wrappers) */
bool			has_philo_died(t_info *info);
enum e_states	philo_state(t_philo *philo);

/* Utility Functions */
long			ft_strtol(const char *str, char **endptr, int base);
int				ft_isalnum(int c);
int				ft_isdigit(int c);

#endif
