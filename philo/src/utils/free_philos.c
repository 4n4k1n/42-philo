/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:09:49 by anakin            #+#    #+#             */
/*   Updated: 2025/07/14 18:10:04 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_philos(t_philo *head, size_t size)
{
	size_t	i;
	t_philo	*temp;

	i = 0;
	while (i < size)
	{
		temp = head->next;
		free(head);
		i++;
	}
}
