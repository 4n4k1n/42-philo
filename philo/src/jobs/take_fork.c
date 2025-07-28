/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:00:00 by anakin            #+#    #+#             */
/*   Updated: 2025/07/23 13:40:38 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

static int single_philo_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->left_fork);
	return (0);
}

static int	odd_philo_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	if (philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->left_fork);
		return (0);
	}
	print_status(philo, "has taken a fork");
	
	pthread_mutex_lock(philo->right_fork);
	if (philo->data->simulation_end)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
		return (0);
	}
	print_status(philo, "has taken a fork");
	return (1);
}

static int	even_philo_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (philo->data->simulation_end)
	{
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	print_status(philo, "has taken a fork");
	
	pthread_mutex_lock(&philo->left_fork);
	if (philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	print_status(philo, "has taken a fork");
	return (1);
}

int	take_forks(t_philo *philo)
{
	if (philo->data->simulation_end)
		return (0);
	if (philo->data->philo_amount == 1)
		return (single_philo_take_fork(philo));
	if (philo->id % 2 == 0)
	{
		if (!even_philo_take_fork(philo))
			return (0);
	}
	else
	{
		if (!odd_philo_take_fork(philo))
			return (0);
	}
	return (1);
}
