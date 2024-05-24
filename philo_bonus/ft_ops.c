/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:04:16 by passunca          #+#    #+#             */
/*   Updated: 2024/05/23 21:13:09 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

///
/// @brief			Lock and unlock mutex and print message to stdout
/// @param philo	Pointer to a t_philo struct
/// @param str		Message to print
void	ft_philo_log(t_philo *philo, char *str)
{
	sem_wait(philo->sem_printf);
	if (philo->wait == NO)
		printf("%lld %d %s\n", \
				(ft_gettime() - philo->t_start), philo->idx, str);
	sem_post(philo->sem_printf);
}
