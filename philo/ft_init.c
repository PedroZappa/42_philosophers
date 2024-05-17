/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:33:44 by passunca          #+#    #+#             */
/*   Updated: 2024/05/17 18:27:09 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

static int	ft_init_data(t_data **data, int argc, char **argv);
static int	ft_init_fork(t_data *data);
static void	ft_init_philo(t_philo *philo, int i, t_data *data, t_mutex *forks);

/// @brief			Initialize all simulation data
/// @details		- Initialize mutexes
///					- Initialize forks
///					- Alloc & Initialize philos
/// @param philo	Pointer to array of philos
/// @param argc		Number of arguments
/// @param argv		Argument vector
/// @return			0 on success, -1 on failure
int	ft_init(t_philo **philo, int argc, char **argv)
{
	t_data	*data;
	t_philo	*new_philo;
	int		i;

	if (ft_init_data(&data, argc, argv) == -1)
		return (-1);
	if (pthread_mutex_init(&data->mutex_printf, NULL))
		return (ft_perror(RED"Error: Printf Mutex init\n"NC));
	if (ft_init_fork(data) == -1)
		return (-1);
	new_philo = malloc(sizeof(t_philo) * data->n_philos);
	if (!new_philo)
		return (ft_perror(RED"Error: failed to alloc philos\n"NC));
	i = -1;
	while (++i < data->n_philos)
		ft_init_philo((new_philo + i), i, data, data->mutex_fork);
	*philo = new_philo;
	return (0);
}

static int	ft_init_data(t_data **data, int argc, char **argv)
{
	(void)data;
	(void)argc;
	(void)argv;
	return (0);
}

static int	ft_init_fork(t_data *data)
{
	(void)data;
	return (0);
}

static void	ft_init_philo(t_philo *philo, int i, t_data *data, t_mutex *forks)
{
	(void)philo;
	(void)i;
	(void)data;
	(void)forks;
}
