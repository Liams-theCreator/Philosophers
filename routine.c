/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:44:59 by imellali          #+#    #+#             */
/*   Updated: 2025/07/30 16:45:58 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void thinking(t_philo *philo)
{
    printf("%d is thinking\n", philo->id);
}

void eat(t_philo *philo)
{
    printf("%d is eating\n", philo->id);
    ft_usleep(1000);
}

void sleeping(t_philo *philo)
{
    printf("%d is sleeping\n", philo->id);
    ft_usleep(1000);
}

void eating(t_philo *philo)
{
    if (philo->left_fork == philo->right_fork)
    {
        pthread_mutex_lock(philo->left_fork);
        printf("%d pick up the fork\n", philo->id);
        ft_usleep(1000);
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        printf("%d pick up the left fork\n", philo->id);
        pthread_mutex_lock(philo->right_fork);
        printf("%d pick up the right fork\n", philo->id);
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        printf("%d pick up the right fork\n", philo->id);
        pthread_mutex_lock(philo->left_fork);
        printf("%d pick up the left fork\n", philo->id);
    }
    eat(philo);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
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
        eating(philo);
        sleeping(philo);
    }
    return NULL;
}
