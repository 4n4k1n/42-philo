/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:05:18 by apregitz          #+#    #+#             */
/*   Updated: 2025/09/21 16:06:13 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_int(char *str, int *out)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		sign = 1 - 2 * (*(str++) == '-');
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		if (num * sign > INT_MAX || num * sign < INT_MIN)
			return (1);
		str++;
	}
	if (*str != '\0')
		return (1);
	*out = (int)(num * sign);
	return (0);
}

int	parse_args(int argc, char **argv, t_params *params)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (parse_int(argv[1], &params->num_philos) == 1
		|| params->num_philos <= 0)
		return (1);
	if (parse_int(argv[2], &params->time_to_die) == 1
		|| params->time_to_die < 0)
		return (1);
	if (parse_int(argv[3], &params->time_to_eat) == 1
		|| params->time_to_eat < 0)
		return (1);
	if (parse_int(argv[4], &params->time_to_sleep) == 1
		|| params->time_to_sleep < 1)
		return (1);
	if (argc == 6)
	{
		if (parse_int(argv[5], &params->num_meals) == 1
			|| params->num_meals <= 0)
			return (1);
	}
	else
		params->num_meals = -1;
	return (0);
}
