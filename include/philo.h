/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:35:23 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/20 21:03:18 by yasamankari   ########   odam.nl         */
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

enum e_philo_states
{
	TAKEN_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	INACTIVE,
	ACTIVE,
};

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	long				last_meal_time;
	enum e_philo_states	philo_state;
	t_info				*info;
	pthread_mutex_t		state_mutex;
	int					left_fork_index;
	int					right_fork_index;
}						t_philo;

/* Commandline arguments the program receives */
typedef struct s_input
{
	int					num_of_philos;
	long				time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
}						t_input;

/* One main struct to rule them all */
typedef struct s_info
{
	t_input				input;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		start_lock;
	long				start_time;
	bool				end;
}						t_info;

/******************************************************************************/
/* Parsing */
int				get_input(t_input *input, int argc, char *argv[]);
int				parse_input(t_input *input, int argc, char *argv[]);

/* Initializing the program */
int				init(t_info *info);
void			init_philos(t_info *info);
int				init_mutexes(t_info *info);

/* Simulation */
int				create_threads(t_info *info);
int				join_threads(t_info *info);
void			*philo_life_cycle(void *arg);
void			eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			think(t_philo *philo);
void			pickup_forks(t_philo *philo);
void			*monitor(t_info	*info);

/* Utility Functions */
size_t			ft_strlen(char *s);
long			ft_strtol(const char *str, char **endptr, int base);
int				ft_isalnum(int c);
int				ft_isdigit(int c);

/* Log */
void			log_message(t_philo *philo, enum e_philo_states philo_state);

/* Time keeping functions */
long	get_current_time(void);
long			calculate_elapsed_time(long start);
void			ft_usleep(long time, t_philo *philo);

/* Error Handling */
void			print_error(char *errmsg);
void			program_end(t_info *info);
void			cleanup(t_info *info);

#endif
