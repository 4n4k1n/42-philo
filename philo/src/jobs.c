/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:34:33 by apregitz          #+#    #+#             */
/*   Updated: 2025/09/10 15:01:59 by apregitz         ###   ########.fr       */
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
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->params.time_to_sleep, philo);
	return (0);
}

static int	thinking(t_philo *philo)
{
	if (philo->dead)
		return (1);
	print_status(philo, "is thinking");
	ft_usleep(philo->data->params.time_to_sleep, philo);
	return (0);
}

static int	eating(t_philo *philo)
{
	if (philo->dead)
		return (1);
	pthread_mutex_lock(&philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	philo->last_meal = get_time_in_ms();
	print_status(philo, "is eating");
	ft_usleep(philo->data->params.time_to_eat, philo);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	philo->last_meal = get_time_in_ms();
	while (!philo->dead && (philo->data->params.num_meals == -1 || philo->meals_eaten < philo->data->params.num_meals))
	{
		if (eating(philo) || sleeping(philo) || thinking(philo))
			break ; 
	}
	return (NULL);
}	
