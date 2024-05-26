/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:39:21 by passunca          #+#    #+#             */
/*   Updated: 2024/05/26 20:43:43 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_child(t_philo *philo);
static int	ft_philosophize(t_philo *philo);
static void	*ft_monitor(void *arg);
static int	ft_check(t_philo *philo);

/// @brief		Philosophers main function
/// @param argc	Number of arguments
/// @param argv	Argument vector
/// @details	- Parse input arguments and initialize the data 
///				- Get the current time (simulation start)
///				- Fork n_philos processes
///					- Handle failure to fork on main process
///					- Handle child processes logic
///				- Free allocated memory
int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_time	*t;
	int		i;

	i = -1;
	t = malloc(sizeof(t_time));
	philos = ft_parsinit(argc, argv);
	if (ft_gettime(t) == -1)
		ft_perror(RED"Error: gettime failed\n"NC);
	philos->t_start = *t;
	while (++i < philos->n_philos)
	{
		philos->pid[i] = fork();
		if (philos->pid[i] == -1)
			ft_perror(RED"Error: fork failed\n"NC);
		if (philos->pid[i] == 0)
		{
			philos->idx = (i + 1);
			philos->curr_meal = ft_gettime(t);
			ft_child(philos);
		}
	}
	ft_free(&philos);
	free(t);
	return (0);
}

static void	ft_child(t_philo *philo)
{
	if (pthread_create(&philo->monitor, NULL, &ft_monitor, philo))
		ft_perror(RED"Error: pthread_create failed\n"NC);
	if (pthread_detach(philo->monitor))
		ft_perror(RED"Error: pthread_detach failed\n"NC);
	exit(ft_philosophize(philo));
}

/// @brief			Philosophers logic
/// @param philo	Pointer to a t_philo struct
/// @details		- Sleep 1000us if philo is even idx'ed
/// @details		- Set semaphores
/// 				- While simulation is not over:
///
static int	ft_philosophize(t_philo *philo)
{
	ft_set_sem_t(philo);
	while (1)
	{
		sem_wait(philo->sem_start);
		if ((ft_take_fork(philo) == 0) && (ft_take_fork(philo) == 0))
		{
			sem_post(philo->sem_start);
			if ((ft_meal(philo) == 1) || (ft_sleep(philo) == 1) \
				|| (ft_think(philo) == 1))
				ft_sem_post_end(philo);
		}
		else
			ft_sem_post_end(philo);
	}
	return (0);
}

/// @brief		Monitor thread
/// @param arg	Pointer to a t_philo struct passed by reference
/// @return		0 if alive, 1 if dead
/// @details	- Typecast arg (void *) to a t_philo *
/// 			- While simulation is not over:
static void	*ft_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->done)
	{
		if (ft_check(philo) != 0)
			return (NULL);
	}
	exit(0);
}

static int	ft_check(t_philo *philo)
{
	if (sem_wait(philo->sem_death) == 0)
	{
		if (sem_post(philo->sem_death) != 0)
		{
			printf(RED"Error: sem_post failed\n"NC);
			return (1);
		}
	}
	else
	{
		printf(RED"Error: sem_wait failed\n"NC);
		return (1);
	}
	return (0);
}
