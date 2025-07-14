/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:14:39 by anakin            #+#    #+#             */
/*   Updated: 2025/07/14 15:38:01 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	parsing(int ac, char **av, t_data *data)
{
	if (ac < 5 || ac > 6)
		return (1);
	if (valid_input(ac, av) == 1)
		return (1);
	memset(data, 0, sizeof(*data));
	data->philo_amount = ft_atoi(av[1]);
	data->tt_die = ft_atoi(av[2]);
	data->tt_eat = ft_atoi(av[3]);
	data->tt_sleep = ft_atoi(av[4]);
	if (data->meals_to_eat < 0 || data->tt_die < 0 \
		|| data->tt_eat < 0 || data->tt_sleep < 0)
		return (1);
	if (ac == 6)
	{
		data->meals_to_eat = ft_atoi(av[5]);
		if (data->meals_to_eat < 0)
			return (1);
	}
	else
		data->meals_to_eat = -1;
	return (0);
}
