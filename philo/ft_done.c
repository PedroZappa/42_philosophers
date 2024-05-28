/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_done.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:26:36 by passunca          #+#    #+#             */
/*   Updated: 2024/05/28 16:33:30 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_isdead(t_philo *philo)
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

void ft_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex[MTX_DIED]);
	philo->data->died = TRUE;
	pthread_mutex_unlock(&philo->data->mutex[MTX_DIED]);
}

int ft_isdone(t_philo *philo)
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

void ft_done(t_data *data)
{
	pthread_mutex_lock(&data->mutex[MTX_DONE]);
	data->done = TRUE;
	pthread_mutex_unlock(&data->mutex[MTX_DONE]);
}

int	ft_are_done(t_philo *philo, t_data *data)
{
	int	i;
	int	done;
	int	meals_count;

	if (data->n_meals == -1)
		return (FALSE);
	i = -1;
	done = -1;
	while (++i < data->n_philos)
	{
		pthread_mutex_lock(&philo[i].data->mutex[MTX_MEALS]);
		meals_count = philo[i].meal_count;
		pthread_mutex_unlock(&philo[i].data->mutex[MTX_MEALS]);
		if (meals_count >= data->n_meals)
			if (++done == data->n_philos - 1)
				return (TRUE);
		usleep(50);
	}
	return (FALSE);
}

/// @brief			Lock and unlock mutex and print message to stdout
/// @param philo	Pointer to a t_philo struct
/// @param str		Message to print
void	ft_log(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->mutex[MTX_PRINTF]);
	if (!philo->data->done)
		printf("%3lld %3d %s\n", ft_dtime(philo->data->t_start), 
				philo->id, str);
	pthread_mutex_unlock(&philo->data->mutex[MTX_PRINTF]);
}
