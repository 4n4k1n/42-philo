/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:32:58 by anakin            #+#    #+#             */
/*   Updated: 2025/07/18 10:39:27 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	join_threads(t_data *data)
{
	int		i;
	t_philo	*philo;

	philo = data->philos;
	i = 0;
	while (i < data->philo_amount)
	{
		if (pthread_join(philo->thread, NULL) != 0)
			return (1);
		i++;
		philo = philo->next;
	}
	return (0);
}
