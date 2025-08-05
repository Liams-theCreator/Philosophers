/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:39:34 by imellali          #+#    #+#             */
/*   Updated: 2025/08/05 22:50:10 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_over(t_simulation *sim)
{
	int	result;

	pthread_mutex_lock(&sim->death_mutex);
	result = sim->dead_flag || sim->finished_eating;
	pthread_mutex_unlock(&sim->death_mutex);
	return (result);
}

int	check_death(t_philo *philo)
{
	long	current;
	long	last_meal;
	int		eating;

	get_status(philo, &current, &last_meal, &eating);
	if (!eating && (current - last_meal) >= philo->sim->config.time_to_die + 2)
	{
		pthread_mutex_lock(&philo->sim->death_mutex);
		if (!philo->sim->dead_flag)
		{
			get_status(philo, &current, &last_meal, &eating);
			if (!eating && (current
					- last_meal) >= philo->sim->config.time_to_die + 2)
			{
				philo->sim->dead_flag = 1;
				pthread_mutex_unlock(&philo->sim->death_mutex);
				current = current_time() - philo->sim->start_time;
				pthread_mutex_lock(&philo->sim->print_mutex);
				printf("%ld %d died\n", current, philo->id);
				return (pthread_mutex_unlock(&philo->sim->print_mutex), 1);
			}
		}
		pthread_mutex_unlock(&philo->sim->death_mutex);
	}
	return (0);
}

int	all_eat(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.num_philos)
	{
		pthread_mutex_lock(&sim->philosophers[i].meal_mutex);
		if (sim->philosophers[i].meals_eaten < sim->config.must_eat_count)
		{
			pthread_mutex_unlock(&sim->philosophers[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&sim->philosophers[i].meal_mutex);
		i++;
	}
	return (1);
}

int	check_meal_completion(t_simulation *sim)
{
	if (!sim->config.must_eat_flag)
		return (0);
	pthread_mutex_lock(&sim->death_mutex);
	if (sim->dead_flag || sim->finished_eating)
	{
		pthread_mutex_unlock(&sim->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&sim->death_mutex);
	if (all_eat(sim))
	{
		pthread_mutex_lock(&sim->death_mutex);
		if (!sim->dead_flag)
			sim->finished_eating = 1;
		pthread_mutex_unlock(&sim->death_mutex);
		return (1);
	}
	return (0);
}

void	*watcher_routine(void *arg)
{
	t_simulation	*sim;
	int				i;

	sim = (t_simulation *)arg;
	if (sim->config.num_philos == 1)
		return (NULL);
	ft_usleep(10);
	while (!is_simulation_over(sim))
	{
		i = 0;
		while (i < sim->config.num_philos && !is_simulation_over(sim))
		{
			if (check_death(&sim->philosophers[i]))
				return (NULL);
			i++;
		}
		if (sim->config.must_eat_flag && check_meal_completion(sim))
			return (NULL);
		ft_usleep(1);
	}
	return (NULL);
}
