/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:00:00 by anakin            #+#    #+#             */
/*   Updated: 2025/07/23 13:24:13 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	philo_think(t_philo *philo)
{
	long	think_time;

	if (philo->data->simulation_end)
		return ;
	philo->state = THINK;
	print_status(philo, "is thinking");
	think_time = (philo->data->tt_die - (philo->data->tt_eat
				+ philo->data->tt_sleep)) / 4;
	if (think_time > 100)
		think_time = 100;
	else if (think_time < 0)
		think_time = 0;
	if (think_time > 0)
		ft_usleep(think_time * 1000);
}
