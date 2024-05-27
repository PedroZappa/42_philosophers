/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:00:25 by passunca          #+#    #+#             */
/*   Updated: 2024/05/26 22:13:01 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_data	*ft_init_data(int argc, char **argv);
int				ft_init_semaphores(t_data *data);

/// @brief		Parse and initialize the data
/// @param argc	Number of arguments
/// @param argv	Argument vector
/// @return		Pointer to a t_philo struct w/ the initialized data
/// @details	- Check if the number of arguments is valid
///				- Initialize the data
///				- Convert milliseconds to microseconds
///
t_data	*ft_init(int argc, char **argv)
{
	t_data	*new;

	if ((argc < 5) || (argc > 6))
		exit(ft_perror(RED"Error: Wrong number of arguments\n"NC));
	new = ft_init_data(argc, argv);
	ft_ms2us(&new->t_death);
	ft_ms2us(&new->t_meal);
	ft_ms2us(&new->t_sleep);
	if ((new->n_philos % 2) \
		&& ((new->t_death - new->t_meal - new->t_sleep) / 2 > 0))
		new->t_think = ((new->t_death - new->t_meal - new->t_sleep) / 2);
	return (new);
}

/// @brief		Initialize the data
/// @param argc	Number of arguments
/// @param argv	Argument vector
/// @return		Pointer to a t_philo struct w/ the initialized data
/// @details	- Allocate memory for a t_philo struct
///				- Initialize the data
///				- return pointer to a t_philo struct w/ the initialized data
static t_data	*ft_init_data(int argc, char **argv)
{
	t_data	*new;

	new = malloc(sizeof(t_philo));
	ft_bzero(new, sizeof(t_philo));
	if (!new)
		ft_perror(RED"Error: Failed to allocate memory (ft_init)\n"NC);
	new->n_philos = ft_parse_arg(argv[1]);
	new->n_forks = new->n_philos;
	new->t_death = ft_parse_arg(argv[2]);
	new->t_meal = ft_parse_arg(argv[3]);
	new->t_sleep = ft_parse_arg(argv[4]);
	if ((new->n_philos < 1) || (new->n_philos > 200) || (new->t_death == -1) \
		|| (new->t_meal == -1) || (new->t_sleep == -1) || (new->t_death < 60) \
		|| (new->t_meal < 60) || (new->t_sleep < 60))
		exit(ft_perror(RED"Error: invalid arguments\n"NC));
	new->meal_max = -1;
	if (argc == 6)
	{
		new->meal_max = ft_parse_arg(argv[5]);
		if (new->meal_max == -1)
			exit(ft_perror(RED"Error: invalid arguments\n"NC));
	}
	new->meal_counter = 0;
	return (new);
}

/// @brief			Initialize semaphores
/// @param philo	Pointer to a t_philo struct
/// @return			0 on success, -1 on failure
int	ft_init_semaphores(t_data *data)
{
	sem_unlink("/sem_forks");
	data->sem_forks = sem_open("/sem_forks", O_CREAT, S_IRWXU, \
										data->n_forks);
	if (data->sem_forks == SEM_FAILED)
		 return (ft_perror(RED"Error: semaphore open error"NC));
	sem_unlink("/sem_printf");
	data->sem_printf = sem_open("/sem_printf", O_CREAT, S_IRWXU, 1);
	if (data->sem_printf == SEM_FAILED)
		return (ft_perror(RED"Error: semaphore open error"NC));
	sem_unlink("/sem_end");
	data->sem_end = sem_open("/sem_end", O_CREAT, S_IRWXU, 0);
	if (data->sem_end == SEM_FAILED)
		return (ft_perror(RED"Error: semaphore open error"NC));
	sem_unlink("/sem_death");
	data->sem_death = sem_open("/sem_death", O_CREAT, S_IRWXU, 0);
	if (data->sem_death == SEM_FAILED)
		return (ft_perror(RED"Error: semaphore open error"NC));
	sem_unlink("/sem_start");
	data->sem_start = sem_open("/sem_start", O_CREAT, S_IRWXU, \
								(data->n_philos / 2));
	if (data->sem_start == SEM_FAILED)
		return (ft_perror(RED"Error: semaphore open error"NC));
	sem_unlink("/sem_time");
	data->sem_time = sem_open("/sem_time", O_CREAT, S_IRWXU, 0);
	if (data->sem_time == SEM_FAILED)
		return (ft_perror(RED"Error: semaphore open error"NC));
	return (0);
}
