/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
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
