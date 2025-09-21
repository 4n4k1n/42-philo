/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:37:17 by apregitz          #+#    #+#             */
/*   Updated: 2025/09/21 15:24:22 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	init_philo(t_philo *philo, int id, t_data *data)
// {
// 	philo->id = id;
// 	philo->meals_eaten = 0;
// 	philo->last_meal = get_time_in_ms();
// 	philo->data = data;
// 	philo->dead = false;
// }

static int	create_philo_array(t_data *data)
{
	int	i;
	int	max;

	max = data->params.num_philos - 1;
	data->philos = malloc(sizeof(t_philo) * data->params.num_philos);
	if (!data->philos)
		return (0);
	i = 0;
	while (i < data->params.num_philos)
	{
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = get_time_in_ms();
		data->philos[i].data = data;
		data->philos[i].dead = false;
		if (i > 0)
			data->philos[i - 1].right_fork = &data->philos[i].left_fork;
		i++;
	}
	data->philos[max].right_fork = &data->philos[0].left_fork;
	return (1);
}

static void	mutex_creation_fail_destory(t_data *data, int i, int last_mutex)
{
	if (last_mutex == 3)
	{
		pthread_mutex_destroy(&data->philos[i].left_fork);
		pthread_mutex_destroy(&data->philos[i].death_mutex);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
	}
	else if (last_mutex == 2)
	{
		pthread_mutex_destroy(&data->philos[i].left_fork);
		pthread_mutex_destroy(&data->philos[i].death_mutex);
	}
	else if (last_mutex == 1)
		pthread_mutex_destroy(&data->philos[i].left_fork);
	while (i >= 0)
	{
		i--;
		pthread_mutex_destroy(&data->philos[i].left_fork);
		pthread_mutex_destroy(&data->philos[i].death_mutex);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
	}
}

static int	create_mutexes(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (printf("Mutex init error: print_mutex"), 1);
	i = 0;
	while (++i < data->params.num_philos)
	{
		if (pthread_mutex_init(&data->philos[i].left_fork, NULL) != 0)
		{
			return (printf("Mutex init error: left_fork"),
				mutex_creation_fail_destory(data, i, 1), 1);
		}
		if (pthread_mutex_init(&data->philos[i].death_mutex, NULL) != 0)
		{
			return (printf("Mutex init error: death_mutex"),
				mutex_creation_fail_destory(data, i, 2), 1);
		}
		if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
		{
			return (printf("Mutex init error: meal_mutex"),
				mutex_creation_fail_destory(data, i, 3), 1);
		}
		i++;
	}
	return (0);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->params.num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				routine, &data->philos[i]) != 0)
		{
			while (i-- >= 0)
				pthread_join(data->philos[i].thread, NULL);
			return (1);
		}
		i++;
	}
	return (0);
}

int	setup(t_data *data)
{
	if (!create_philo_array(data))
		return (1);
	data->start_time = get_time_in_ms();
	if (create_mutexes(data) == 1)
		return (free(data->philos), 1);
	if (create_threads(data) == 1)
	{
		mutex_creation_fail_destory(data, data->params.num_philos + 1, 0);
		free(data->philos);
		return (1);
	}
	return (0);
}
