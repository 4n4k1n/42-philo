/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 09:00:00 by anakin            #+#    #+#             */
/*   Updated: 2025/07/23 13:44:44 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	return_forks(t_philo *philo)
{
	if (philo->data->philo_amount == 1)
		return ;
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
