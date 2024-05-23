/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:11:19 by passunca          #+#    #+#             */
/*   Updated: 2024/05/23 20:38:19 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/// @brief			Free all the allocated memory
/// @param data		Philosophical data to be freed
/// @param philo	Philosophers array to be freed
void	ft_free(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
		kill(philo[i++].pid, SIGKILL);
	sem_close(data->death);
	sem_close(data->stop);
	sem_close(data->msg);
	sem_close(data->forks);
	free(philo);
}
