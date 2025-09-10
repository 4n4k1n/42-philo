/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:32:59 by apregitz          #+#    #+#             */
/*   Updated: 2025/09/10 14:52:32 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
#include <limits.h>
#include <stdbool.h>

typedef struct s_data	t_data;

typedef struct s_params
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
}					t_params;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
	bool			dead;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
}					t_philo;

typedef struct s_data
{
	t_params		params;
	t_philo			*philos;
	long			start_time;
}					t_data;

int		parse_args(int argc, char **argv, t_params *params);
void	print_status(t_philo *philo, char *status);
int		get_time_in_ms(void);
int		initialize_data(t_data *data);
void	cleanup_data(t_data *data);
void	*routine(void *arg);
void	monitor_philos(t_data *data);
int		setup(t_data *data);

#endif