/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:14:44 by imellali          #+#    #+#             */
/*   Updated: 2025/04/30 16:31:36 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_config	config;
	t_data		data;
	int			i;

	if (ft_parse(argc, argv, &config))
	{
		ft_usage(argv[0]);
		return (1);
	}
	if (init_data(&data, &config))
	{
		write(2, "Error: initialization failed\n", 28);
		return (1);
	}
	printf("Initialization succeeded!\n");
	printf("Number of philosophers: %d\n", data.config.num_philos);
	printf("Time to die: %d ms\n", data.config.time_to_die);
	printf("Time to eat: %d ms\n", data.config.time_to_eat);
	printf("Time to sleep: %d ms\n", data.config.time_to_sleep);
	if (data.config.must_eat_flag)
		printf("Meals required per philosopher: %d\n", data.config.must_eat_count);
	else
		printf("Meals required per philosopher: unlimited\n");
	printf("Simulation start time: %ld ms\n", data.start_time_ms);
	printf("Stop flag: %d\n", data.stop_sim);

	i = 0;
	while (i < data.config.num_philos)
	{
		printf("Philo %d:\n", data.philos[i].id);
		printf("  Address:        %p\n", (void*)&data.philos[i]);
		printf("  Meals eaten:    %d\n", data.philos[i].meals_eaten);
		printf("  Last meal:      %ld ms\n", data.philos[i].last_meal_ms);
		printf("  Left fork:      %p\n", (void*)data.philos[i].left_fork);
		printf("  Right fork:     %p\n", (void*)data.philos[i].right_fork);
		i++;
	}
	cleanup_data(&data);
	return (0);
}
