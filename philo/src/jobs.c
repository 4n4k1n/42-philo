/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:34:33 by apregitz          #+#    #+#             */
/*   Updated: 2025/09/21 15:41:52 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_philo *philo)
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
	last_meal = philo->data->params.time_to_die
		- (get_time_in_ms() - last_meal);
	if (philo->id % 2 == 0)
		ft_usleep(last_meal / 4, philo);
	else
		ft_usleep(last_meal / 2, philo);
	return (0);
}

static int	even_takes(t_philo *philo)
{
	bool	dead_check;

	if (philo->id % 2 == 0)
	{
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
	return (0);
}

static int	odd_takes(t_philo *philo)
{
	bool	dead_check;

	if (philo->id % 2 == 1)
	{
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
	return (0);
}

int	eating(t_philo *philo)
{
	int		exit_code;
	bool	death_check;

	if (&philo->left_fork == philo->right_fork)
		return (print_status(philo, "has taken a fork"), 1);
	exit_code = 0;
	pthread_mutex_lock(&philo->death_mutex);
	death_check = philo->dead;
	pthread_mutex_unlock(&philo->death_mutex);
	if (death_check || even_takes(philo) || odd_takes(philo))
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
		return (pthread_mutex_unlock(philo->right_fork),
			pthread_mutex_unlock(&philo->left_fork), exit_code);
	}
	return (pthread_mutex_unlock(&philo->left_fork),
		pthread_mutex_unlock(philo->right_fork), exit_code);
}
