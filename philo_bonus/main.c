/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:39:21 by passunca          #+#    #+#             */
/*   Updated: 2024/05/26 22:11:22 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_children(t_philo *philo);
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
	t_data	*data;
	t_philo	*philos;

	data = ft_init(argc, argv);
	if (!data)
		exit(1);
	philos = ft_init_philos(data);
	if (!philos)
		exit(1);
	if ((ft_init_semaphores(data) == 1) || (ft_children(philos) == 1))
	{
		ft_free_philos(philos);
		exit(1);
	}
	ft_kill_philos(philos);
	ft_sem_closer(data);
	ft_free_philos(philos);
	return (0);

}

static int	ft_children(t_philo *philo)
{
	t_philo	*new;
	int		i;

	new = philo;
	i = philo->data->n_philos;
	while (i--)
	{
		new->pid = fork();
		if (new->pid == 0)
		{

			exit(ft_philosophize(new));
		}
		else if (new->pid == -1)
			return(ft_perror(RED"Error: fork failed\n"NC));
		else
			new = new->next;
	}

	if (pthread_create(&philo->data->monitor, NULL, &ft_monitor, philo))
		ft_perror(RED"Error: pthread_create failed\n"NC);
	if (pthread_detach(philo->data->monitor))
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
		sem_wait(philo->data->sem_start);
		if ((ft_take_fork(philo) == 0) && (ft_take_fork(philo) == 0))
		{
			sem_post(philo->data->sem_start);
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
	while (1)
	{
		if (ft_check(philo) != 0)
			return (NULL);
	}
	exit(0);
}

static int	ft_check(t_philo *philo)
{
	if (sem_wait(philo->data->sem_death) == 0)
	{
		if (sem_post(philo->data->sem_death) != 0)
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
