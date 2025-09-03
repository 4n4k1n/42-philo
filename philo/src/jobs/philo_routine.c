/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 07:59:38 by anakin            #+#    #+#             */
/*   Updated: 2025/08/26 14:12:32 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = philo->data->start_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (philo->id % 2 == 0)
		ft_usleep(1000, philo);
	while (!get_philo_end(philo))
	{
		philo_eat(philo);
		if (get_philo_end(philo))
			break;
		philo_sleep(philo);
		if (get_philo_end(philo))
			break;
		philo_think(philo);
	}
	return (NULL);
}
