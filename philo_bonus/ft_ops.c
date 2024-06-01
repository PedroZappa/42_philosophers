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
/// @param p		Reference to t_philo struct
/// @return			0 on success, 1 on failure
/// @details		- Grab sem_now to get the current time
/// 				- Log the event
/// 				- Drop the forks
/// @note			Used in ft_philosophize
int	ft_meal(t_philo *p)
{
	if (sem_wait(p->d->sem_now) == SUCCESS)
	{
		p->t_curr = ft_now(p);
		if (sem_post(p->d->sem_now) != SUCCESS)
			return (ft_perror(RED"Error: sem_post failed\n"NC));
	}
	else
		return (printf(RED"Error: sem_wait failed\n"NC));
	if (ft_log(p, EAT, ft_now(p)) == FAILURE)
		return (ft_perror("Error: ft_log failed (EAT)\n"));
	usleep(ft_min(p->d->t_meal, p->d->t_death));
	if (ft_drop_fork(p) || ft_drop_fork(p))
		return (ft_perror("Error: ft_drop_fork failed\n"));
	if ((p->d->meal_max != NULL) && (++p->n_meals == *p->d->meal_max))
		return (sem_post(p->d->sem_end), FAILURE);
	return (SUCCESS);
}

/// @brief			Sleeping
/// @param philo	Reference to t_philo struct
/// @return			0 on success, 1 on failure
/// @details		- Log the event
/// 				- Sleep
/// @note			Used in ft_philosophize
int	ft_sleep(t_philo *philo)
{
	if (ft_log(philo, SLEEP, ft_now(philo)) == FAILURE)
		return (ft_perror("Error: ft_log failed (SLEEP)\n"));
	usleep(philo->d->t_sleep);
	return (SUCCESS);
}

/// @brief			Thinking
/// @param philo	Reference to t_philo struct
/// @return			0 on success, 1 on failure
/// @details		- Log the event
/// 				- Think
/// @note			Used in ft_philosophize
int	ft_think(t_philo *philo)
{
	if (ft_log(philo, THINK, ft_now(philo)) == FAILURE)
		return (ft_perror("Error: ft_log failed (THINK)\n"));
	usleep(philo->d->t_think);
	return (SUCCESS);
}

/// @brief			Log an event
/// @param p		Reference to t_philo struct
/// @param select	Select the event to log
/// @param t		Reference to t_time struct
/// @return			0 on success, 1 on failure
/// @details		- Attempt to acquire sem_printf
/// 				- Log the event
/// 				- Release sem_printf
/// @note			Used all over the codebase
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
