/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:17:35 by passunca          #+#    #+#             */
/*   Updated: 2024/05/17 21:11:42 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_philosophize(t_philo *philos);
static void	*ft_start_philo(void *args);
static void	*ft_monitor(void *args);

/// @brief		Main function
/// @param argc	Number of arguments
/// @param argv	Argument vector
int	main(int argc, char **argv)
{
	t_philo	*philos;

	if ((argc != 5) && (argc != 6))
		return (ft_perror(RED"Error: Wrong number of arguments\n"NC));
	if (ft_init(&philos, argc, argv) == -1)
		return (0);
	ft_philosophize(philos);
	return (0);
}

/// @brief			Launch all philos
/// @details		- Sets the start time of the simulation
/// 				- Create all philo threads
/// 				- Detach all philo threads (so they run independently)
/// 				- Create monitor thread
/// 				- Join monitor thread
/// 				- Destroy philos mutexes and printf mutex
/// @param philos	Pointer to array of philos
static void	ft_philosophize(t_philo *philos)
{
	int	i;

	i = -1;
	philos->data->t_start = ft_gettime();
	while (++i < philos->data->n_philos)
	{
		(philos + i)->t_meal = ft_gettime();
		if (pthread_create(&philos[i].thread, NULL, &ft_start_philo, \
							&philos[i]) != 0)
			ft_perror(RED"Error: Failed to create philo thread\n"NC);
		pthread_detach((philos + i)->thread);
		usleep(50);
	}
	if (pthread_create(&philos->data->monitor, NULL, &ft_monitor, philos) != 0)
		ft_perror(RED"Error: Failed to create monitor thread\n"NC);
	if (pthread_join(philos->data->monitor, NULL) != 0)
		ft_perror(RED"Error: Failed to join monitor thread\n"NC);
	i = -1;
	while (++i < philos->data->n_forks)
		pthread_mutex_destroy(&philos->data->mutex_fork[i]);
	pthread_mutex_destroy(&philos->data->mutex_printf);
}

static void	*ft_start_philo(void *args)
{
	(void)args;
	return (NULL);
}

static void	*ft_monitor(void *args)
{
	(void)args;
	return (NULL);
}
