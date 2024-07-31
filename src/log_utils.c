#include "philo.h"

void	ft_bzero(void *s, size_t n)
{
	memset(s, 0, n);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == 0 || *s == 0)
		return ;
	write(fd, s, ft_strlen(s));
}

/* Write error messages to standard error */
// error()
// {
// 	ft_putstr_fd(STDERR_FILENO, "Error: ");
// 	if ()
// 		ft_putstr_fd(STDERR_FILENO, );
// 	if ()
// 	{

// 	}

// }