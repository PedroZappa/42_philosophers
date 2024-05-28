/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_done.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:26:36 by passunca          #+#    #+#             */
/*   Updated: 2024/05/28 16:31:38 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_check_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex[MTX_DIED]);
	if (philo->data->died)
	{
		pthread_mutex_unlock(&philo->data->mutex[MTX_DIED]);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->data->mutex[MTX_DIED]);
	return (FALSE);
}

int ft_check_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex[MTX_DONE]);
	if (philo->data->done)
	{
		pthread_mutex_unlock(&philo->data->mutex[MTX_DONE]);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->data->mutex[MTX_DONE]);
	return (FALSE);
}

void ft_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex[MTX_DIED]);
	philo->data->died = TRUE;
	pthread_mutex_unlock(&philo->data->mutex[MTX_DIED]);
}

void ft_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex[MTX_DONE]);
	philo->data->done = TRUE;
	pthread_mutex_unlock(&philo->data->mutex[MTX_DONE]);
}


