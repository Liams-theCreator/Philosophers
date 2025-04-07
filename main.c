/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:25:26 by imellali          #+#    #+#             */
/*   Updated: 2025/04/04 17:20:11 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" // Suppose you place your structs and function prototypes here

int main(int argc, char **argv)
{
    t_config    config;
    t_philo     *philos;
    pthread_t   *threads;
    pthread_mutex_t *forks;
    int         i;

    if (parse_arguments(argc, argv, &config) == -1)
        return (EXIT_FAILURE);

    philos = malloc(sizeof(t_philo) * config.number_of_philos);
    threads = malloc(sizeof(pthread_t) * config.number_of_philos);
    forks = malloc(sizeof(pthread_mutex_t) * config.number_of_philos);

    for (i = 0; i < config.number_of_philos; i++)
        pthread_mutex_init(&forks[i], NULL);

    for (i = 0; i < config.number_of_philos; i++)
    {
        philos[i].id = i;
        philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + 1) % config.number_of_philos];
        philos[i].last_eat_time = 0;
        philos[i].times_eaten = 0;
        philos[i].config = &config;
        pthread_create(&threads[i], NULL, philosopher_routine, &philos[i]);
    }

    for (i = 0; i < config.number_of_philos; i++)
        pthread_join(threads[i], NULL);

    for (i = 0; i < config.number_of_philos; i++)
        pthread_mutex_destroy(&forks[i]);
    free(forks);
    free(threads);
    free(philos);
    return (0);
}