/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:04:16 by passunca          #+#    #+#             */
/*   Updated: 2024/05/26 22:16:50 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_meal(t_philo *philo)
{
	if (sem_wait(philo->data->sem_death) == 0)
	{
		philo->t_curr = ft_now(philo);
		if (sem_post(philo->data->sem_death) != 0)
		{
			printf(RED"Error: sem_post failed"NC);
			return (1);
		}
	}
	else
	{
		printf(RED"Error: sem_wait failed"NC);
		return (1);
	}
	ft_log(philo, EAT, ft_now(philo));
	usleep(ft_min(philo->data->t_meal, philo->data->t_death));
	if ((ft_drop_fork(philo) == 1) || (ft_drop_fork(philo) == 1))
		return (1);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (ft_log(philo, SLEEP, ft_now(philo)) == 1)
		return (1);
	usleep(philo->data->t_sleep);
	return (0);
}

int	ft_think(t_philo *philo)
{
	if (ft_log(philo, THINK, ft_now(philo)) == 1)
		return (1);
	usleep(philo->data->t_think);
	return (0);
}

int	ft_log(t_philo *p, int select, t_time t)
{
	if (sem_wait(p->data->sem_printf) == 0)
	{
		if (select == FORK)
			printf("%lld %d has taken a fork\n", \
					ft_dtime(p->data->t_start, t), p->idx);
		else if (select == EAT)
			printf("%lld %d is eating\n", ft_dtime(p->data->t_start, t), p->idx);
		else if (select == SLEEP)
			printf("%lld %d is sleeping\n", ft_dtime(p->data->t_start, t), p->idx);
		else if (select == THINK)
			printf("%lld %d is thinking\n", ft_dtime(p->data->t_start, t), p->idx);
		else if (select == DEAD)
			printf("%lld %d died\n", ft_dtime(p->data->t_start, t), p->idx);
		if (sem_post(p->data->sem_printf) != 0)
		{
			printf(RED"Error: sem_post failed"NC);
			return (1);
		}
	}
	else
	{
		printf(RED"Error: sem_wait failed"NC);
		return (1);
	}
	return (0);
}
