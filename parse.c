/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:14:13 by imellali          #+#    #+#             */
/*   Updated: 2025/08/05 13:46:36 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parse(int argc, char **argv, t_config *config)
{
	if (!is_pos(argv[1]) || !is_pos(argv[2]) || !is_pos(argv[3])
		|| !is_pos(argv[4]))
		return (1);
	config->num_philos = ft_atoi(argv[1]);
	if (config->num_philos > 200)
		return (1);
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

void	ft_man(void)
{
	printf("Usage: `num_philos` `time_to_die` `time_to_eat` "
		"`time_to_sleep` `must_eat_count`\n");
}
