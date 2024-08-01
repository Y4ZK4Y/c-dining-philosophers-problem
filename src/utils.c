#include "philo.h"

static int	check_and_adjust_base(const char **str, char **endptr, int *base)
{
	if (*base < 0 || *base == 1 || *base > 36)
	{
		if (endptr)
			*endptr = (char *)*str;
		errno = EINVAL;
		return (-1);
	}
	if (*base == 0)
	{
		if (**str == '0')
		{
			(*str)++;
			if (**str == 'x' || **str == 'X')
			{
				*base = 16;
				(*str)++;
			}
			else
				*base = 8;
		}
		else
			*base = 10;
	}
	return (0);
}

static long	parse_number(const char **str, int base, \
						int is_negative, char **endptr)
{
	unsigned long	result;
	int				digit;

	result = 0;
	while (isalnum(**str))
	{
		if (isdigit(**str))
			digit = **str - '0';
		else if (isupper(**str))
			digit = **str - 'A' + 10;
		else
			digit = **str - 'a' + 10;
		if (digit >= base)
			break ;
		result = result * base + digit;
		(*str)++;
	}
	if (endptr)
		*endptr = (char *)*str;
	if (is_negative)
		return (-(long)result);
	else
		return ((long)result);
}

long	ft_strtol(const char *str, char **endptr, int base)
{
	int	is_negative;

	is_negative = 0;
	while (isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		is_negative = (*str == '-');
		str++;
	}
	if (check_and_adjust_base(&str, endptr, &base) == -1)
		return (0);
	return (parse_number(&str, base, is_negative, endptr));
}
