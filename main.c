/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:34:49 by imellali          #+#    #+#             */
/*   Updated: 2025/07/29 15:52:07 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	sim;
	int				i;

	if (argc < 5 || argc > 6)
		return (ft_man(), -1);
	if (ft_parse(argc, argv, &sim.config))
		return (ft_man(), -1);
	if (init_simulation(&sim))
		return (cleanup_simulation(&sim), -1);
	sim.start_time = current_time();
	if (pthread_create(&sim.watcher_thread, NULL, watcher_routine, &sim) != 0)
	{
		printf("Failed to create watcher thread\n");
		cleanup_simulation(&sim);
		return (-1);
	}
	i = 0;
	while (i < sim.config.num_philos)
	{
		if (pthread_create(&sim.philosophers[i].thread, NULL,
				philosopher_routine, &sim.philosophers[i]) != 0)
		{
			printf("Failed to create philosopher thread\n");
			cleanup_simulation(&sim);
			return (-1);
		}
		i++;
	}
	i = 0;
	while (i < sim.config.num_philos)
	{
		pthread_join(sim.philosophers[i].thread, NULL);
		i++;
	}
	pthread_join(sim.watcher_thread, NULL);
	cleanup_simulation(&sim);
	return (0);
}
