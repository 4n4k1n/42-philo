/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:05:18 by apregitz          #+#    #+#             */
/*   Updated: 2025/09/09 13:35:28 by apregitz         ###   ########.fr       */
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
			return (0);
		str++;
	}
	if (*str != '\0')
		return (0);
	*out = (int)(num * sign);
	return (1);
}

int	parse_args(int argc, char **argv, t_params *params)
{
	if (argc != 5 && argc != 6)
		return (0);
	if (!parse_int(argv[1], &params->num_philos) || params->num_philos <= 0)
		return (0);
	if (!parse_int(argv[2], &params->time_to_die) || params->time_to_die < 0)
		return (0);
	if (!parse_int(argv[3], &params->time_to_eat) || params->time_to_eat < 0)
		return (0);
	if (!parse_int(argv[4], &params->time_to_sleep) || params->time_to_sleep < 0)
		return (0);
	if (argc == 6)
	{
		if (!parse_int(argv[5], &params->num_meals) || params->num_meals <= 0)
			return (0);
	}
	else
		params->num_meals = -1;
	return (1);
}
