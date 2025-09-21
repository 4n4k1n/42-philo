/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:37:03 by apregitz          #+#    #+#             */
/*   Updated: 2025/09/21 15:44:18 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	print_status(t_philo *philo, char *status)
{
	bool	death_check;
	int		death_msg;

	death_msg = ft_strcmp(status, "died");
	if (death_msg != 0)
		pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->death_mutex);
	death_check = philo->dead;
	pthread_mutex_unlock(&philo->death_mutex);
	if (death_msg != 0 && death_check)
		return ((void)pthread_mutex_unlock(&philo->data->print_mutex));
	printf("%ld %d %s\n", get_time_in_ms() - philo->data->start_time,
		philo->id + 1, status);
	if (death_msg != 0)
		pthread_mutex_unlock(&philo->data->print_mutex);
}

int	ft_usleep(long time_in_ms, t_philo *philo)
{
	long	start_time;
	long	elapsed;
	bool	death_check;

	start_time = get_time_in_ms();
	while (1)
	{
		elapsed = get_time_in_ms() - start_time;
		pthread_mutex_lock(&philo->death_mutex);
		death_check = philo->dead;
		pthread_mutex_unlock(&philo->death_mutex);
		if (death_check)
			return (1);
		if (elapsed >= time_in_ms)
			break ;
		usleep(100);
	}
	return (0);
}
