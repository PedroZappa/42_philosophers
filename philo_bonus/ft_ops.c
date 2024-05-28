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
	if (sem_wait(philo->d->sem_death) == 0)
	{
		philo->t_curr = ft_now(philo);
		if (sem_post(philo->d->sem_death) != 0)
			return (printf(RED"Error: sem_post failed\n"NC));
	}
	else
		return (printf(RED"Error: sem_wait failed\n"NC));
	ft_log(philo, EAT, ft_now(philo));
	usleep(ft_min(philo->d->t_meal, philo->d->t_death));
	if ((ft_drop_fork(philo) == 1) || (ft_drop_fork(philo) == 1))
		return (1);
	if ((philo->d->meal_max != NULL) \
		&& (++philo->n_meals == *philo->d->meal_max))
		sem_post(philo->d->sem_end);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (ft_log(philo, SLEEP, ft_now(philo)) == 1)
		return (1);
	usleep(philo->d->t_sleep);
	return (0);
}

int	ft_think(t_philo *philo)
{
	if (ft_log(philo, THINK, ft_now(philo)) == 1)
		return (1);
	usleep(philo->d->t_think);
	return (0);
}

int	ft_log(t_philo *p, int select, t_time t)
{
	if (sem_wait(p->d->sem_printf) == 0)
	{
		if (select == FORK)
			printf("%lld %d has taken a fork\n", \
					ft_dtime(p->d->t_start, t), p->idx);
		else if (select == EAT)
			printf("%lld %d is eating\n", ft_dtime(p->d->t_start, t), p->idx);
		else if (select == SLEEP)
			printf("%lld %d is sleeping\n", ft_dtime(p->d->t_start, t), p->idx);
		else if (select == THINK)
			printf("%lld %d is thinking\n", ft_dtime(p->d->t_start, t), p->idx);
		else if (select == DEAD)
			printf("%lld %d died\n", ft_dtime(p->d->t_start, t), p->idx);
		if (sem_post(p->d->sem_printf) != 0)
			return (ft_perror(RED"Error: sem_post failed"NC));
	}
	else
		return (ft_perror(RED"Error: sem_wait failed"NC));
	return (0);
}
