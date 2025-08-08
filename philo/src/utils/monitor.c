/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:00:00 by anakin            #+#    #+#             */
/*   Updated: 2025/07/28 10:38:13 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

static int	check_philosopher_death(t_philo *philo)
{
	long long	current_time;
	long long	time_since_last_meal;

	pthread_mutex_lock(&philo->meal_mutex);
	current_time = get_time();
	time_since_last_meal = current_time - philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (time_since_last_meal > philo->data->tt_die)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (!philo->data->simulation_end)
		{
			philo->data->simulation_end = 1;
			pthread_mutex_lock(&philo->data->print_mutex);
			current_time = get_time() - philo->data->start_time;
			printf("%lld %zu died\n", current_time, philo->id);
			pthread_mutex_unlock(&philo->data->print_mutex);
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	return (0);
}

static int	check_all_ate_enough(t_data *data)
{
	t_philo	*current;
	int		i;
	int		all_ate_enough;

	if (data->meals_to_eat <= 0)
		return (0);
	current = data->philos;
	i = 0;
	all_ate_enough = 1;
	while (i < data->philo_amount)
	{
		pthread_mutex_lock(&current->meal_mutex);
		if (current->meals_eaten < data->meals_to_eat)
			all_ate_enough = 0;
		pthread_mutex_unlock(&current->meal_mutex);
		if (!all_ate_enough)
			break;
		current = current->next;
		i++;
	}
	if (all_ate_enough)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->simulation_end = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_monitor	*monitor;
	t_philo	*current;
	int		i;

	monitor = (t_monitor *)arg;
	while (!monitor->data->simulation_end)
	{
		current = monitor->head;
		i = 0;
		while (i < monitor->philos_count && !monitor->data->simulation_end)
		{
			if (check_philosopher_death(current))
				return (NULL);
			current = current->next;
			i++;
		}
		if (check_all_ate_enough(monitor->data))
			return (NULL);
		ft_usleep(1000);
	}
	return (NULL);
}

int	create_monitors(t_data *data)
{
	t_philo		*current;
	int			i;
	int			j;
	int			philos_per_monitor;

	data->monitor_count = (data->philo_amount + PHILOS_PER_THRED - 1) / PHILOS_PER_THRED;
	data->monitor_threads = malloc(sizeof(pthread_t) * data->monitor_count);
	data->monitors = malloc(sizeof(t_monitor) * data->monitor_count);
	if (!data->monitor_threads || !data->monitors)
	{
		if (data->monitor_threads)
			free(data->monitor_threads);
		if (data->monitors)
			free(data->monitors);
		return (1);
	}
	current = data->philos;
	i = 0;
	while (i < data->monitor_count)
	{
		data->monitors[i].data = data;
		data->monitors[i].head = current;
		philos_per_monitor = PHILOS_PER_THRED;
		if (i == data->monitor_count - 1)
			philos_per_monitor = data->philo_amount - (i * PHILOS_PER_THRED);
		data->monitors[i].philos_count = philos_per_monitor;
		if (pthread_create(&data->monitor_threads[i], NULL, monitor_routine, &data->monitors[i]) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_join(data->monitor_threads[i], NULL);
			}
			free(data->monitors);
			free(data->monitor_threads);
			data->monitor_threads = NULL;
			data->monitors = NULL;
			return (1);
		}
		j = 0;
		while (j < philos_per_monitor && current)
		{
			current = current->next;
			j++;
		}
		i++;
	}
	return (0);
}

int	join_monitors(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->monitor_count)
	{
		if (pthread_join(data->monitor_threads[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
