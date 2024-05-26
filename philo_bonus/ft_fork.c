/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:19:15 by passunca          #+#    #+#             */
/*   Updated: 2024/05/26 20:33:17 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_take_fork(t_philo *philo)
{
	if (sem_wait(philo->sem_forks) == 0)
	{
		if (ft_log(philo, FORK, ft_now(philo)) == 1)
			return (1);
	}
	else
	{
		printf(RED"Error: sem_wait failed"NC);
		return (1);
	}
	return (0);
}

int	ft_drop_fork(t_philo *philo)
{
	if (sem_post(philo->sem_forks) != 0)
	{
		printf(RED"Error: sem_post failed"NC);
		return (1);
	}
	return (0);
}
