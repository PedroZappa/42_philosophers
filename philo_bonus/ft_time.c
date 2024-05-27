/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:24:42 by passunca          #+#    #+#             */
/*   Updated: 2024/05/26 22:17:10 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/// @brief		Get current time into a struct timeval
/// @param t	Reference to t_time struct
/// @return		0 on success, 1 on failure
int	ft_gettime(t_time *t)
{
	if (gettimeofday(t, NULL) == -1)
	{
		printf(RED"Error: gettimeofday failed"NC);
		return (1);
	}
	return (0);
}

/// @brief		Get current time and convert it to milliseconds
/// @return		Current time in microseconds
t_msec	ft_utime(t_time t)
{
	return (t.tv_sec * 1000000 + t.tv_usec);
}

/// @brief		Difference between two times in milliseconds
/// @param t0	Reference to t_time struct
/// @param t1	Reference to t_time struct
/// @return		Difference in milliseconds
t_msec	ft_dtime(t_time t0, t_time t1)
{
	return ((ft_utime(t1) - ft_utime(t0)) / 1000);
}

/// @brief		Convert milliseconds to microseconds
/// @param t	Reference to t_msec variable
void	ft_ms2us(void *t)
{
	*(t_msec *)t = (*(t_msec *)t * 1000);
}

t_time	ft_now(t_philo *philo)
{
	struct timeval	now;

	ft_bzero(&now, sizeof(t_time));
	if (sem_wait(philo->data->sem_time) == 0)
	{
		now = philo->t_curr;
		if (sem_post(philo->data->sem_time) != 0)
			perror(RED"Error: sem_post failed"NC);
	}
	return (now);
}

/// @brief			Set t_start time
/// @param philo	Reference to t_philo struct
/// @return			0 on success, 1 on failure
int	ft_set_start_time(t_philo *philo)
{
	t_philo	*tmp;
	int		i;

	if (ft_gettime(&philo->data->t_start) == -1)
		return (1);
	tmp = philo;
	i = philo->data->n_philos;
	while (i--)
	{
		tmp->t_curr = philo->data->t_start;
		tmp = tmp->next;
	}
	return (0);
}
