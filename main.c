/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:34:49 by imellali          #+#    #+#             */
/*   Updated: 2025/07/27 00:50:27 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (argc < 5 || argc > 6)
		return (ft_man(), -1);
	if (ft_parse(argc, argv, &sim.config))
		return (ft_man(), -1);
	if (init_simulation(&sim))
		return (cleanup_simulation(&sim), -1);
	// TODO: Later you'll add thread creation here
	printf("Simulation initialized successfully!\n");
	printf("Philosophers: %d\n", sim.config.num_philos);
	printf("Time to die: %d ms\n", sim.config.time_to_die);
	printf("Time to eat: %d ms\n", sim.config.time_to_eat);
	printf("Time to sleep: %d ms\n", sim.config.time_to_sleep);
	if (sim.config.must_eat_flag)
		printf("Must eat count: %d\n", sim.config.must_eat_count);
	
	cleanup_simulation(&sim);
	return (0);
}
