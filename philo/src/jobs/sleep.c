/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:00:00 by anakin            #+#    #+#             */
/*   Updated: 2025/07/23 13:43:25 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	philo_sleep(t_philo *philo)
{
	if (philo->data->simulation_end)
		return ;
	philo->state = SLEEP;
	print_status(philo, "is sleeping");
	usleep(philo->data->tt_sleep);
}