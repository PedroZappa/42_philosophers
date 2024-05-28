/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:33:44 by passunca          #+#    #+#             */
/*   Updated: 2024/05/23 20:34:56 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_data(t_data **data, int argc, char **argv);
static int	ft_init_mutexes(t_data **data);
static int	ft_init_philo(t_philo **philo, t_data *data);

/// @brief			Initialize all simulation data
/// @details		- Initialize mutexes
///					- Initialize forks
///					- Alloc & Initialize philos
/// @param philo	Pointer to array of philos
/// @param argc		Number of arguments
/// @param argv		Argument vector
/// @return			0 on success, 1 on failure
int	ft_init(t_philo **philo, int argc, char **argv)
{
	t_data	*data;

	if (ft_init_data(&data, argc, argv) == -1)
		return (FAILURE);
	*philo = malloc(sizeof(t_philo) * data->n_philos);
	if (!(*philo))
		return (ft_perror(RED"Error: failure to alloc philos\n"NC));
	(*philo)->fork = NULL;
	if (ft_init_philo(philo, data) != SUCCESS)
		return (ft_perror(RED"Error: failure to init philos\n"NC));
	return (SUCCESS);

}

/// @brief			Parse input arguments and initialize data
/// @details		- Init n_philos
/// 				- Init time to die
/// 				- Init time to eat
/// 				- Init time to sleep
/// 				- Init n_meals
/// @param data		Pointer to a t_data struct
/// @param argc		Number of arguments
/// @param argv		Argument vector
/// @return			0 on success, -1 on failure
static int	ft_init_data(t_data **data, int argc, char **argv)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (!new)
		return (ft_perror(RED"Error: failure to alloc data\n"NC));
	new->mutex = NULL;
	new->n_philos = ft_parse_arg(argv[1]);
	new->t_death = ft_parse_arg(argv[2]);
	new->t_meal = ft_parse_arg(argv[3]);
	new->t_sleep = ft_parse_arg(argv[4]);
	if ((new->n_philos < 1) || (new->n_philos > 200) || (new->t_death == -1) \
		|| (new->t_meal == -1) || (new->t_sleep == -1) || (new->t_death < 60) \
		|| (new->t_meal < 60) || (new->t_sleep < 60))
		return (ft_perror(RED"Error: invalid arguments\n"NC));
	new->n_meals = -1;
	if (argc == 6)
	{
		new->n_meals = ft_parse_arg(argv[5]);
		if (new->n_meals == -1)
			return (ft_perror(RED"Error: invalid number of meals\n"NC));
	}
	new->done = FALSE;
	new->died = FALSE;
	if (ft_init_mutexes(&new))
		return (ft_perror(RED"Error: failure to init mutexes\n"NC));
	*data = new;
	return (SUCCESS);
}

/// @brief			Initialize forks
///	@param data		Pointer to a t_data struct holding the simulation data
///	@return			0 on success, -1 on failure
static int	ft_init_mutexes(t_data **data)
{
	t_mutex	*mutex;
	int		i;

	mutex = malloc(sizeof(t_mutex) * (size_t)MTX_NUM);
	if (!mutex)
		return (ft_perror(RED"Error: failure to alloc mutexes\n"NC));
	i = 0;
	while (i < MTX_NUM)
		pthread_mutex_init(&mutex[i++], NULL);
	(*data)->mutex = mutex;
	return (SUCCESS);
}

/// @brief			Initialize a philo
/// @param philo	Pointer to a t_philo struct to init
/// @param i		Index of the current philo
/// @param data		Pointer to a t_data struct holding the simulation data
/// @param forks	Pointer to an array of mutexes/forks (part of t_data)
static int	ft_init_philo(t_philo **philo, t_data *data)
{
	t_mutex	*fork;
	int		i;

	fork = malloc(sizeof(t_mutex) * (size_t)data->n_philos);
	if (!fork)
		return (ft_perror(RED"Error: failure to alloc forks\n"NC));
	i = 0;
	while (i < data->n_philos)
		pthread_mutex_init(&fork[i++], NULL);
	i = 0;
	while (i < data->n_philos)
	{
		philo[i]->id = (i + 1);
		philo[i]->last_meal = data->t_start;
		philo[i]->meal_count = 0;
		philo[i]->l_fork = i;
		if ((i - 1) < 0)
			philo[i]->r_fork = (data->n_philos - 1);
		else
			philo[i]->r_fork = (i - 1);
		philo[i]->fork = &fork[i];
		philo[i]->data = data;
		++i;
	}
	return (SUCCESS);
}
