/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_handling.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: yasamankarimi <yasamankarimi@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/03 20:21:54 by yasamankari   #+#    #+#                 */
/*   Updated: 2024/08/20 12:18:32 by yasamankari   ########   odam.nl         */
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
	while (i < info->input.num_of_philos)
	{
		pthread_mutex_destroy(&info->forks[i]);
		pthread_mutex_destroy(&info->philos[i].state_mutex);
		i++;
	}
	pthread_mutex_destroy(&info->write_lock);
	pthread_mutex_destroy(&info->start_lock);
	cleanup(info);
}

