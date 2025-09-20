/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:37:03 by apregitz          #+#    #+#             */
/*   Updated: 2025/09/20 04:25:51 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_time_in_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;
	int			id;
	bool		death_check;

	pthread_mutex_lock(&philo->death_mutex);
	death_check = philo->dead;
	pthread_mutex_unlock(&philo->death_mutex);
	if (death_check && ft_strcmp(status, "died") != 0)
		return;
	id = philo->id;
	timestamp = get_time_in_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d %s\n", timestamp, id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
