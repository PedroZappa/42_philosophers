/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:00:25 by passunca          #+#    #+#             */
/*   Updated: 2024/05/23 21:16:05 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/// @brief		Parse and initialize the data
/// @param argc	Number of arguments
/// @param argv	Argument vector
/// @return		Pointer to a t_philo struct w/ the initialized data
/// @details	- Check if the number of arguments is valid
/// 			- Initialize the data
/// 			- Alloc memory for the pid array
/// 			- Create semaphoreso
/// 			- Open semaphores
///				- Handle failure to open semaphores
///				- Return pointer to a t_philo struct w/ the initialized data
t_philo	*ft_parsinit(int argc, char **argv)
{
	t_philo	*new;

	if ((argc < 5) || (argc > 6))
		exit(ft_perror(RED"Error: Wrong number of arguments\n"NC));
	new = ft_init_data(argc, argv);
	new->pid = malloc(sizeof(int) * new->n_forks);
	if (!new->pid)
		ft_perror(RED"Error: malloc error (init pid)"NC);
	sem_unlink("/sem_printf");
	sem_unlink("/sem_forks");
	new->sem_printf = sem_open("/sem_printf", O_CREAT, S_IRWXU, 1);
	new->sem_forks = sem_open("/sem_forks", O_CREAT, S_IRWXU, new->n_forks);
	if ((new->sem_printf == NULL) || (new->sem_forks == NULL))
		ft_perror(RED"Error: semaphore open error"NC);
	return (new);
}

/// @brief		Initialize the data
/// @param argc	Number of arguments
/// @param argv	Argument vector
/// @return		Pointer to a t_philo struct w/ the initialized data
/// @details	- Allocate memory for a t_philo struct
///				- Initialize the data
///				- return pointer to a t_philo struct w/ the initialized data
t_philo	*ft_init_data(int argc, char **argv)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		ft_perror(RED"Error: Failed to allocate memory (ft_init)\n"NC);
	new->n_philos = ft_parse_arg(argv[1]);
	new->n_forks = new->n_philos;
	new->t_death = ft_parse_arg(argv[2]);
	new->t_meal = ft_parse_arg(argv[3]);
	new->t_sleep = ft_parse_arg(argv[4]);
	if ((new->n_philos < 1) || (new->n_philos > 200) || (new->t_death == -1) \
		|| (new->t_meal == -1) || (new->t_sleep == -1))
		ft_perror(RED"Error: invalid arguments\n"NC);
	new->meal_max = -1;
	if (argc == 6)
	{
		new->meal_max = ft_parse_arg(argv[5]);
		if (new->meal_max == -1)
			ft_perror(RED"Error: invalid arguments\n"NC);
	}
	new->meal_counter = 0;
	new->wait = 0;
	new->died = 0;
	return (new);
}
