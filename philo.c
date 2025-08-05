/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:42:45 by imellali          #+#    #+#             */
/*   Updated: 2025/08/03 16:56:08 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_status(t_philo *philo, long *current, long *last_meal, int *eating)
{
	pthread_mutex_lock(&philo->meal_mutex);
	*current = current_time();
	*last_meal = philo->last_meal_time;
	*eating = philo->eating;
	pthread_mutex_unlock(&philo->meal_mutex);
}

void	*single_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = philo->sim->start_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, "has taken a fork");
	ft_usleep(philo->sim->config.time_to_die);
	print_status(philo, "died");
	return (NULL);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->sim->config.num_philos == 1)
		return (single_philo_routine(arg));
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = philo->sim->start_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->id % 2 == 0)
		ft_usleep(philo->sim->config.time_to_eat / 2);
	while (!is_simulation_over(philo->sim))
	{
		if (take_forks(philo))
			break ;
		eat(philo);
		drop_forks(philo);
		if (philo->meals_eaten == philo->sim->config.must_eat_count)
			return (NULL);
		if (is_simulation_over(philo->sim))
			break ;
		sleep_and_think(philo);
		if (philo->sim->config.num_philos > 2)
			ft_usleep(1);
	}
	return (NULL);
}
