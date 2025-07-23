/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 15:46:39 by anakin            #+#    #+#             */
/*   Updated: 2025/07/15 15:49:40 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philo	*create_philos(size_t size)
{
	t_philo	*head;
	t_philo	*temp;
	size_t	i;

	if (size == 0)
		return (NULL);
	head = malloc(sizeof(t_philo));
	if (!head)
		return (NULL);
	memset(head, 0, sizeof(t_philo));
	temp = head;
	i = 1;
	while (i < size)
	{
		temp->next = malloc(sizeof(t_philo));
		if (!temp->next)
			return (free_philos(head, i), NULL);
		temp = temp->next;
		memset(temp, 0, sizeof(t_philo));
		i++;
	}
	return (head);
}
