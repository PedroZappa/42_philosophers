/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:20:12 by passunca          #+#    #+#             */
/*   Updated: 2024/05/26 17:20:30 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_min(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}

/// @brief 		Initializes a zeroed array
/// @param s	Pointer to the array
/// @param n	Number of bytes to set to zero
void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = '\0';
}

/// @brief			Set t_start time
/// @param philo	Reference to t_philo struct
/// @return			0 on success, 1 on failure
int	ft_set_start_time(t_philo *philo)
{
	t_philo	*tmp;
	int		i;

	if (ft_gettime(&philo->d->t_start) == -1)
		return (1);
	tmp = philo;
	i = philo->d->n_philos;
	while (i--)
	{
		tmp->t_curr = philo->d->t_start;
		tmp = tmp->next;
	}
	return (0);
}
