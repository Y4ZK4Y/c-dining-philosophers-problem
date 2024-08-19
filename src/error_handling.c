/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:21:54 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/19 16:24:23 by ykarimi       ########   odam.nl         */
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

static void	cleanup(t_info *info, int created)
{
	int	i;
	i = 0;
	if (created == info->input.num_of_philos)
	{
		if (info->philos != NULL)
			free(info->philos);
	}
	if (info->forks != NULL)
		free(info->forks);
}
// have to do the samething for state_mutex as well
static void	destroy_mutexes(t_info *info, int start_program)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&info->write_lock);
	pthread_mutex_destroy(&info->start_lock);
	if (start_program > 0)
	{
		while (start_program-- > 0)
		{
			pthread_mutex_destroy(&info->forks[start_program]);
		}
	}
	else
	{
		while (i < info->input.num_of_philos)
		{
			pthread_mutex_destroy(&info->forks[i]);
			pthread_mutex_destroy(&info->philos[i].state_mutex);
			i++;
		}
	}
}

void	error(char *errmsg, t_info *info, int start_program)
{
	write_stderr(errmsg);
	if (info != NULL)
		cleanup(info);
	destroy_mutexes(info, start_program);
}

