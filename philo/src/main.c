/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:23:40 by apregitz          #+#    #+#             */
/*   Updated: 2025/09/12 14:42:45 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->params.num_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	set_all_philos_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->params.num_philos)
	{
		pthread_mutex_lock(&data->philos[i].death_mutex);
		data->philos[i].dead = true;
		pthread_mutex_unlock(&data->philos[i].death_mutex);
		i++;
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
			if ((current_time - data->philos[i].last_meal) > data->params.time_to_die)
			{
				set_all_philos_dead(data);
				pthread_mutex_unlock(&data->philos[i].death_mutex);
				print_status(&data->philos[i], "died");
				i = -1;
				return ;
			}
			pthread_mutex_unlock(&data->philos[i].death_mutex);
			i++;
		}
	}
}

void	cleanup_data(t_data *data)
{
	int	i;

	while (i < data->params.num_philos)
	{
		pthread_mutex_destroy(&data->philos[i].left_fork);
		pthread_mutex_destroy(&data->philos[i].death_mutex);
		pthread_mutex_destroy(&data->philos[i].print_mutex);
		i++;
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
