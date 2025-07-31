/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:44:59 by imellali          #+#    #+#             */
/*   Updated: 2025/07/31 22:09:41 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->sim->death_mutex);
	if (philo->sim->dead_flag)
	{
		pthread_mutex_unlock(&philo->sim->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->sim->death_mutex);
	timestamp = current_time() - philo->sim->start_time;
	pthread_mutex_lock(&philo->sim->print_mutex);
	printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->sim->print_mutex);
}

int	is_simulation_over(t_simulation *sim)
{
	int	result;

	pthread_mutex_lock(&sim->death_mutex);
	result = sim->dead_flag || sim->finished_eating;
	pthread_mutex_unlock(&sim->death_mutex);
	return (result);
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
		{
			pthread_mutex_unlock(philo->right_fork);
			return (1);
		}
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		if (is_simulation_over(philo->sim))
		{
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
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

int	check_death(t_philo *philo)
{
	long	current;
	long	last_meal;
	int		eating;

	pthread_mutex_lock(&philo->meal_mutex);
	current = current_time();
	last_meal = philo->last_meal_time;
	eating = philo->eating;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (!eating && (current - last_meal) >= philo->sim->config.time_to_die)
	{
		pthread_mutex_lock(&philo->sim->death_mutex);
		if (!philo->sim->dead_flag)
		{
			pthread_mutex_lock(&philo->meal_mutex);
			current = current_time();
			last_meal = philo->last_meal_time;
			eating = philo->eating;
			pthread_mutex_unlock(&philo->meal_mutex);
			if (!eating && (current
					- last_meal) >= philo->sim->config.time_to_die)
			{
				philo->sim->dead_flag = 1;
				pthread_mutex_unlock(&philo->sim->death_mutex);
				current = current_time() - philo->sim->start_time;
				pthread_mutex_lock(&philo->sim->print_mutex);
				printf("%ld %d died\n", current, philo->id);
				pthread_mutex_unlock(&philo->sim->print_mutex);
				return (1);
			}
		}
		pthread_mutex_unlock(&philo->sim->death_mutex);
	}
	return (0);
}

int	check_meal_completion(t_simulation *sim)
{
	int	i;
	int	all_ate_enough;

	if (!sim->config.must_eat_flag)
		return (0);
	pthread_mutex_lock(&sim->death_mutex);
	if (sim->dead_flag || sim->finished_eating)
	{
		pthread_mutex_unlock(&sim->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&sim->death_mutex);
	all_ate_enough = 1;
	i = 0;
	while (i < sim->config.num_philos)
	{
		pthread_mutex_lock(&sim->philosophers[i].meal_mutex);
		if (sim->philosophers[i].meals_eaten < sim->config.must_eat_count)
			all_ate_enough = 0;
		pthread_mutex_unlock(&sim->philosophers[i].meal_mutex);
		if (!all_ate_enough)
			break ;
		i++;
	}
	if (all_ate_enough)
	{
		pthread_mutex_lock(&sim->death_mutex);
		if (!sim->dead_flag)
			sim->finished_eating = 1;
		pthread_mutex_unlock(&sim->death_mutex);
		return (1);
	}
	return (0);
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
		if (is_simulation_over(philo->sim))
			break ;
		sleep_and_think(philo);
		if (philo->sim->config.num_philos > 2)
			ft_usleep(1);
	}
	return (NULL);
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
