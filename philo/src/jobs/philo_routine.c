/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 07:59:38 by anakin            #+#    #+#             */
/*   Updated: 2025/07/23 13:46:16 by anakin           ###   ########.fr       */
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
		usleep(1000);
	while (!philo->data->simulation_end)
	{
		if (check_death(philo))
			break ;
		philo_eat(philo);
		if (philo->data->meals_to_eat > 0 && 
			philo->meals_eaten >= philo->data->meals_to_eat)
			break ;
		if (philo->data->simulation_end)
			break ;
		philo_sleep(philo);
		if (philo->data->simulation_end)
			break ;
		philo_think(philo);
	}
	return (NULL);
}
