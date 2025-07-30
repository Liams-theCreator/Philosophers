/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:44:59 by imellali          #+#    #+#             */
/*   Updated: 2025/07/30 15:09:42 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void thinking(t_philo *philo)
{
    printf("%d is thinking\n", philo->id);
}

void sitting(t_philo *philo)
{
    printf("%d is eating\n", philo->id);
    ft_usleep(1000);
}

void sleeping(t_philo *philo)
{
    printf("%d is sleeping\n", philo->id);
    ft_usleep(1000);
}

void sitting(t_philo *philo)
{
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    if (philo->left_fork == philo->right_fork)
    {
        pthread_mutex_lock(philo->left_fork);
        printf("%d picked up the only fork\n", philo->id);
        ft_usleep(1000);
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    if (philo->left_fork < philo->right_fork)
    {
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    }
    else
    {
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    }

    pthread_mutex_lock(first_fork);
    printf("%d picked up first fork\n", philo->id);
    pthread_mutex_lock(second_fork);
    printf("%d picked up second fork\n", philo->id);

    eating(philo);

    pthread_mutex_unlock(second_fork);
    pthread_mutex_unlock(first_fork);
}

void *philosopher_routine(void *arg)
{
    t_philo *philo;

    // if (philo->id % 2 == 0)
    //     ft_usleep(100);
	philo = arg;
    while (1)
    {
        thinking(philo);
        sitting(philo);
        sleeping(philo);
    }
    return NULL;
}
