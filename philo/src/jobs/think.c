/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:00:00 by anakin            #+#    #+#             */
/*   Updated: 2025/08/26 13:24:26 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	philo_think(t_philo *philo)
{
	long	think_time;

	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->simulation_end)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	philo->state = THINK;
	print_status(philo, "is thinking");
	think_time = (philo->data->tt_die - (philo->data->tt_eat
				+ philo->data->tt_sleep)) / 4;
	if (think_time > 100)
		think_time = 100;
	else if (think_time < 0)
		think_time = 0;
	if (think_time > 0)
		ft_usleep(think_time * 1000, philo);
}
