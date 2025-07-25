/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:14:13 by imellali          #+#    #+#             */
/*   Updated: 2025/07/25 08:11:24 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	i;

	i = 0;
	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	if (dstsize > srclen)
	{
		while (src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
		return (srclen);
	}
	while (i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}

static size_t	ft_check(char c)
{
	char	chr[7];
	size_t	i;

	i = 0;
	ft_strlcpy(chr, " \t\v\r\n\f", 8);
	while (chr[i] != '\0')
	{
		if (chr[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_check(str[i]) == 1)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	is_pos(const char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_parse(int argc, char **argv, t_config *config)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (!is_pos(argv[1]) || !is_pos(argv[2]) || !is_pos(argv[3])
		|| !is_pos(argv[4]))
		return (1);
	config->num_philos = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	config->must_eat_flag = 0;
	if (argc == 6)
	{
		if (!is_pos(argv[5]))
			return (1);
		config->must_eat_count = ft_atoi(argv[5]);
		config->must_eat_flag = 1;
	}
	else
		config->must_eat_count = -1;
	if (config->num_philos < 1 || config->time_to_die < 1
		|| config->time_to_eat < 1 || config->time_to_sleep < 1
		|| (config->must_eat_flag && config->must_eat_count < 1))
		return (1);
	return (0);
}
void	ft_usage(char *prog_name)
{
	printf("Usage: %s <num_philos> <time_to_die> <time_to_eat> "
		"<time_to_sleep> [<must_eat_count>]\n", prog_name);
	printf("All arguments must be positive integers.\n");
}
