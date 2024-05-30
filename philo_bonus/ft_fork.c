/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:19:15 by passunca          #+#    #+#             */
/*   Updated: 2024/05/26 22:15:20 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/// @brief			Take a fork
/// @param philo	Reference to t_philo struct
/// @return			0 on success, 1 on failure
/// @details		- If there are forks available:
///						- Take a fork
///					- Log the event
///	@note			Used in ft_philosophize
int	ft_take_fork(t_philo *philo)
{
	if (sem_wait(philo->d->sem_forks) == SUCCESS)
	{
		if (ft_log(philo, FORK, ft_now(philo)) == FAILURE)
			exit(ft_perror(RED"Error: ft_log failed (FORK)\n"NC));
	}
	else
		exit(ft_perror(RED"Error: sem_wait failed"NC));
	return (SUCCESS);
}

/// @brief			Drop a fork
/// @param philo	Reference to t_philo struct
/// @return			0 on success, 1 on failure
/// @details		- Post sem_forks (put fork back)
/// @note			Used in ft_meal
int	ft_drop_fork(t_philo *philo)
{
	if (sem_post(philo->d->sem_forks) != SUCCESS)
		exit(ft_perror(RED"Error: sem_post failed"NC));
	return (SUCCESS);
}
