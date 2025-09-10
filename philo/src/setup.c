/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:40:49 by apregitz          #+#    #+#             */
/*   Updated: 2025/09/10 14:58:14 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(t_philo *philo, int id, t_data *data)
{
    philo->id = id;
    philo->meals_eaten = 0;
    philo->last_meal = 0;
    philo->data = data;
}

static int	create_philo_array(t_data *data)
{
    int i;

    data->philos = malloc(sizeof(t_philo) * data->params.num_philos);
    if (!data->philos)
        return (0);
    for (i = 0; i < data->params.num_philos; i++)
    {
        init_philo(&data->philos[i], i + 1, data);
        if (i > 0)
            data->philos[i - 1].right_fork = &data->philos[i].left_fork;
    }
    data->philos[data->params.num_philos - 1].right_fork = &data->philos[0].left_fork;
    return (1);
}

static int	create_mutexes(t_data *data)
{
    int i;

    for (i = 0; i < data->params.num_philos; i++)
    {
        if (pthread_mutex_init(&data->philos[i].left_fork, NULL) != 0)
            return (0);
    }
    return (1);
}

int create_threads(t_data *data)
{
    int i;

    for (i = 0; i < data->params.num_philos; i++)
    {
        if (pthread_create(&data->philos[i].thread, NULL, routine,  &data->philos[i]) != 0)
            return (0);
    }
    return (1);
}

int setup(t_data *data)
{
    if (!create_philo_array(data))
        return (1);
    data->start_time = get_time_in_ms();
    create_mutexes(data);
    create_threads(data);
    return (0);
}
