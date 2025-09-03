/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:00:00 by anakin            #+#    #+#             */
/*   Updated: 2025/09/03 10:00:01 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

int	get_philo_end(t_philo *philo)
{
	int	end_value;

	pthread_mutex_lock(&philo->end_mutex);
	end_value = philo->end;
	pthread_mutex_unlock(&philo->end_mutex);
	return (end_value);
}

void	set_philo_end(t_philo *philo, int value)
{
	pthread_mutex_lock(&philo->end_mutex);
	philo->end = value;
	pthread_mutex_unlock(&philo->end_mutex);
}

int	get_data_end(t_data *data)
{
	int	end_value;

	pthread_mutex_lock(&data->end_mutex);
	end_value = data->end;
	pthread_mutex_unlock(&data->end_mutex);
	return (end_value);
}

void	set_data_end(t_data *data, int value)
{
	pthread_mutex_lock(&data->end_mutex);
	data->end = value;
	pthread_mutex_unlock(&data->end_mutex);
}