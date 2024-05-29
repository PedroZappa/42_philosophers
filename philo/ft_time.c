/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:38:36 by passunca          #+#    #+#             */
/*   Updated: 2024/05/29 19:59:22 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief		Get current time and convert it to milliseconds
/// @var t		To store current time
/// @details	- Get current time into t
/// 			- Convert t to milliseconds
/// @return		Current time in milliseconds
t_msec	ft_gettime(void)
{
	t_time	t;

	if (gettimeofday(&t, NULL) == -1)
		ft_perror(RED"Error: gettimeofday failed\n"NC);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

/// @brief			Get the time difference between two times
/// @param time	Starting time
/// @details		- Subtract the current time from the give time
/// @return			Time difference in milliseconds
t_msec	ft_dtime(t_msec time)
{
	return (ft_gettime() - time);
}

/// @brief		Lock and unlock mutex and print message to stdout
/// @param p	Pointer to a t_philo struct
/// @param str	Message to print
/// @details	- Lock printf mutex
/// 			- Print message if not dead or done
/// 			- Unlock printf mutex
/// @note		Used in ft_eating_start, ft_eating_done, 
///					ft_monitor & ft_start_philo
void	ft_log(t_philo *p, char *str)
{
	pthread_mutex_lock(&p->data->mutex[MTX_PRINTF]);
	if (((!ft_isdead(p)) && (!ft_isdone(p))) || (*str == 'd'))
		printf("%3lld %3d %s\n", (ft_dtime(p->data->t_start)), p->id, str);
	pthread_mutex_unlock(&p->data->mutex[MTX_PRINTF]);
}

/// @brief		Convert milliseconds to microseconds
/// @param msec	Number of milliseconds
/// @details	- Multiply the number of milliseconds by 1000
/// @return		Number of microseconds
void	ft_msleep(t_msec msec)
{
	usleep(msec * 1000);
}
