/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imellali <imellali@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:13:53 by imellali          #+#    #+#             */
/*   Updated: 2025/08/05 13:46:22 by imellali         ###   ########.fr       */
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
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		meal_mutex;
	int					meals_eaten;
	long				last_meal_time;
	int					eating;
	struct s_simulation	*sim;
}						t_philo;

typedef struct s_simulation
{
	t_config			config;
	t_philo				*philosophers;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	int					dead_flag;
	pthread_mutex_t		meal_mutex;
	int					finished_eating;
	long				start_time;
	pthread_t			watcher_thread;
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

/* Time Management Function */
long					current_time(void);
void					ft_usleep(long ms);

/* Routine Functions */
int						start_simulation(t_simulation *sim);
int						run_simulation(t_simulation *sim);
void					*philosopher_routine(void *arg);
void					*single_philo_routine(void *arg);
void					*watcher_routine(void *arg);
int						join_threads(t_simulation *sim);

/* Status Functions */
void					print_status(t_philo *philo, char *status);
void					get_status(t_philo *philo, long *current,
							long *last_meal, int *eating);
int						check_death(t_philo *philo);
int						check_meal_completion(t_simulation *sim);
int						is_simulation_over(t_simulation *sim);
int						all_eat(t_simulation *sim);

/* Routine Management Functions */
int						take_forks(t_philo *philo);
void					drop_forks(t_philo *philo);
void					eat(t_philo *philo);
void					sleep_and_think(t_philo *philo);

#endif
