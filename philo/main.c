/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:17:35 by passunca          #+#    #+#             */
/*   Updated: 2024/05/29 19:21:47 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_philosophize(t_philo *philos);
static void	*ft_start_philo(void *args);
static int	ft_monitor(t_philo *philo, t_data *data);
static void	ft_free(t_philo *philo, t_data *data);

/// @brief			Main function
/// @param argc		Number of arguments
/// @param argv		Argument vector
/// @var philos		Pointer to array of philos
/// @var data		Pointer to a t_data struct
/// @return			0 on success, 1 on failure
/// @details		- Check number of arguments
/// 				- Initialize all simulation data
/// 				- Launch simulation
/// 				- Free data and philos
/// @note			Philosophy Time!!
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
	if (ft_philosophize(philos) != SUCCESS)
		return (ft_free(philos, data), EXIT_FAILURE);
	return (ft_free(philos, data), EXIT_SUCCESS);
}

/// @brief			Launch all philos
/// @param philos	Pointer to array of philos
/// @var i			To iterate through philos/threads
/// @return			0 on success, 1 on failure
/// @details		- Allocate memory for the mutexes
///					- Create all philo threads (w/ failure protection)
/// 				- Run monitor
/// 				- Join philo threads
/// 				- Destroy all mutexes
/// 				- Free allocated memory for threads
/// @note			Used in main
static int	ft_philosophize(t_philo *philo)
{
	int			i;

	philo->data->th = malloc (sizeof(pthread_t) * philo->data->n_philos);
	if (philo->data->th == NULL)
		return (FAILURE);
	i = -1;
	while (++i < philo->data->n_philos)
	{
		if (pthread_create(&philo->data->th[i], 0, ft_start_philo, &philo[i]))
		{
			while (i--)
				pthread_join(philo->data->th[i], NULL);
			return (free(philo->data->th), FAILURE);
		}
	}
	if (ft_monitor(philo, philo->data) != SUCCESS)
		return (ft_kill_mtx(philo), free(philo->data->th),
			FAILURE);
	i = -1;
	while (++i < philo->data->n_philos)
		if (pthread_join (philo->data->th[i], NULL))
			return (FAILURE);
	return (ft_kill_mtx(philo), free(philo->data->th), SUCCESS);
}

/// @brief			Launch a philo thread
/// @param args		Pointer to a t_philo struct
/// @return			NULL
/// @details		While the simulation is running a philo:
/// 				- Thinks (print)
/// 				- Attempts to grab forks by locking mutexes
///					- After getting forks, eats (print and waits)
///					- Updates last meal time
///					- Releases forks
///					- Increments meal count if the simulation is not done
///					- Sleeps (print and waits)
/// @note			Used in ft_philosophize
static void	*ft_start_philo(void *arg)
{
	t_philo	*self;

	self = (t_philo *) arg;
	if (self->id % 2 == 0)
	{
		ft_log(self, "is thinking");
		ft_msleep(self->data->t_meal);
	}
	while (1)
	{
		if (ft_isdead(self))
			break ;
		if (ft_eating(self) != SUCCESS)
			break ;
		ft_log(self, "is thinking");
		ft_msleep(self->data->t_think);
	}
	return (NULL);
}

/// @brief			Monitors if any philo has died or if the simulation is done
/// @param philo	Pointer to a t_philo struct
/// @param data		Pointer to a t_data struct
/// @var l_meal		Last meal time
/// @var i			To ride the array of philos
///	@return			0 on success, 1 on failure
/// @details		While the simulation is running:
///					- Get the last meal time of a philo
///					- Check if the philos have eaten n_meals times
///					- Check if a philo has died
///	@note			Used in ft_philosophize
static int	ft_monitor(t_philo *philo, t_data *data)
{
	t_msec			l_meal;
	int				i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->mutex[MTX_MEALS]);
		l_meal = philo[i].last_meal;
		pthread_mutex_unlock(&data->mutex[MTX_MEALS]);
		if (l_meal && ft_are_done(philo, data))
		{
			ft_done(data);
			break ;
		}
		if (l_meal && ((ft_gettime() - l_meal) > data->t_death))
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

/// @brief			Free all allocated memory
/// @param philo	Pointer to a t_philo struct
/// @param data		Pointer to a t_data struct
/// @note			Used in main
static void	ft_free(t_philo *philo, t_data *data)
{
	if (data && data->mutex)
		free(data->mutex);
	if (data)
		free(data);
	if (philo && philo->fork)
		free(philo->fork);
	if (philo)
		free(philo);
}
