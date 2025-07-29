/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:24:54 by imellali          #+#    #+#             */
/*   Updated: 2025/07/29 15:51:28 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_status(t_philo *philo, const char *msg)
{
	pthread_mutex_lock(&philo->sim->print_mutex);
	printf("%ld %d %s\n", current_time() - philo->sim->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->sim->print_mutex);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;


	while (1)
	{
		pthread_mutex_lock(&philo->sim->death_mutex);
		if (philo->sim->dead_flag || philo->sim->finished_eating)
		{
			pthread_mutex_unlock(&philo->sim->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->sim->death_mutex);

		print_status(philo, "is thinking");

		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->right_fork);
			print_status(philo, "has take the right fork");
			pthread_mutex_lock(philo->left_fork);
			print_status(philo, "has take the left fork");
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			print_status(philo, "has take the right fork");
			pthread_mutex_lock(philo->right_fork);
			print_status(philo, "has take the left fork");
		}

        pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal_time = current_time();
		philo->eating = 1;
		print_status(philo, "is eating");
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_mutex);

		ft_usleep(philo->sim->config.time_to_eat);

		pthread_mutex_lock(&philo->meal_mutex);
		philo->eating = 0;
		pthread_mutex_unlock(&philo->meal_mutex);

		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		print_status(philo, "na3ess");
		ft_usleep(philo->sim->config.time_to_sleep);
	}
	return (NULL);
}

void	*watcher_routine(void *arg)
{
	t_simulation	*sim = (t_simulation *)arg;
	int				i;
	int				done;

	while (1)
	{
		done = 0;
		i = 0;
		while (i < sim->config.num_philos)
		{
			t_philo *philo = &sim->philosophers[i];

			pthread_mutex_lock(&philo->meal_mutex);
			if (current_time() - philo->last_meal_time > sim->config.time_to_die)
			{
				pthread_mutex_lock(&sim->print_mutex);
				printf("%ld %d died\n", current_time() - sim->start_time, philo->id);
				pthread_mutex_unlock(&sim->print_mutex);
				sim->dead_flag = 1;
				pthread_mutex_unlock(&philo->meal_mutex);
				return (NULL);
			}
			if (sim->config.must_eat_flag && philo->meals_eaten >= sim->config.must_eat_count)
				done++;
			pthread_mutex_unlock(&philo->meal_mutex);

			i++;
		}
		if (sim->config.must_eat_flag && done == sim->config.num_philos)
		{
			sim->finished_eating = 1;
			return (NULL);
		}
		usleep(1000);
	}
}
