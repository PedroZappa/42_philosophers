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

/// @brief			Eating
/// @param philo	Reference to t_philo struct
/// @return			0 on success, 1 on failure
/// @details		- Grab sem_death to get the current time
/// 				- Log the event
/// 				- Drop the forks
int	ft_meal(t_philo *philo)
{
	if (sem_wait(philo->d->sem_death) == SUCCESS)
	{
		philo->t_curr = ft_now(philo);
		if (sem_post(philo->d->sem_death) != SUCCESS)
			return (ft_perror(RED"Error: sem_post failed\n"NC));
	}
	else
		return (printf(RED"Error: sem_wait failed\n"NC));
	if (ft_log(philo, EAT, ft_now(philo)) == 1)
		return (ft_perror("Error: ft_log failed (EAT)\n"));
	usleep(ft_min(philo->d->t_meal, philo->d->t_death));
	if (ft_drop_fork(philo) || ft_drop_fork(philo))
		return (ft_perror("Error: ft_drop_fork failed\n"));
	if ((philo->d->meal_max != NULL) \
		&& (++philo->n_meals == *philo->d->meal_max))
		sem_post(philo->d->sem_end);
	return (SUCCESS);
}

int	ft_sleep(t_philo *philo)
{
	if (ft_log(philo, SLEEP, ft_now(philo)) == 1)
		return (ft_perror("Error: ft_log failed (SLEEP)\n"));
	usleep(philo->d->t_sleep);
	return (SUCCESS);
}

int	ft_think(t_philo *philo)
{
	if (ft_log(philo, THINK, ft_now(philo)) == 1)
		return (ft_perror("Error: ft_log failed (THINK)\n"));
	usleep(philo->d->t_think);
	return (SUCCESS);
}

int	ft_log(t_philo *p, int select, t_time t)
{
	if (sem_wait(p->d->sem_printf) == SUCCESS)
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
		if (sem_post(p->d->sem_printf) != SUCCESS)
			return (ft_perror(RED"Error: sem_post failed"NC));
	}
	else
		return (ft_perror(RED"Error: sem_wait failed"NC));
	return (SUCCESS);
}
