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
int	ft_init(t_philo **philo, t_data **data, int argc, char **argv)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
		return (ft_perror(RED"Error: failure to alloc data\n"NC));
	(*data)->mutex = NULL;
	if (ft_init_data(data, argc, argv) != SUCCESS)
		return (FAILURE);
	*philo = malloc(sizeof(t_philo) * (*data)->n_philos);
	if (!(*philo))
		return (ft_perror(RED"Error: failure to alloc philos\n"NC));
	(*philo)->fork = NULL;
	if (ft_init_philo(philo, *data) != SUCCESS)
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
	(*data)->t_start = ft_gettime();
	(*data)->n_philos = ft_parse_arg(argv[1]);
	(*data)->t_death = ft_parse_arg(argv[2]);
	(*data)->t_meal = ft_parse_arg(argv[3]);
	(*data)->t_sleep = ft_parse_arg(argv[4]);
	(*data)->t_think = 0;
	if (((*data)->n_philos % 2) && ((*data)->t_meal > (*data)->t_sleep))
		(*data)->t_think = (1 + ((*data)->t_meal - (*data)->t_sleep)); 
	if (((*data)->n_philos < 1) || ((*data)->n_philos > 200) || ((*data)->t_death == -1) \
		|| ((*data)->t_meal == -1) || ((*data)->t_sleep == -1) || ((*data)->t_death < 60) \
		|| ((*data)->t_meal < 60) || ((*data)->t_sleep < 60))
		return (ft_perror(RED"Error: invalid arguments\n"NC));
	(*data)->n_meals = -1;
	if (argc == 6)
	{
		(*data)->n_meals = ft_parse_arg(argv[5]);
		if ((*data)->n_meals == -1)
			return (ft_perror(RED"Error: invalid number of meals\n"NC));
	}
	(*data)->done = FALSE;
	(*data)->died = FALSE;
	if (ft_init_mutexes(data))
		return (ft_perror(RED"Error: failure to init mutexes\n"NC));
	return (SUCCESS);
}

/// @brief			Initialize data mutexes
///	@param data		Pointer to a t_data struct holding the simulation data
///	@return			0 on success, -1 on failure
static int	ft_init_mutexes(t_data **data)
{
	t_mutex	*mutex;
	int		i;

	mutex = malloc(sizeof(t_mutex) * MTX_NUM);
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
		philo[i]->fork = fork;
		philo[i]->data = data;
		++i;
	}
	return (SUCCESS);
}
