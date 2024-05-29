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

void	ft_kill_mtx(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philos)
		pthread_mutex_destroy(&philo->data->mutex[i++]);
	i = 0;
	while (i < MTX_NUM)
		pthread_mutex_destroy(&philo->data->mutex[i++]);
}
