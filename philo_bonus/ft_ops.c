/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:04:16 by passunca          #+#    #+#             */
/*   Updated: 2024/05/23 21:13:09 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->sem_death);
		if (philo->next_meal < ft_gettime())
		{
			ft_philo_log(DIED, philo);
			sem_post(philo->data->sem_wait);
			break ;
		}
		sem_post(philo->data->sem_death);
		sem_wait(philo->data->sem_death);
		if ((philo->data->meal_counter != -1) \
			&& (philo->data->curr_meal >= philo->data->max_meals))
		{
			ft_philo_log(DONE, philo);
			sem_post(philo->data->sem_wait);
			break ;
		}
		sem_post(philo->data->sem_death);
	}
	return (NULL);
}
