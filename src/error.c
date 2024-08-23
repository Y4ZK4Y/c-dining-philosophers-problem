/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:21:54 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/23 15:55:59 by ykarimi       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
static void	ft_putstr_fd(char *s, int fd)
{
	if (s == 0 || *s == 0)
		return ;
	write(fd, s, ft_strlen(s));
}

/* Writing errors to STDERR */
void	print_error(char *errmsg)
{
	ft_putstr_fd("Erorr: ", STDERR_FILENO);
	ft_putstr_fd(errmsg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	cleanup(t_info *info)
{
	if (info->philos != NULL)
		free(info->philos);
	if (info->forks != NULL)
		free(info->forks);
}

void program_end(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->input.num_philos)
	{
		pthread_mutex_destroy(&info->forks[i]);
		pthread_mutex_destroy(&info->philos[i].death_lock);
		i++;
	}
	pthread_mutex_destroy(&info->write_lock);
	pthread_mutex_destroy(&info->start_lock);
	pthread_mutex_destroy(&info->end_lock);
	//pthread_mutex_destroy(&info->time_keeping_lock);
	cleanup(info);
}

