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
static void	ft_philo_log(t_philo *philo, char *str);

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
/// @param philos	Pointer to array of philos
/// @details		- Sets the start time of the simulation
/// 				- Create all philo threads
/// 				- Detach all philo threads (so they run independently)
/// 				- Create monitor thread
/// 				- Join monitor thread
/// 				- Destroy philos mutexes and printf mutex
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
/// @note			Used in ft_philosophize
/// @return			NULL
static void	*ft_start_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!philo->data->done)
	{
		ft_philo_log(philo, "is thinking");
		pthread_mutex_lock(philo->l_fork);
		ft_philo_log(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		ft_philo_log(philo, "has taken a fork");
		ft_philo_log(philo, "is eating");
		ft_philo_do(philo->data->t_meal, philo->data);
		philo->t_meal = ft_gettime();
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		if (!philo->data->done)
			philo->meal_count++;
		ft_philo_log(philo, "is sleeping");
		ft_philo_do(philo->data->t_sleep, philo->data);
	}
	return (NULL);
}

/// @brief			Monitors if any philo has died or if the simulation is done
/// @param args		Pointer to a t_philo struct
/// @details		While the simulation is running:
///					- Loops through all philos:
///						- Checks if a philo has died
///							- Prints that the philo has died
///							- If so, sets the done flag
///						- Increments the number of times the philo has eaten
///					- Check if numnber of meals has been reached
///	@return			NULL
static void	*ft_monitor(void *args)
{
	t_philo	*philos;
	int		meals_done;
	int		i;

	philos = (t_philo *)args;
	while (!philos->data->done)
	{
		i = -1;
		meals_done = 0;
		while (++i < philos->data->n_philos)
		{
			if ((ft_gettime() - (philos + i)->t_meal) > philos->data->t_death)
			{
				ft_philo_log((philos + i), "died");
				philos->data->done = 1;
				break ;
			}
			if ((philos->data->n_meals != -1) \
				&& ((philos + i)->meal_count >= philos->data->n_meals))
				++meals_done;
		}
		if (meals_done == philos->data->n_philos)
			philos->data->done = 1;
	}
	return (NULL);
}

/// @brief			Lock and unlock mutex and print message to stdout
/// @param philo	Pointer to a t_philo struct
/// @param str		Message to print
static void	ft_philo_log(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->mutex_printf);
	if (!philo->data->done)
		printf("%lld %d %s\n", \
				(ft_gettime() - philo->data->t_start), philo->id, str);
	pthread_mutex_unlock(&philo->data->mutex_printf);
}
