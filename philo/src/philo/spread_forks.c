/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spread_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:04:08 by anakin            #+#    #+#             */
/*   Updated: 2025/07/19 09:52:27 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	spread_forks(t_data *data)
{
	int	i;
	t_philo	*head;

	head = data->philos;
	while (i < data->philo_amount)
	{
		head->right_fork = &head->next->left_fork;
		i++;
	}
	return (1);
}
