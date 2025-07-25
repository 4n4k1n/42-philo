/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:58:21 by anakin            #+#    #+#             */
/*   Updated: 2025/07/19 09:50:06 by anakin           ###   ########.fr       */
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

typedef enum e_state
{
	THINK,
	EAT,
	TRY_EAT,
	SLEEP,
	DEAD
}			t_state;

typedef struct s_philo	t_philo;

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
}					t_philo;


// utils
int valid_input(int ac, char **av);
int	ft_atoi(char *nptr);
t_philo	*create_philos(int size);
void	free_philos(t_philo *head, size_t size);
int	parsing(int ac, char **av, t_data *data);
int	spread_forks(t_data *data);

// timing and logging
long long	get_time(void);
void		print_status(t_philo *philo, char *status);
int			check_death(t_philo *philo);

// philosopher jobs
void		*philo_routine(void *arg);
int			take_forks(t_philo *philo);
void		return_forks(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);

#endif