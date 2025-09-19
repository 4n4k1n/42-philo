/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:23:40 by apregitz          #+#    #+#             */
/*   Updated: 2025/09/19 15:04:24 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->params.num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]) != 0)
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
		data->philos[i].dead = true;
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
		while (i < data->params.num_philos)
		{
			pthread_mutex_lock(&data->philos[i].death_mutex);
			current_time = get_time_in_ms();
			// printf("%ld > %d\n", current_time - data->philos[i].last_meal, data->params.time_to_die);
			if ((current_time - data->philos[i].last_meal) > data->params.time_to_die)
			{
				// printf("fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
				set_all_philos_dead(data);
				pthread_mutex_unlock(&data->philos[i].death_mutex);
				print_status(&data->philos[i], "died");
				return ;
			}
			pthread_mutex_unlock(&data->philos[i].death_mutex);
			i++;
		}
		usleep(500);
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
	// printf("tt_eat: %d\ntt_sleep %d\ntt_die %d\n", data.params.time_to_eat, data.params.time_to_sleep, data.params.time_to_die);
	// return (0);
	setup(&data);
	join_threads(&data);
	monitor_philos(&data);
	cleanup_data(&data);
	return (0);
}
