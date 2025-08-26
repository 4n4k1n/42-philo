/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uusleep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:38:43 by anakin            #+#    #+#             */
/*   Updated: 2025/07/28 10:38:45 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	ft_usleep(long ms, t_philo *philo)
{
	long	start;
	long	elapsed;

	start = get_time();
	while (1)
	{
		elapsed = get_time() - start;
		if (elapsed >= ms / 1000)
			break ;
		if (philo->end)
			break;
		usleep(100);
	}
}
