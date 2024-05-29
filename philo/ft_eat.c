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

// int	ft_eating(t_philo *philo)
// {
// 	if (ft_eating_start(philo) != SUCCESS)
// 		return (FAILURE);
// 	pthread_mutex_lock(&philo->data->mutex[MTX_MEALS]);
// 	philo->last_meal = ft_gettime();
// 	philo->meal_count++;
// 	pthread_mutex_unlock(&philo->data->mutex[MTX_MEALS]);
// 	if (ft_isdone(philo) == SUCCESS)
// 	{
// 		ft_eating_done(philo);
// 		return (FAILURE);
// 	}
// 	ft_msleep(philo->data->t_meal);
// 	// usleep(philo->data->t_meal);
// 	ft_eating_done(philo);
// 	return (SUCCESS);
// }
int	ft_eating(t_philo *self)
{
	if (ft_eating_start(self) != SUCCESS)
		return (FAILURE);
	pthread_mutex_lock(&self->data->mutex[MTX_MEALS]);
	self->last_meal = ft_gettime();
	self->meal_count++;
	pthread_mutex_unlock(&self->data->mutex[MTX_MEALS]);
	if (ft_isdone(self))
	{
		ft_eating_done(self);
		return (FAILURE);
	}
	ft_msleep(self->data->t_meal);
	ft_eating_done(self);
	return (SUCCESS);
}

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
// static int	ft_eating_start(t_philo *self)
// {
// 	pthread_mutex_lock(&self->fork[ft_min (self->l_fork, self->r_fork)]);
// 	ft_log(self, "has taken a fork");
// 	if (self->l_fork == self->r_fork)
// 	{
// 		pthread_mutex_unlock(&self->fork[ft_min (self->l_fork, self->r_fork)]);
// 		return (FAILURE);
// 	}
// 	pthread_mutex_lock(&self->fork[ft_max (self->l_fork, self->r_fork)]);
// 	ft_log(self, "has taken a fork");
// 	ft_log(self, "is eating");
// 	return (SUCCESS);
// }

// static int	ft_eating_done(t_philo *p)
// {
// 	ft_log(p, "is sleeping");
// 	pthread_mutex_unlock(&p->fork[ft_max(p->l_fork, p->r_fork)]);
// 	pthread_mutex_unlock(&p->fork[ft_min(p->l_fork, p->r_fork)]);
// 	ft_msleep(p->data->t_sleep);
// 	// usleep(p->data->t_sleep);
// 	return (SUCCESS);
// }
static int	ft_eating_done(t_philo *self)
{
	ft_log(self, "is sleeping");
	pthread_mutex_unlock(&self->fork[ft_max (self->l_fork, self->r_fork)]);
	pthread_mutex_unlock(&self->fork[ft_min (self->l_fork, self->r_fork)]);
	ft_msleep(self->data->t_sleep);
	return (SUCCESS);
}
