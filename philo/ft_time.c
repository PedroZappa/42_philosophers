/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:38:36 by passunca          #+#    #+#             */
/*   Updated: 2024/05/22 11:06:43 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief		Get current time and convert it to milliseconds
/// @return		Current time in milliseconds
t_msec	ft_gettime(void)
{
	t_time	t;

	if (gettimeofday(&t, NULL) == -1)
		ft_perror(RED"Error: gettimeofday failed\n"NC);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

t_msec	ft_dtime(t_msec start)
{
	return (ft_gettime() - start);
}

/// @brief			Lock and unlock mutex and print message to stdout
/// @param philo	Pointer to a t_philo struct
/// @param str		Message to print
void	ft_log(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->mutex[MTX_PRINTF]);
	if (!philo->data->done)
		printf("%3lld %3d %s\n", \
				(ft_dtime(philo->data->t_start)), philo->id, str);
	pthread_mutex_unlock(&philo->data->mutex[MTX_PRINTF]);
}
