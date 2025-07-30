/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:44:59 by imellali          #+#    #+#             */
/*   Updated: 2025/07/30 17:57:50 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timestamp(t_simulation *sim)
{
	return (current_time() - sim->start_time);
}

void	print_status(t_philo *philo, const char *msg, int is_death)
{
	t_simulation *sim = philo->sim;
	long ms = current_time() - sim->start_time;

	pthread_mutex_lock(&sim->print_mutex);
	pthread_mutex_lock(&sim->death_mutex);
	if (!sim->dead_flag || is_death)
	{
		printf("%ld %d %s\n", ms, philo->id, msg);
		if (is_death)
			sim->dead_flag = 1;
	}
	pthread_mutex_unlock(&sim->death_mutex);
	pthread_mutex_unlock(&sim->print_mutex);
}

void	thinking(t_philo *philo)
{
	print_status(philo, "is thinking", 0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);

	print_status(philo, "is eating", 0);
	ft_usleep(philo->sim->config.time_to_eat);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping", 0);
	ft_usleep(philo->sim->config.time_to_sleep);
}

void	eating(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork", 0);
		ft_usleep(philo->sim->config.time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork", 0);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork", 0);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork", 0);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork", 0);
	}
	eat(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*watcher(void *arg)
{
	t_simulation *sim = (t_simulation *)arg;
	int	i;
	long	now;
	long	last_meal;
	int	ate_enough;

	while (1)
	{
		i = 0;
		while (i < sim->config.num_philos)
		{
			pthread_mutex_lock(&sim->philosophers[i].meal_mutex);
			last_meal = sim->philosophers[i].last_meal_time;
			pthread_mutex_unlock(&sim->philosophers[i].meal_mutex);

			now = current_time();
			pthread_mutex_lock(&sim->death_mutex);
			if (!sim->dead_flag && (now - last_meal > sim->config.time_to_die))
			{
				print_status(&sim->philosophers[i], "died", 1);
				pthread_mutex_unlock(&sim->death_mutex);
				return NULL;
			}
			pthread_mutex_unlock(&sim->death_mutex);
			i++;
		}
		ate_enough = 1;
		if (sim->config.must_eat_flag && sim->config.must_eat_count > 0)
		{
			i = 0;
			while (i < sim->config.num_philos)
			{
				pthread_mutex_lock(&sim->philosophers[i].meal_mutex);
				if (sim->philosophers[i].meals_eaten < sim->config.must_eat_count)
					ate_enough = 0;
				pthread_mutex_unlock(&sim->philosophers[i].meal_mutex);
				i++;
			}
			if (ate_enough)
			{
				pthread_mutex_lock(&sim->death_mutex);
				sim->dead_flag = 1;
				pthread_mutex_unlock(&sim->death_mutex);
				return NULL;
			}
		}
		ft_usleep(10);
	}
	return NULL;
}

void	*routine(void *arg)
{
	t_philo *philo = arg;

	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = current_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	while (1)
	{
		pthread_mutex_lock(&philo->sim->death_mutex);
		if (philo->sim->dead_flag) {
			pthread_mutex_unlock(&philo->sim->death_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->sim->death_mutex);
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
	return NULL;
}
