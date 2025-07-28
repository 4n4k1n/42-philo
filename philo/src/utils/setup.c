/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:23:31 by anakin            #+#    #+#             */
/*   Updated: 2025/07/28 13:28:16 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

int	setup(t_data *data)
{
	if (setup_mutex(data) == 1)
		return (1);
	data->philos = create_philos(data->philo_amount);
	if (!data->philos)
		return (1);
	if (spread_forks(data) == 1)
		return (1);
	data->start_time = get_time();
	data->simulation_end = 0;
	if (create_threads(data) == 1)
		return (1);
	return (0);
}
