/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:40:49 by apregitz          #+#    #+#             */
/*   Updated: 2025/09/09 13:41:36 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_philo(t_philo *philo, int id, t_data *data)
{
    philo->id = id;
    philo->meals_eaten = 0;
    philo->last_meal = 0;
    philo->data = data;
}

int create_philo_array(t_params *params, t_data *data)
{
    int i;

    data->philos = malloc(sizeof(t_philo) * params->num_philos);
    if (!data->philos)
        return (0);
    for (i = 0; i < params->num_philos; i++)
    {
        init_philo(&data->philos[i], i + 1, data);
        if (i > 0)
            data->philos[i - 1].right_fork = &data->philos[i].left_fork;
    }
    data->philos[params->num_philos - 1].right_fork = &data->philos[0].left_fork;
    return (1);
}

int create_mutexes(t_data *data)
{
    int i;

    for (i = 0; i < data->params.num_philos; i++)
    {
        if (pthread_mutex_init(&data->philos[i].left_fork, NULL) != 0)
            return (0);
    }
    return (1);
}

int setup(t_params *params, t_data *data)
{
    if (!create_philo_array(params, data))
        return (1);
    data->params = *params;
    data->dead = false;
    data->start_time = get_time_in_ms();
    return (0);
}
