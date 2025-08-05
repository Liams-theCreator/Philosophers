/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:44:59 by imellali          #+#    #+#             */
/*   Updated: 2025/08/05 22:39:41 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->sim->print_mutex);
	pthread_mutex_lock(&philo->sim->death_mutex);
	if (philo->sim->dead_flag)
	{
		pthread_mutex_unlock(&philo->sim->death_mutex);
		pthread_mutex_unlock(&philo->sim->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->sim->death_mutex);
	timestamp = current_time() - philo->sim->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->sim->print_mutex);
}

int	take_forks(t_philo *philo)
{
	if (is_simulation_over(philo->sim))
		return (1);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		if (is_simulation_over(philo->sim))
			return (pthread_mutex_unlock(philo->right_fork), 1);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		if (is_simulation_over(philo->sim))
			return (pthread_mutex_unlock(philo->left_fork), 1);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	return (0);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->eating = 1;
	philo->last_meal_time = current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, "is eating");
	ft_usleep(philo->sim->config.time_to_eat);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->meal_mutex);
}

void	sleep_and_think(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->sim->config.time_to_sleep);
	print_status(philo, "is thinking");
}
