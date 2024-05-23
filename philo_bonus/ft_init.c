/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:00:25 by passunca          #+#    #+#             */
/*   Updated: 2024/05/23 17:01:56 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*ft_init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo) * data->n_philos);
	data->death = NULL;
	data->stop = NULL;
	data->msg = NULL;
	data->forks = NULL;
	while (++i < data->n_philos)
	{
		philo[i].idx = i;
		philo[i].died = NO;
		philo[i].data = data;
		philo[i].pid = -1;
		if (data->meal_counter == -1)
			philo[i].meal_counter = -1;
		else
			philo[i].meal_counter = data->meal_counter;
	}
	return (philo);
}

void	ft_init_semaphores(t_data *data)
{
	(void)data;
}

void	ft_fork_process(t_data *data, t_philo *philo)
{
	(void)data;
	(void)philo;
}
