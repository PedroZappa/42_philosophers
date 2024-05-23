/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:04:16 by passunca          #+#    #+#             */
/*   Updated: 2024/05/23 20:04:56 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_philo_log(int id, t_philo *philo);

/// @brief		Get current time and convert it to milliseconds
/// @return		Current time in milliseconds
t_msec	ft_gettime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	*ft_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->death);
		if (philo->next_meal < ft_gettime())
		{
			ft_philo_log(DIED, philo);
			sem_post(philo->data->stop);
			break ;
		}
		sem_post(philo->data->death);
		sem_wait(philo->data->death);
		if ((philo->data->meal_counter != -1) \
			&& (philo->data->curr_meal >= philo->data->max_meals))
		{
			ft_philo_log(DONE, philo);
			sem_post(philo->data->stop);
			break ;
		}
		sem_post(philo->data->death);
	}
	return (NULL);
}

void	ft_philo_log(int id, t_philo *philo)
{
	t_msec	time;

	time = (ft_gettime() - philo->data->t_start);
	sem_wait(philo->data->msg);
	if (id == FORK)
		printf("%lld\t%d has taken a fork\n", time, (philo->idx + 1));
	else if (id == EATING)
		printf("%lld\t%d is eating\n", time, (philo->idx + 1));
	else if (id == SLEEPING)
		printf("%lld\t%d is sleeping\n", time, (philo->idx + 1));
	else if (id == THINKING)
		printf("%lld\t%d is thinking\n", time, (philo->idx + 1));
	else if (id == DIED)
		printf("%lld\t%d died\n", time, (philo->idx + 1));
	else if (id == DONE)
		printf("Done Philosophizing.\n");
	if (id != DIED)
		sem_post(philo->data->msg);
}
