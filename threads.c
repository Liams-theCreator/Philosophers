/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:40:46 by imellali          #+#    #+#             */
/*   Updated: 2025/08/05 22:50:11 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.num_philos)
	{
		if (pthread_join(sim->philosophers[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	if (sim->config.num_philos > 1)
	{
		if (pthread_join(sim->watcher_thread, NULL) != 0)
			return (1);
	}
	return (0);
}

int	start_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.num_philos)
	{
		if (pthread_create(&sim->philosophers[i].thread, NULL,
				philosopher_routine, &sim->philosophers[i]) != 0)
			return (1);
		i++;
	}
	if (sim->config.num_philos > 1)
	{
		if (pthread_create(&sim->watcher_thread, NULL, watcher_routine,
				sim) != 0)
			return (1);
	}
	return (0);
}

int	run_simulation(t_simulation *sim)
{
	if (start_simulation(sim))
		return (1);
	if (join_threads(sim))
		return (1);
	return (0);
}
