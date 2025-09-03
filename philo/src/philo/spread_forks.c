/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spread_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:04:08 by anakin            #+#    #+#             */
/*   Updated: 2025/07/23 21:27:22 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	spread_forks(t_data *data)
{
	int		i;
	t_philo	*head;
	t_philo	*current;

	head = data->philos;
	current = head;
	i = 0;
	while (i < data->philo_amount)
	{
		current->id = i + 1;
		current->data = data;
		if (pthread_mutex_init(&current->left_fork, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&current->meal_mutex, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&current->end_mutex, NULL) != 0)
			return (1);
		if (i == data->philo_amount - 1)
			current->next = head;
		current = current->next;
		i++;
	}
	current = head;
	i = 0;
	while (i < data->philo_amount)
	{
		current->right_fork = &current->next->left_fork;
		current = current->next;
		i++;
	}
	return (0);
}
