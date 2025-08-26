/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:58:21 by anakin            #+#    #+#             */
/*   Updated: 2025/08/26 13:23:13 by anakin           ###   ########.fr       */
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

# define PHILOS_PER_THRED 20

typedef enum e_state
{
	THINK,
	EAT,
	TRY_EAT,
	SLEEP,
	DEAD
}			t_state;

typedef struct s_philo	t_philo;
typedef struct s_monitor	t_monitor;

typedef struct s_monitor
{
	t_philo	*head;
	struct s_data	*data;
	int		philos_count;
}				t_monitor;

typedef struct s_data
{
	int				philo_amount;
	int				tt_eat;
	int				tt_die;
	int				tt_sleep;
	int				meals_to_eat;
	long long		start_time;
	int				simulation_end;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philos;
	int				monitor_count;
	pthread_t		*monitor_threads;
	t_monitor		*monitors;
	int				end;
}		t_data;

typedef struct	s_philo
{
	t_data			*data;
	pthread_t		thread;
	size_t			id;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	struct s_philo	*next;
	t_state			state;
	long long		last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	meal_mutex;
	int end;
}					t_philo;


// utils
int valid_input(int ac, char **av);
int	ft_atoi(char *nptr);
t_philo	*create_philos(size_t size);
void	free_philos(t_philo *head, size_t size);
int	parsing(int ac, char **av, t_data *data);
int	spread_forks(t_data *data);
int	create_threads(t_data *data);
int	join_threads(t_data *data);

// timing and logging
long long	get_time(void);
void		print_status(t_philo *philo, char *status);
int			check_death(t_philo *philo);

// monitoring
void		*monitor_routine(void *arg);
int			create_monitors(t_data *data);
int			join_monitors(t_data *data);

// philosopher jobs
void		*philo_routine(void *arg);
int			take_forks(t_philo *philo);
void		return_forks(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);

void		ft_usleep(long ms, t_philo *philo);
void	desruct(t_data *data);
int 	setup_mutex(t_data *data);
int		setup(t_data *data);

#endif