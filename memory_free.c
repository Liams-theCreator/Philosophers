/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 00:17:32 by imellali          #+#    #+#             */
/*   Updated: 2025/08/05 13:46:39 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_mutex(t_simulation *sim)
{
	int	i;

	if (!sim)
		return ;
	if (sim->forks)
	{
		i = 0;
		while (i < sim->config.num_philos)
		{
			pthread_mutex_destroy(&sim->forks[i]);
			i++;
		}
		free(sim->forks);
		sim->forks = NULL;
	}
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->death_mutex);
	pthread_mutex_destroy(&sim->meal_mutex);
}

void	cleanup_simulation(t_simulation *sim)
{
	int	i;

	if (!sim)
		return ;
	if (sim->philosophers)
	{
		i = 0;
		while (i < sim->config.num_philos)
		{
			pthread_mutex_destroy(&sim->philosophers[i].meal_mutex);
			i++;
		}
		free(sim->philosophers);
		sim->philosophers = NULL;
	}
	cleanup_mutex(sim);
}
