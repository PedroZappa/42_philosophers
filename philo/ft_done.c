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

/// @brief			Check if a philo dead
/// @param philo	Pointer to a t_philo struct
/// @return			TRUE if dead, FALSE if not
/// @note			Used in ft_start_philo & ft_log
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

/// @brief			Check if the simulation is done
/// @param philo	Pointer to a t_philo struct
/// @return			TRUE if done, FALSE if not
/// @note			Used in ft_eating & ft_log
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

/// @brief			Set a philo dead
/// @param data		Pointer to a t_data struct
/// @note			Used in ft_monitor
void ft_died(t_data *data)
{
	pthread_mutex_lock(&data->mutex[MTX_DIED]);
	data->died = TRUE;
	pthread_mutex_unlock(&data->mutex[MTX_DIED]);
}

/// @brief			Check if n_meals have been eaten
/// @param philo	Pointer to a t_philo struct
/// @param data		Pointer to a t_data struct
/// @return			TRUE if done, FALSE if not
/// @note			Used in ft_monitor
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
		pthread_mutex_lock(&philo->data->mutex[MTX_MEALS]);
		meals_count = philo[i].meal_count;
		pthread_mutex_unlock(&philo->data->mutex[MTX_MEALS]);
		if (meals_count >= data->n_meals)
			if (++done == (data->n_philos - 1))
				return (TRUE);
		usleep(50);
	}
	return (FALSE);
}

/// @brief			Set the simulation as done
/// @param data		Pointer to a t_data struct
/// @note			Used in ft_monitor
void ft_done(t_data *data)
{
	pthread_mutex_lock(&data->mutex[MTX_DONE]);
	data->done = TRUE;
	pthread_mutex_unlock(&data->mutex[MTX_DONE]);
}
