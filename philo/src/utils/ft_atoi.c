/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:58:02 by anakin            #+#    #+#             */
/*   Updated: 2025/07/14 12:47:18 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(char *nptr)
{
	unsigned int	num;
	int				sign;

	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	sign = 0;
	if (*nptr == '+' || *nptr == '-')
		sign = 1 - 2 * (*(nptr++) == '-');
	num = 0;
	while (*nptr >= '0' && *nptr <= '9')
		num = (num * 10) + ((*nptr++ - '0') * sign);
	return (1);
}
