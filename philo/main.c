/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:17:35 by passunca          #+#    #+#             */
/*   Updated: 2024/05/28 16:19:48 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_philosophize(t_philo *philos, t_data *data);
static void	*ft_start_philo(void *args);
static int	ft_monitor(t_philo *philo, t_data *data);
static void	ft_free(t_philo *philo, t_data *data);

/// @brief		Main function
/// @param argc	Number of arguments
/// @param argv	Argument vector
int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_data	*data;

	data = NULL;
	philos = NULL;
	if ((argc != 5) && (argc != 6))
		return (ft_perror(RED"Error: Wrong number of arguments\n"NC));
	if (ft_init(&philos, &data, argc, argv) != SUCCESS)
		return (ft_free(philos, data), EXIT_FAILURE);
	if (ft_philosophize(philos, philos->data) != SUCCESS)
		return (ft_free(philos, data), EXIT_FAILURE);
	return (ft_free(philos, data), EXIT_SUCCESS);
}

/// @brief			Launch all philos
/// @param philos	Pointer to array of philos
/// @details		- Sets the start time of the simulation
/// 				- Create all philo threads
/// 				- Detach all philo threads (so they run independently)
/// 				- Create monitor thread
/// 				- Join monitor thread
/// 				- Destroy philos mutexes and printf mutex
static int	ft_philosophize(t_philo *p, t_data *data)
{
	pthread_t	*th;
	int	i;

	printf(GRN"Philosophizing...\n"NC);
	th = malloc(sizeof(pthread_t) * (size_t)data->n_philos);
	if (!th)
		return (ft_perror(RED"Error: failure to alloc threads\n"NC));
	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_create(&th[i], 0, ft_start_philo, (void *)&p[i]))
		{
			while (i--)
				pthread_join(th[i], NULL);
			return (free(th), FAILURE);
		}
	}
	if (ft_monitor(p, data) != SUCCESS)
		return ((void)ft_kill_mtx(p), free(th), FAILURE);
	i = -1;
	while (++i < p->data->n_philos)
		if (pthread_join(th[i], NULL))
			return (FAILURE);
	printf(RED"Philosophizing is Over.\n"NC);
	return ((void)ft_kill_mtx(p), free(th), SUCCESS);
}

/// @brief			Launch a philo thread
/// @param args		Pointer to a t_philo struct
/// @details		While the simulation is running a philo:
/// 				- Thinks (print)
/// 				- Attempts to grab forks by locking mutexes
///					- After getting forks, eats (print and waits)
///					- Updates last meal time
///					- Releases forks
///					- Increments meal count if the simulation is not done
///					- Sleeps (print and waits)
/// @note		Used in ft_philosophize
/// @return			NULL
static void	*ft_start_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if ((philo->id % 2) == 0)
	{
		ft_log(philo, "is thinking");
		usleep(philo->data->t_meal);
	}
	while (1)
	{
		if (ft_isdead(philo) == TRUE)
			break ;
		if (ft_eating(philo) != SUCCESS)
			break ;
		ft_log(philo, "is thinking");
		usleep(philo->data->t_think);
	}
	return (NULL);
}

/// @brief			Monitors if any philo has died or if the simulation is done
/// @param args		Pointer to a t_philo struct
/// @details		While the simulation is running:
///					- Loops through all philos:
///						- Checks if a philo has died
///							- Prints that the philo has died
///							- Sets the done flag
///						- Increments the number of times the philo has eaten
///					- Check if n_meals has been reached
///	@return			NULL
static int	ft_monitor(t_philo *philo, t_data *data)
{
	int		last_meal;
	int		i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->mutex[MTX_MEALS]);
		last_meal = philo[i].last_meal;
		pthread_mutex_unlock(&data->mutex[MTX_MEALS]);
		if (last_meal && ft_are_done(philo, data))
		{
			ft_done(data);
			break ;
		}
		if (last_meal && ((ft_gettime() - last_meal) >= data->t_death))
		{
			ft_died(data);
			ft_log(&philo[i], "died");
			break ;
		}
		i = ((i + 1) % data->n_philos);
		usleep(200);
	}
	return (SUCCESS);
}

static void	ft_free(t_philo *philo, t_data *data)
{
	if (data && data->mutex)
		free (data->mutex);
	if (data)
		free (data);
	if (philo && philo->fork)
		free (philo->fork);
	if (philo)
		free (philo);
}
