/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:41:04 by anakin            #+#    #+#             */
/*   Updated: 2025/07/18 10:32:03 by anakin           ###   ########.fr       */
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
	if (pthread_mutex_init(&data.print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data.death_mutex, NULL) != 0)
		return (1);
	data.philos = create_philos(data.philo_amount);
	if (!data.philos)
		return (1);
	if (spread_forks(&data) == 1)
		return (1);
	data.start_time = get_time();
	data.simulation_end = 0;
	monitor.head = data.philos;
	monitor.data = &data;
	if (pthread_create(&monitor_thread, NULL, monitor_routine, &monitor) != 0)
		return (1);
	if (create_threads(&data) == 1)
		return (1);
	if (join_threads(&data) == 1)
		return (1);
	pthread_join(monitor_thread, NULL);
	pthread_mutex_destroy(&data.print_mutex);
	pthread_mutex_destroy(&data.death_mutex);
	free_philos(data.philos, data.philo_amount);
	return (0);
}
