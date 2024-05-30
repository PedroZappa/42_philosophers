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
static sem_t	*ft_init_semaphore(const char *name, int n);

/// @brief		Parse and initialize the data
/// @param argc	Number of arguments
/// @param argv	Argument vector
/// @return		Pointer to a t_philo struct w/ the initialized data
/// @details	- Check if the number of arguments is valid
///				- Initialize the data
///				- Convert milliseconds to microseconds
///				- Calculate t_think time if it's not divisible by 2
///	@note		Used in main
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
///	@note		Used in ft_init
static t_data	*ft_init_data(int argc, char **argv)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (!new)
		ft_perror(RED"Error: Failed to allocate memory (ft_init)\n"NC);
	memset(new, '\0', sizeof(t_data));
	new->n_philos = ft_parse_arg(argv[1]);
	new->t_death = ft_parse_arg(argv[2]);
	new->t_meal = ft_parse_arg(argv[3]);
	new->t_sleep = ft_parse_arg(argv[4]);
	if ((new->n_philos < 1) || (new->n_philos > 200) || (new->t_death == -1) \
		|| (new->t_meal == -1) || (new->t_sleep == -1) || (new->t_death < 60) \
		|| (new->t_meal < 60) || (new->t_sleep < 60))
		exit(ft_perror(RED"Error: invalid arguments\n"NC));
	if (argc == 6)
	{
		new->meal_max = malloc(sizeof(t_msec));
		*new->meal_max = ft_parse_arg(argv[5]);
		if ((*new->meal_max <= 0) || (*new->meal_max > INT_MAX))
			exit(ft_perror(RED"Error: invalid arguments\n"NC));
	}
	return (new);
}

/// @brief		Initialize semaphores
/// @param d	Pointer to a t_data struct
/// @return		0 on success
///	@note		Used in main
int	ft_init_semaphores(t_data *d)
{
	d->sem_forks = ft_init_semaphore("/sem_forks", d->n_philos);
	d->sem_printf = ft_init_semaphore("/sem_printf", 1);
	d->sem_death = ft_init_semaphore("/sem_death", 1);
	d->sem_start = ft_init_semaphore("/sem_start", (d->n_philos / 2));
	d->sem_end = ft_init_semaphore("/sem_end", 0);
	d->sem_time = ft_init_semaphore("/sem_time", 1);
	return (SUCCESS);
}

/// @brief		Open and initialize a semaphore
/// @param name	Name of the semaphore
/// @param n	Value of the semaphore
/// @return		Reference to the initialized semaphore
///	@note		Used in ft_init_semaphores
static sem_t	*ft_init_semaphore(const char *name, int n)
{
	sem_t	*sem;

	sem_unlink(name);
	sem = sem_open(name, O_CREAT, (S_IRWXU | S_IRGRP | S_IROTH), n);
	if (sem == SEM_FAILED)
		exit(ft_perror(RED"Error: semaphore open error"NC));
	return (sem);
}
