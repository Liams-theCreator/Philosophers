/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:34:49 by imellali          #+#    #+#             */
/*   Updated: 2025/07/30 15:09:38 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.num_philos)
	{
		pthread_create(&sim->philosophers[i].thread, NULL, philosopher_routine,
				&sim->philosophers[i]);
		i++;
	}
	i = 0;
	while (i < sim->config.num_philos)
	{
		pthread_join(sim->philosophers[i].thread, NULL);
		i++;
	}
}

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
	create_threads(&sim);
	cleanup_simulation(&sim);
	return (0);
}
