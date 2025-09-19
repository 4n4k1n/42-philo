/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:34:33 by apregitz          #+#    #+#             */
/*   Updated: 2025/09/19 23:34:31 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_usleep(long time_in_ms, t_philo *philo)
{
	long start_time;
	long elapsed;
	// printf("				%d	%ld\n", philo->id, time_in_ms);

	start_time = get_time_in_ms();
	while (1)
	{
		elapsed = get_time_in_ms() - start_time;
		if (philo->dead)
			return (1);
		if (elapsed >= time_in_ms)
			break ;
		usleep(100);
	}
	return (0);
}

static int	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
	if (ft_usleep(philo->data->params.time_to_sleep, philo))
		return (1);
	return (0);
}

int	thinking(t_philo *philo)
{
	bool	death_check;

	pthread_mutex_lock(&philo->death_mutex);
	death_check = philo->dead;
	pthread_mutex_unlock(&philo->death_mutex);
	if (death_check)
		return (1);
	print_status(philo, "is thinking");
	return (0);
}

static void	take_forks(t_philo *philo)
{
	bool dead_check;

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->death_mutex);
		dead_check = philo->dead;
		pthread_mutex_unlock(&philo->death_mutex);
		if (dead_check)
			return ((void)pthread_mutex_unlock(&philo->left_fork));
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		usleep(500);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->death_mutex);
		dead_check = philo->dead;
		pthread_mutex_unlock(&philo->death_mutex);
		if (dead_check)
			return ((void)pthread_mutex_unlock(philo->right_fork));
		pthread_mutex_lock(&philo->left_fork);
		print_status(philo, "has taken a fork");
	}
}

static int	eating(t_philo *philo)
{
	int	exit_code;

	exit_code = 0;
	if (philo->dead)
		return (1);
	take_forks(philo);
	philo->last_meal = get_time_in_ms();
	print_status(philo, "is eating");
	if (ft_usleep(philo->data->params.time_to_eat, philo))
		exit_code = 1;
	philo->meals_eaten++;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
		return (exit_code);
	}
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (exit_code);
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	philo->last_meal = get_time_in_ms();
	while (1)
	{
		if (eating(philo))
			break ; 
		if (sleeping(philo))
			break ;
		if (thinking(philo))
			break;
	}
	return (NULL);
}
