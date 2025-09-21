/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:34:33 by apregitz          #+#    #+#             */
/*   Updated: 2025/09/21 11:01:59 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_usleep(long time_in_ms, t_philo *philo)
{
	long	start_time;
	long	elapsed;
	bool	death_check;

	start_time = get_time_in_ms();
	while (1)
	{
		elapsed = get_time_in_ms() - start_time;
		pthread_mutex_lock(&philo->death_mutex);
		death_check = philo->dead;
		pthread_mutex_unlock(&philo->death_mutex);
		if (death_check)
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
	long	last_meal;

	pthread_mutex_lock(&philo->death_mutex);
	death_check = philo->dead;
	pthread_mutex_unlock(&philo->death_mutex);
	if (death_check)
		return (1);
	print_status(philo, "is thinking");
	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->id % 2 == 0)
		ft_usleep((philo->data->params.time_to_die - (get_time_in_ms() - last_meal)) / 4, philo);
	else
		ft_usleep((philo->data->params.time_to_die - (get_time_in_ms() - last_meal)) / 2, philo);
	return (0);
}

static int	even_takes(t_philo *philo)
{
	bool	dead_check;

	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->death_mutex);
	dead_check = philo->dead;
	pthread_mutex_unlock(&philo->death_mutex);
	if (dead_check)
		return (pthread_mutex_unlock(&philo->left_fork), 1);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->death_mutex);
	dead_check = philo->dead;
	pthread_mutex_unlock(&philo->death_mutex);
	if (dead_check)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
		return (1);
	}
	print_status(philo, "has taken a fork");
}

static int	odd_takes(t_philo *philo)
{
	bool	dead_check;
	
	usleep(500);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->death_mutex);
	dead_check = philo->dead;
	pthread_mutex_unlock(&philo->death_mutex);
	if (dead_check)
		return (pthread_mutex_unlock(philo->right_fork), 1);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->death_mutex);
	dead_check = philo->dead;
	pthread_mutex_unlock(&philo->death_mutex);
	if (dead_check)
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_status(philo, "has taken a fork");
}

static int	take_forks(t_philo *philo)
{
	bool	dead_check;

	if (philo->id % 2 == 0)
	{
		if (even_takes(philo) == 1)
			return (1);
	}
	else
	{
		if (odd_takes(philo) == 1)
			reutnr (1);
	}
	return (0);
}

static int	eating(t_philo *philo)
{
	int		exit_code;
	bool	death_check;

	exit_code = 0;
	pthread_mutex_lock(&philo->death_mutex);
	death_check = philo->dead;
	pthread_mutex_unlock(&philo->death_mutex);
	if (death_check)
		return (1);
	if (take_forks(philo))
		return (1);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, "is eating");
	if (ft_usleep(philo->data->params.time_to_eat, philo))
		exit_code = 1;
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
	t_philo *philo;
	
	philo = (t_philo *)arg;
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
