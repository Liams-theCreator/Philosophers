/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:13:53 by imellali          #+#    #+#             */
/*   Updated: 2025/07/27 15:01:11 by imellali         ###   ########.fr       */
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
	int					num_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
	int					must_eat_flag;
}						t_config;

typedef struct s_philo
{
	int					id; // thread id
	long				last_meal_time; // timestamp 
	int					eating; // threads activity status
	pthread_t			thread; // philosopher thread
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		meal_mutex; // private resource (meals eaten)
	int					meals_eaten; // meals eaten counter
	struct s_simulation	*sim; // shared resources 
}						t_philo;

typedef struct s_simulation
{
	t_config			config; // rules
	t_philo				*philosophers; // philos threads
	pthread_mutex_t		*forks; // forks
	pthread_mutex_t		print_mutex; // printing status
	pthread_mutex_t		death_mutex; // death status lock
	int					dead_flag; // death status
	pthread_mutex_t		meal_mutex; // shared resource
	int					finished_eating; // end of simulation
	long				start_time; // simulation start time
	pthread_t			watcher_thread; // watcher of all threads
}						t_simulation;

/* Parsing Functions */
int						ft_parse(int argc, char **argv, t_config *config);
void					ft_man(void);


/* Utility Functions */
size_t					ft_strlen(const char *s);
int						ft_atoi(const char *str);
int						is_pos(const char *s);


/* Initialization Functions */
int						init_mutexes(t_simulation *sim);
int						init_philosophers(t_simulation *sim);
int						init_simulation(t_simulation *sim);

/* Cleanup Functions */
void					cleanup_mutex(t_simulation *sim);
void					cleanup_simulation(t_simulation *sim);

#endif
