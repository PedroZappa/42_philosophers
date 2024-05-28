/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:48:16 by passunca          #+#    #+#             */
/*   Updated: 2024/05/26 21:46:09 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/// @brief			Get current time through semaphore
/// @param d	Reference to t_philo struct
/// @return			0 on success, 1 on failure
int	ft_set_time_sem(t_philo *philo)
{
	if (sem_wait(philo->d->sem_time) == 0)
	{
		if (ft_gettime(&philo->t_now) == -1)
			return (1);
		if (sem_post(philo->d->sem_time) != 0)
		{
			printf(RED"Error: sem_wait failed"NC);
			return (1);
		}
	}
	return (0);
}

void	ft_sem_post_end(t_philo *philo)
{
	int	i;

	i = philo->d->n_philos;
	while (i--)
	{
		if (sem_post(philo->d->sem_end) != 0)
		{
			printf(RED"Error: sem_post failed"NC);
			exit(1);
		}
	}
}
