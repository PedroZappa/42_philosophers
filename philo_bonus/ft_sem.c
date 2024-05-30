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
/// @param philo	Reference to t_philo struct
/// @return			0 on success, 1 on failure
/// @details		- Attempt to acquire sem_time
/// 					- Get current time
/// 					- Release sem_time
/// @note			Used in ft_philosophize
int	ft_gettime_sem(t_philo *philo)
{
	if (sem_wait(philo->d->sem_time) == SUCCESS)
	{
		if (ft_gettime(&philo->t_0) == -1)
			return (FAILURE);
		if (sem_post(philo->d->sem_time) != SUCCESS)
			return (ft_perror(RED"Error: sem_wait failed"NC));
	}
	return (SUCCESS);
}

/// @brief			End simulation semaphore
/// @param philo	Reference to t_philo struct
/// @var i			To iterate through n_philos
/// @details		- Post sem_end
/// @note			Used in ft_philosophize
void	ft_end_sem(t_philo *philo)
{
	int	i;

	i = philo->d->n_philos;
	while (i--)
		if (sem_post(philo->d->sem_end) != SUCCESS)
			exit(ft_perror(RED"Error: sem_post failed"NC));
}
