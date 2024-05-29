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

int	ft_eating(t_philo *philo)
{
	if (ft_eating_start(philo) != SUCCESS)
		return (FAILURE);
	pthread_mutex_lock(&philo->data->mutex[MTX_MEALS]);
	philo->last_meal = ft_gettime();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->data->mutex[MTX_MEALS]);
	if (ft_isdone(philo) == SUCCESS)
	{
		ft_eating_done(philo);
		return (FAILURE);
	}
	ft_msleep(philo->data->t_meal);
	ft_eating_done(philo);
	return (SUCCESS);
}

static int	ft_eating_start(t_philo *p)
{
	pthread_mutex_lock(&p->fork[ft_min(p->l_fork, p->r_fork)]);
	ft_log(p, "has taken a fork\n");
	if (p->l_fork == p->r_fork)
	{
		pthread_mutex_unlock(&p->fork[ft_min(p->l_fork, p->r_fork)]);
		return (FAILURE);
	}
	pthread_mutex_lock(&p->fork[ft_max(p->l_fork, p->r_fork)]);
	ft_log(p, "has taken a fork\n");
	ft_log(p, "is eating\n");
	return (SUCCESS);
}

static int	ft_eating_done(t_philo *p)
{
	ft_log(p, "is sleeping\n");
	pthread_mutex_unlock(&p->fork[ft_max(p->l_fork, p->r_fork)]);
	pthread_mutex_unlock(&p->fork[ft_min(p->l_fork, p->r_fork)]);
	ft_msleep(p->data->t_sleep);
	return (SUCCESS);
}
