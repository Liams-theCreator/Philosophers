/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:14:13 by imellali          #+#    #+#             */
/*   Updated: 2025/04/29 17:39:02 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	config->num_philos = atoi(argv[1]);
	config->time_to_die = atoi(argv[2]);
	config->time_to_eat = atoi(argv[3]);
	config->time_to_sleep = atoi(argv[4]);
	config->must_eat_flag = 0;
	if (argc == 6)
	{
		if (!is_pos(argv[5]))
			return (1);
		config->must_eat_count = atoi(argv[5]);
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
	printf("Usage:
		%s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
		prog_name);
	printf("All arguments must be positive integers.\n");
}
