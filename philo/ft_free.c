/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:36:54 by passunca          #+#    #+#             */
/*   Updated: 2024/05/21 16:15:16 by passunca         ###   ########.fr       */
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
		printf("i = %d\n", i);
		printf("Philosopher %d freed\n", i + 1);
		printf("%p\n", (philo + i));
		pthread_mutex_destroy(&data->mutex_fork[i]);
	}
	// free(philo);
	pthread_mutex_destroy(&data->mutex_printf);
	free(*philo);
	free(data);
}
