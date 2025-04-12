/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:40:17 by imellali          #+#    #+#             */
/*   Updated: 2025/04/12 18:21:24 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_config
{
    int number_of_philos; 
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
}   t_config;

#endif
