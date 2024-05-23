/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:24:42 by passunca          #+#    #+#             */
/*   Updated: 2024/05/23 20:24:58 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/// @brief		Get current time and convert it to milliseconds
/// @return		Current time in milliseconds
t_msec	ft_gettime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

///
/// @brief			Wait for a certain amount of time
/// @param time		Time to wait in milliseconds
/// @param data		Pointer to t_data struct
/// @details		- Get current time in milliseconds
/// 				- Wait until time is reached or data->done is set
void	ft_philo_do(t_msec time, t_philo *philo)
{
	t_msec	t;

	t = ft_gettime();
	while (!philo->wait)
	{
		if ((ft_gettime() - t) >= time)
			break ;
		usleep(500);
	}
}
