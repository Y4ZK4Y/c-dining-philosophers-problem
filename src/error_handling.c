/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:21:54 by yasamankari   #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2024/08/13 10:23:57 by ykarimi       ########   odam.nl         */
=======
/*   Updated: 2024/08/12 17:25:02 by yasamankari   ########   odam.nl         */
>>>>>>> e507436b114563853af6faf015a3bf49aea133d1
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_putstr_fd(char *s, int fd)
{
	if (s == 0 || *s == 0)
		return ;
	write(fd, s, ft_strlen(s));
}

/* Writing errors to STDERR */
static void	write_stderr(char *errmsg)
{
	ft_putstr_fd("ERROR: ", STDERR_FILENO);
	if (errmsg)
		ft_putstr_fd(errmsg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static void	cleanup(t_info *info)
{
	if (info->philos != NULL)
		free(info->philos);
	if (info->forks != NULL)
		free(info->forks);
}

static void	destroy_mutexes(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->input.num_of_philos)
	{
		pthread_mutex_destroy(&info->forks[i]);
		//pthread_mutex_destroy(&info->philos[i].state_mutex);
		i++;
	}
	pthread_mutex_destroy(&info->write_lock);
}

void	error_exit(char *errmsg, int exit_status, t_info *info, int mutex)
{
	write_stderr(errmsg);
	if (info != NULL)
		cleanup(info);
	if (mutex == 0)
		destroy_mutexes(info);
	if (exit_status != NVM)
		exit(exit_status);
}
