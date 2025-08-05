/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 22:35:25 by imellali          #+#    #+#             */
/*   Updated: 2025/08/05 15:19:18 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_simulation *sim)
{
	int	i;

	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->config.num_philos);
	if (!sim->forks)
		return (1);
	i = 0;
	while (i < sim->config.num_philos)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&sim->forks[i]);
			return (free(sim->forks), sim->forks = NULL, 1);
		}
		i++;
	}
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
		return (cleanup_mutex(sim), 1);
	if (pthread_mutex_init(&sim->death_mutex, NULL) != 0)
		return (cleanup_mutex(sim), 1);
	if (pthread_mutex_init(&sim->meal_mutex, NULL) != 0)
		return (cleanup_mutex(sim), 1);
	return (0);
}

int	init_philosophers(t_simulation *sim)
{
	int	i;

	sim->philosophers = malloc(sizeof(t_philo) * sim->config.num_philos);
	if (!sim->philosophers)
		return (1);
	i = 0;
	while (i < sim->config.num_philos)
	{
		sim->philosophers[i].id = i + 1;
		sim->philosophers[i].meals_eaten = 0;
		sim->philosophers[i].last_meal_time = 0;
		sim->philosophers[i].eating = 0;
		sim->philosophers[i].sim = sim;
		sim->philosophers[i].left_fork = &sim->forks[i];
		sim->philosophers[i].right_fork = &sim->forks[(i + 1)
			% sim->config.num_philos];
		if (pthread_mutex_init(&sim->philosophers[i].meal_mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&sim->philosophers[i].meal_mutex);
			return (free(sim->philosophers), sim->philosophers = NULL, 1);
		}
		i++;
	}
	return (0);
}

int	init_simulation(t_simulation *sim)
{
	sim->philosophers = NULL;
	sim->forks = NULL;
	sim->start_time = 0;
	sim->dead_flag = 0;
	sim->finished_eating = 0;
	if (init_mutexes(sim))
		return (1);
	if (init_philosophers(sim))
		return (cleanup_mutex(sim), 1);
	sim->start_time = current_time();
	if (sim->start_time == -1)
		return (cleanup_simulation(sim), 1);
	return (0);
}
