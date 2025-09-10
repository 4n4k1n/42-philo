/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:23:40 by apregitz          #+#    #+#             */
/*   Updated: 2025/09/10 15:05:19 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int join_threads(t_data *data)
{
	int	i;

	for (i = 0; i < data->params.num_philos; i++)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (0);
	}
	return (1);
}

void	set_all_philos_dead(t_data *data)
{
	int	i;

	for (i = 0; i < data->params.num_philos; i++)
	{
		pthread_mutex_lock(&data->philos[i].death_mutex);
		data->philos[i].dead = true;
		pthread_mutex_unlock(&data->philos[i].death_mutex);
	}
}

void monitor_philos(t_data *data)
{
	int		i;
	long	current_time;

	while (true)
	{
		i = 0;
		while (i < data->params.num_philos && !data->philos[i].dead)
		{
			current_time = get_time_in_ms();
			pthread_mutex_lock(&data->philos[i].death_mutex);
			if (!data->philos[i].dead && (current_time - data->philos[i].last_meal) > data->params.time_to_die)
			{
				set_all_philos_dead(data);
				print_status(&data->philos[i], "died");
				break;
			}
			pthread_mutex_unlock(&data->philos[i].death_mutex);
			i++;
		}
	}
}

void	cleanup_data(t_data *data)
{
	int	i;

	for (i = 0; i < data->params.num_philos; i++)
	{
		pthread_mutex_destroy(&data->philos[i].left_fork);
		pthread_mutex_destroy(&data->philos[i].death_mutex);
		pthread_mutex_destroy(&data->philos[i].print_mutex);
	}
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data		data;
	if (!parse_args(argc, argv, &data.params))
		return (printf("Error: Invalid arguments\n"), 1);
	setup(&data);
	join_threads(&data);
	monitor_philos(&data);
	cleanup_data(&data);
	return (0);
}
