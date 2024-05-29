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

/// @brief			Get minimum value
/// @param a		First value
/// @param b		Second value
/// @return			Minimum value
/// @note			Used in ft_meal
int	ft_min(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}

/// @brief			Set t_start time
/// @param philo	Reference to t_philo struct
/// @var tmp		Reference to t_philo struct
/// @var i			To iterate through n_philos
/// @return			0 on success, 1 on failure
/// @details		Get the start time of the simulation
/// 				- Set it in every t_philo node
/// @note			Used in ft_children
int	ft_set_start_time(t_philo *philo)
{
	t_philo	*tmp;
	int		i;

	if (ft_gettime(&philo->d->t_start) == -1)
		return (FAILURE);
	tmp = philo;
	i = philo->d->n_philos;
	while (i--)
	{
		tmp->t_curr = philo->d->t_start;
		tmp = tmp->next;
	}
	return (SUCCESS);
}
