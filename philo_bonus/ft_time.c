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
/// @note		Used in ft_gettime_sem & ft_set_start_time
int	ft_gettime(t_time *t)
{
	if (gettimeofday(t, NULL) == -1)
		return (ft_perror(RED"Error: gettimeofday failed"NC));
	return (SUCCESS);
}

/// @brief		Get current time and convert it to milliseconds
/// @return		Current time in microseconds
/// @note		Used in ft_check
t_msec	ft_utime(t_time t)
{
	return (t.tv_sec * 1000000 + t.tv_usec);
}

/// @brief		Difference between two times in milliseconds
/// @param t0	Reference to t_time struct
/// @param t1	Reference to t_time struct
/// @return		Difference in milliseconds
/// @note		Used in ft_log
t_msec	ft_dtime(t_time t0, t_time t1)
{
	return ((ft_utime(t1) - ft_utime(t0)) / 1000);
}

/// @brief		Convert milliseconds to microseconds
/// @param t	Reference to t_msec variable
/// @details	- Multiply t by 1000
/// @note		Used in ft_init
void	ft_ms2us(void *t)
{
	*(t_msec *)t = (*(t_msec *)t * 1000);
}

/// @brief			Get t_0
/// @param philo	Reference to t_philo struct
/// @var now		To hold current time
/// @return			Current time
/// @details		- Set the memory in mow to 0
/// 				- Attempt to acquire sem_time
///						- Get t_0
/// @note			Used in ft_meal
t_time	ft_now(t_philo *philo)
{
	t_time	now;

	memset(&now, '\0', sizeof(t_time));
	if (sem_wait(philo->d->sem_time) == SUCCESS)
	{
		now = philo->t_0;
		if (sem_post(philo->d->sem_time) != SUCCESS)
			ft_perror(RED"Error: sem_post failed"NC);
	}
	return (now);
}
