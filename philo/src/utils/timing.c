/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:00:00 by anakin            #+#    #+#             */
/*   Updated: 2025/07/23 13:48:51 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	if (philo->data->simulation_end)
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->simulation_end)
	{
		timestamp = get_time() - philo->data->start_time;
		printf("%lld %zu %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	check_death(t_philo *philo)
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
