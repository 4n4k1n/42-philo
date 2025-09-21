/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 14:18:52 by anakin            #+#    #+#             */
/*   Updated: 2025/09/20 17:15:27 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int check_for_enough_meals(t_data *data, int i)
{
	int			meals_eaten;
	static int	check = -1;

	if (data->params.num_meals == -1)	
		return (0);
	pthread_mutex_lock(&data->philos[i].meal_mutex);
	meals_eaten = data->philos[i].meals_eaten;
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
	if (meals_eaten < data->params.num_meals)
	{
		check = i;
		return (0);
	}
	else if (check == i && meals_eaten >= data->params.num_meals)
		return (1);
	return (0);
}

void monitor_philos(t_data *data)
{
	int		i;
	long	current_time;
	long	last_meal;

	while (true)
	{
		i = 0;
		while (i < data->params.num_philos)
		{
			current_time = get_time_in_ms();
			pthread_mutex_lock(&data->philos[i].meal_mutex);
			last_meal = data->philos[i].last_meal;
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			if ((current_time - last_meal) > data->params.time_to_die)
			{ 
				pthread_mutex_lock(&data->print_mutex);
				set_all_philos_dead(data);
				print_status(&data->philos[i], "died");
				pthread_mutex_unlock(&data->print_mutex);
				return ;
			}
			if (check_for_enough_meals(data, i))
				return ((void)set_all_philos_dead(data));
			i++; } usleep(500);
	}
}

void	cleanup_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->params.num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->params.num_philos)
	{
		pthread_mutex_destroy(&data->philos[i].left_fork);
		pthread_mutex_destroy(&data->philos[i].death_mutex);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!parse_args(argc, argv, &data.params))
		return (1);
	if (setup(&data))
		return (printf("setup error\n"), 1);
	monitor_philos(&data);
	cleanup_data(&data);
	return (0);
}
