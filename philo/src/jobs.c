/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:34:33 by apregitz          #+#    #+#             */
/*   Updated: 2025/09/09 15:20:19 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_usleep(long time_in_ms, t_philo *philo)
{
	long start_time = get_time_in_ms();
	long elapsed;

	while (1)
	{
		elapsed = get_time_in_ms() - start_time;
		if (elapsed >= time_in_ms || philo->dead)
			break ;
		usleep(100);
	}
	return (0);
}

static int	sleeping(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_time_in_ms() - philo->data->start_time, philo->id);
	ft_usleep(philo->data->params.time_to_sleep, philo);
	return (0);
}

static int	thinking(t_philo *philo)
{
	if (philo->data->dead)
		return (1);
	printf("%ld %d is thinking\n", get_time_in_ms() - philo->data->start_time, philo->id);
	ft_usleep(philo->data->params.time_to_sleep, philo);
	return (0);
}

static int	eating(t_philo *philo)
{
	long start_time;

	if (philo->data->dead)
		return (1);
	pthread_mutex_lock(&philo->left_fork);
	printf("%ld %d has taken a fork\n", get_time_in_ms() - philo->data->start_time, philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("%ld %d has taken a fork\n", get_time_in_ms() - philo->data->start_time, philo->id);
	philo->last_meal = get_time_in_ms();
	printf("%ld %d is eating\n", philo->last_meal - philo->data->start_time, philo->id);
	start_time = get_time_in_ms();
	ft_usleep(philo->data->params.time_to_eat, philo);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	philo->last_meal = get_time_in_ms();
	while (!philo->data->dead && (philo->data->params.num_meals == -1 || philo->meals_eaten < philo->data->params.num_meals))
	{
		if (eating(philo))
			break ;
		if (sleeping(philo))
			break ;
		if (thinking(philo))
			break ;
	}
	return (0);
}	
