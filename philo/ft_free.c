/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:36:54 by passunca          #+#    #+#             */
/*   Updated: 2024/05/21 15:43:30 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_philo **philo)
{
	t_data	*data;
	int i;

	i = -1;
	data = (*philo)->data;
	while (++i < data->n_philos)
	{
		printf("Philosopher %d freed\n", i + 1);
		free((philo + i));
	}
	i = 0;
	while (i < data->n_forks)
	{
		printf("Fork %d freed\n", i + 1);
		pthread_mutex_destroy(data->mutex_fork + i);
		++i;
	}
	pthread_mutex_destroy(&data->mutex_printf);
	free(data);
}
