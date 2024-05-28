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

int	ft_take_fork(t_philo *philo)
{
	if (sem_wait(philo->d->sem_forks) == 0)
	{
		if (ft_log(philo, FORK, ft_now(philo)) == 1)
			exit(ft_perror("Error: ft_log failed (FORK)\n"));
	}
	else
		exit(ft_perror(RED"Error: sem_wait failed"NC));
	return (0);
}

int	ft_drop_fork(t_philo *philo)
{
	if (sem_post(philo->d->sem_forks) != 0)
		exit(ft_perror(RED"Error: sem_post failed"NC));
	return (0);
}
