/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anakin <anakin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:41:04 by anakin            #+#    #+#             */
/*   Updated: 2025/07/28 13:15:41 by anakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int ac, char **av)
{
	t_data		data;

	if (parsing(ac, av, &data) == 1)
		return (1);
	setup(&data);
	if (create_monitors(&data) != 0)
		return (1);
	if (join_threads(&data) == 1)
		return (1);
	if (join_monitors(&data) != 0)
		return (1);
	desruct(&data);
	return (0);
}
