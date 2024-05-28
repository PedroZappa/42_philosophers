/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:36:54 by passunca          #+#    #+#             */
/*   Updated: 2024/05/22 11:10:11 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief			Free all simulation data
/// @param philo	Pointer to array of philos
// void	ft_free(t_philo **philo)
// {
// 	t_data	*data;
// 	int		i;
//
// 	usleep(3500);
// 	i = -1;
// 	data = (*philo)->data;
// 	while (++i < data->n_philos)
// 		pthread_mutex_destroy(data->mutex_fork + i);
// 	pthread_mutex_destroy(&data->mutex_printf);
// 	free(*philo);
// 	free(data->mutex_fork);
// 	free(data);
// }
