/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:41:04 by anakin            #+#    #+#             */
/*   Updated: 2025/07/28 13:15:41 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	monitor_thread;
	t_monitor	monitor;

	if (parsing(ac, av, &data) == 1)
		return (1);
	setup(&data);
	monitor.head = data.philos;
	monitor.data = &data;
	if (pthread_create(&monitor_thread, NULL, monitor_routine, &monitor) != 0)
		return (1);
	if (join_threads(&data) == 1)
		return (1);
	pthread_join(monitor_thread, NULL);
	desruct(&data);
	return (0);
}
