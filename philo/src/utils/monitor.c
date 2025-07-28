/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:00:00 by anakin            #+#    #+#             */
/*   Updated: 2025/07/28 10:38:13 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

static int	check_philosopher_death(t_philo *philo)
{
	long long	current_time;
	long long	time_since_last_meal;

	pthread_mutex_lock(&philo->meal_mutex);
	current_time = get_time();
	time_since_last_meal = current_time - philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (time_since_last_meal > philo->data->tt_die)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (!philo->data->simulation_end)
		{
			print_status(philo, "died");
			philo->data->simulation_end = 1;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	return (0);
}

static int	check_all_ate_enough(t_data *data)
{
	t_philo	*current;
	int		i;
	int		all_ate_enough;

	if (data->meals_to_eat <= 0)
		return (0);
	current = data->philos;
	i = 0;
	all_ate_enough = 1;
	while (i < data->philo_amount)
	{
		pthread_mutex_lock(&current->meal_mutex);
		if (current->meals_eaten < data->meals_to_eat)
			all_ate_enough = 0;
		pthread_mutex_unlock(&current->meal_mutex);
		if (!all_ate_enough)
			break;
		current = current->next;
		i++;
	}
	if (all_ate_enough)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->simulation_end = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_monitor	*monitor;
	t_philo	*current;
	int		i;

	monitor = (t_monitor *)arg;
	while (!monitor->data->simulation_end)
	{
		current = monitor->head;
		i = 0;
		while (i < monitor->data->philo_amount && !monitor->data->simulation_end)
		{
			if (check_philosopher_death(current))
				return (NULL);
			current = current->next;
			i++;
		}
		if (check_all_ate_enough(monitor->data))
			return (NULL);
		ft_usleep(1000);
	}
	return (NULL);
}
