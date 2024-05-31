/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:33:44 by passunca          #+#    #+#             */
/*   Updated: 2024/05/29 19:32:54 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_data(t_data **data, int argc, char **argv);
static int	ft_init_mutexes(t_data **data);
static int	ft_init_philos(t_philo **philo, t_data *data);

/// @brief			Initialize all simulation data
/// @details		- ...
/// @param philo	Pointer to array of philos
/// @param data		Pointer to a t_data struct
/// @param argc		Number of arguments
/// @param argv		Argument vector
/// @return			0 on success, 1 on failure
/// @details		- Allocate memory for the data
/// 				- Init the data
///					- Allocate memory for philos
/// 				- Init array of philos
/// @note			Used in main
int	ft_init(t_philo **philo, t_data **data, int argc, char **argv)
{
	*data = malloc(sizeof(t_data));
	if (*data == NULL)
		return (ft_perror(RED"Error: failure to alloc data\n"NC));
	(*data)->mutex = NULL;
	if (ft_init_data(data, argc, argv) != SUCCESS)
		return (FAILURE);
	*philo = malloc(sizeof(t_philo) * (*data)->n_philos);
	if (*philo == NULL)
		return (ft_perror(RED"Error: failure to alloc philos\n"NC));
	(*philo)->fork = NULL;
	if (ft_init_philos(philo, *data) != SUCCESS)
		return (ft_perror(RED"Error: failure to init philos\n"NC));
	return (SUCCESS);
}

/// @brief			Initialize data
/// @param d		Pointer to a t_data struct
/// @param argc		Number of arguments
/// @param argv		Argument vector
/// @return			0 on success, -1 on failure
/// @details		- Set input arguments
///					- Init mutexes
/// @note			Used in ft_init
static int	ft_init_data(t_data **d, int argc, char **argv)
{
	(*d)->t_start = ft_gettime();
	(*d)->n_philos = ft_parse_arg(argv[1]);
	(*d)->t_death = ft_parse_arg(argv[2]);
	(*d)->t_meal = ft_parse_arg(argv[3]);
	(*d)->t_sleep = ft_parse_arg(argv[4]);
	(*d)->t_think = 0;
	if (((*d)->n_philos % 2) \
		&& (((*d)->t_death - (*d)->t_meal - (*d)->t_sleep) / 2 > 0))
		(*d)->t_think = (((*d)->t_death - (*d)->t_meal - (*d)->t_sleep) / 2);
	if (ft_check_data(d) == FAILURE)
		return (ft_perror(RED"Error: invalid arguments\n"NC));
	(*d)->n_meals = -1;
	if (argc == 6)
	{
		(*d)->n_meals = ft_parse_arg(argv[5]);
		if ((*d)->n_meals == -1)
			return (ft_perror(RED"Error: invalid number of meals\n"NC));
	}
	(*d)->done = FALSE;
	(*d)->died = FALSE;
	if (ft_init_mutexes(d))
		return (ft_perror(RED"Error: failure to init mutexes\n"NC));
	return (SUCCESS);
}

/// @brief			Initialize data mutexes
///	@param data		Pointer to a t_data struct holding the simulation data
///	@return			0 on success, -1 on failure
///	@details		- Allocate memory for mutexes
///					- Init mutexes
///	@note			Used in ft_init_data
static int	ft_init_mutexes(t_data **data)
{
	t_mutex	*mutex;
	int		i;

	mutex = malloc(sizeof(t_mutex) * MTX_NUM);
	if (mutex == NULL)
		return (ft_perror(RED"Error: failure to alloc mutexes\n"NC));
	i = 0;
	while (i < MTX_NUM)
		pthread_mutex_init(&mutex[i++], NULL);
	(*data)->mutex = mutex;
	return (SUCCESS);
}

/// @brief			Initialize a philo
/// @param philo	Pointer to a t_philo struct to init
/// @param data		Pointer to a t_data struct holding the simulation data
/// @return			0 on success, -1 on failure
/// @details		- Allocate memory for mutexes (forks)
/// 				- Init forks
/// 				- Init philos
/// @note			Used in ft_init
static int	ft_init_philos(t_philo **philo, t_data *data)
{
	t_mutex	*fork;
	int		i;

	fork = malloc(sizeof(t_mutex) * data->n_philos);
	if (!fork)
		return (ft_perror(RED"Error: failure to alloc forks\n"NC));
	i = 0;
	while (i < data->n_philos)
		pthread_mutex_init(&fork[i++], NULL);
	i = 0;
	while (i < data->n_philos)
	{
		(*philo)[i].id = (i + 1);
		(*philo)[i].last_meal = data->t_start;
		(*philo)[i].meal_count = 0;
		(*philo)[i].l_fork = i;
		if ((i - 1) < 0)
			(*philo)[i].r_fork = (data->n_philos - 1);
		else
			(*philo)[i].r_fork = (i - 1);
		(*philo)[i].fork = fork;
		(*philo)[i].data = data;
		++i;
	}
	return (SUCCESS);
}
