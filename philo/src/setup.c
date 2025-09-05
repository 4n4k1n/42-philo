/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:40:49 by apregitz          #+#    #+#             */
/*   Updated: 2025/09/05 15:02:44 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_philo(t_philo *philo, int id, t_data *data)
{
	philo->id = id;
	philo->meals_eaten = 0;
	philo->last_meal = 0;
	philo->data = data;
	philo->next = NULL;
}

int create_philo_linked_list(t_params *params, t_data *data)
{
	int i;
	t_philo *current;
	t_philo *previous;

	i = 0;
	previous = NULL;
	while (i < params->num_philos)
	{
		current = malloc(sizeof(t_philo));
		if (!current)
			return (0);
		init_philo(current, i + 1, data);
		if (previous)
		{
			previous->next = current;
			previous->right_fork = &current->left_fork;
		}
		else
			data->philos = current;
		previous = current;
		i++;
	}
	return (1);
}

int create_mutexes(t_data *data)
{
	t_philo *philo;
	int i;

	philo = data->philos;
	i = 0;
	while (i < data->params.num_philos)
	{
		if (pthread_mutex_init(&philo->left_fork, NULL) != 0)
			return (0);
		philo = philo->next;
		i++;
	}
	return (1);
}

int setup(t_params *params, t_data *data)
{
	if (!create_philo_linked_list(params, data))
		return (1);
	data->params = *params;
	data->dead = false;
	data->start_time = get_time_in_ms();
	return (0);
}
