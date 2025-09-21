/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:37:03 by apregitz          #+#    #+#             */
/*   Updated: 2025/09/20 17:13:02 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_time_in_ms(void)
{
	struct timeval	tv;

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
	bool		death_check;

	pthread_mutex_lock(&philo->death_mutex);
	death_check = philo->dead;
	pthread_mutex_unlock(&philo->death_mutex);
	if (death_check)
		return;
	timestamp = get_time_in_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
