/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:48:18 by anakin            #+#    #+#             */
/*   Updated: 2025/07/16 21:58:23 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	create_threads(t_data *data)
{
	int	i;
	t_philo	*philo;

	philo = data->philos;
	i = 0;
	while (i < data->philo_amount)
	{
		pthread_create(philo->thread, NULL, NULL, philo);
		i++;
		philo = philo->next;
	}
}
