/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:58:21 by anakin            #+#    #+#             */
/*   Updated: 2025/07/14 12:53:00 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <string.h>


typedef struct s_data
{
	int	philo_amount;
	int	tt_eat;
	int	tt_die;
	int	tt_sleep;
	int	meals_to_eat;
}		t_data;

typedef struct	s_philo
{
	t_data			*data;
	pthread_t		thread;
	size_t			id;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	struct s_philo	*next;
}					t_philo;


// utils
int valid_input(int ac, char **av);
int	ft_atoi(char *nptr);


#endif