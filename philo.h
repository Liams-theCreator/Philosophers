/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:13:53 by imellali          #+#    #+#             */
/*   Updated: 2025/07/24 10:52:11 by imellali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_config
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				must_eat_flag;
}					t_config;

typedef struct s_data
{
	t_config		config;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	int				stop_sim;
	long			start_time_ms;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_ms;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}					t_philo;

/* Parsing Functions */
int					ft_parse(int argc, char **argv, t_config *config);
void				ft_usage(char *prog_name);
int					init_data(t_data *data, t_config *config);
void				cleanup_data(t_data *data);
long				get_time_ms(void);

#endif
