/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:18:06 by imellali          #+#    #+#             */
/*   Updated: 2025/05/01 09:51:04 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_data *data, int n)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			data->forks = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_philos(t_data *data, int n, long start_ms)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * n);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < n)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_ms = start_ms;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % n];
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

static int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (1);
	return (0);
}

int	init_data(t_data *data, t_config *config)
{
	data->config = *config;
	data->stop_sim = 0;
	data->start_time_ms = get_time_ms();
	data->forks = NULL;
	data->philos = NULL;
	if (init_forks(data, config->num_philos))
		return (1);
	if (init_philos(data, config->num_philos, data->start_time_ms))
	{
		free(data->forks);
		data->forks = NULL;
		return (1);
	}
	if (init_mutexes(data))
	{
		free(data->forks);
		free(data->philos);
		data->forks = NULL;
		data->philos = NULL;
		return (1);
	}
	return (0);
}

void	cleanup_data(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->config.num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	pthread_mutex_destroy(&data->print_mutex);
}
