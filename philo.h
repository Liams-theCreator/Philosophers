/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:13:53 by imellali          #+#    #+#             */
/*   Updated: 2025/04/30 16:17:33 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

typedef struct s_config
{
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat_count;
	int		must_eat_flag;
}	t_config;

typedef struct s_data
{
	t_config		config;
	struct s_philo	*philos;        // Array of philosophers
	pthread_mutex_t	*forks;         // Array of fork mutexes
	pthread_mutex_t	print_mutex;    // Mutex for logging
	int				stop_sim;       // Flag to signal end of simulation
	long			start_time_ms;  // Simulation start timestamp
}	t_data;

typedef struct s_philo
{
	int				id;             // Philosopher ID (1-based)
	int				meals_eaten;    // Number of times this philosopher ate
	long			last_meal_ms;   // Timestamp of last meal (ms)
	pthread_t		thread;         // Philosopher thread
	pthread_mutex_t	*left_fork;     // Pointer to left fork mutex
	pthread_mutex_t	*right_fork;    // Pointer to right fork mutex
	t_data			*data;          // Pointer to shared data
}	t_philo;

/* Parsing Functions */
int		ft_parse(int argc, char **argv, t_config *config);
void	ft_usage(char *prog_name);
int		init_data(t_data *data, t_config *config);
void	cleanup_data(t_data *data);
long	get_time_ms(void);

#endif
