/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:04:16 by passunca          #+#    #+#             */
/*   Updated: 2024/05/23 20:37:49 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	ft_grab_fork(t_philo *philo)
{
	sem_wait(philo->data->forks);
	ft_philo_log(FORK, philo);
	sem_wait(philo->data->forks);
	ft_philo_log(FORK, philo);
}

void	ft_have_meal(t_philo *philo)
{
	ft_philo_log(EATING, philo);
	if (philo->data->meal_counter != -1)
		philo->data->curr_meal++;
	usleep(philo->data->t_meal * 1000);
	philo->meal_start = ft_gettime();
	philo->next_meal = philo->meal_start + philo->data->t_death;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	ft_sleep(t_philo *philo)
{
	ft_philo_log(SLEEPING, philo);
	usleep(philo->data->t_sleep * 1000);
}
