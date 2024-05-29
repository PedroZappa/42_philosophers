/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:36:54 by passunca          #+#    #+#             */
/*   Updated: 2024/05/29 19:50:55 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief			Destroy all mutexes
/// @param philo	Pointer to a t_philo struct
/// @var i			To iterate through mutexes/philos
/// @returns		void
/// @details		- Destroy fork mutexes
///					- Destroy data mutexes
/// @note			Used in ft_philosophize
void	ft_kill_mtx(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philos)
		pthread_mutex_destroy(&philo->fork[i++]);
	i = 0;
	while (i < MTX_NUM)
		pthread_mutex_destroy(&philo->data->mutex[i++]);
}
