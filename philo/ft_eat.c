/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:10:33 by passunca          #+#    #+#             */
/*   Updated: 2024/05/28 16:25:21 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_eating_start(t_philo *p);
static int	ft_eating_done(t_philo *p);

/// @brief			Eating logic
/// @param p		Pointer to a t_philo struct
/// @return			SUCCESS if eating, FAILURE if not
/// @note			Used in ft_start_philo
int	ft_eating(t_philo *p)
{
	if (ft_eating_start(p) != SUCCESS)
		return (FAILURE);
	pthread_mutex_lock(&p->data->mutex[MTX_MEALS]);
	p->last_meal = ft_gettime();
	p->meal_count++;
	pthread_mutex_unlock(&p->data->mutex[MTX_MEALS]);
	if (ft_isdone(p))
	{
		ft_eating_done(p);
		return (FAILURE);
	}
	ft_msleep(p->data->t_meal);
	ft_eating_done(p);
	return (SUCCESS);
}

/// @brief			Grabbing forks and eating
/// @param p		Pointer to a t_philo struct
/// @return			SUCCESS if eating, FAILURE if not
/// @note			Used in ft_eating
static int	ft_eating_start(t_philo *p)
{
	pthread_mutex_lock(&p->fork[ft_min(p->l_fork, p->r_fork)]);
	ft_log(p, "has taken a fork");
	if (p->l_fork == p->r_fork)
	{
		pthread_mutex_unlock(&p->fork[ft_min(p->l_fork, p->r_fork)]);
		return (FAILURE);
	}
	pthread_mutex_lock(&p->fork[ft_max(p->l_fork, p->r_fork)]);
	ft_log(p, "has taken a fork");
	ft_log(p, "is eating");
	return (SUCCESS);
}

/// @brief			Release forks
/// @param p		Pointer to a t_philo struct
/// @return			SUCCESS if eating, FAILURE if not
/// @note			Used in ft_eating
static int	ft_eating_done(t_philo *p)
{
	ft_log(p, "is sleeping");
	pthread_mutex_unlock(&p->fork[ft_max(p->l_fork, p->r_fork)]);
	pthread_mutex_unlock(&p->fork[ft_min(p->l_fork, p->r_fork)]);
	ft_msleep(p->data->t_sleep);
	return (SUCCESS);
}
