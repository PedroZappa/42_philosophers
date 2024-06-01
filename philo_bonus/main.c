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
///				- Initialize philos
///				- Initialize semaphores
///				- Create children processes
///				- Free allocated memory
/// @note		Philosophy Time!!
int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philos;

	data = ft_init(argc, argv);
	if (!data)
		exit(EXIT_FAILURE);
	philos = ft_init_philos(data);
	if (!philos)
		exit(EXIT_FAILURE);
	if (ft_init_semaphores(data) || ft_children(philos))
	{
		ft_free_philos(philos);
		exit(EXIT_FAILURE);
	}
	ft_kill_philos(philos);
	ft_sem_closer(data);
	ft_free_philos(philos);
	exit(EXIT_SUCCESS);
}

/// @brief			Handle child processes creation
/// @param philo	Pointer to a t_philo struct
/// @var curr_philo	Pointer to a t_philo struct
/// @van n			To store the number of philos to iterate
/// @return			0 on success, 1 on failure
/// @details		- Get the simulation start time
/// 				- Create philo processes
///						- Create monitor thread
///						- Start philosophizing
///	@note			Used in main
static int	ft_children(t_philo *philo)
{
	t_philo	*curr_philo;
	int		n;

	curr_philo = philo;
	n = philo->d->n_philos;
	ft_set_start_time(philo);
	while (n--)
	{
		curr_philo->pid = fork();
		if (curr_philo->pid == 0)
		{
			if (pthread_create(&philo->d->monitor, NULL, \
								&ft_monitor, curr_philo))
				ft_perror(RED"Error: pthread_create failed\n"NC);
			if (pthread_detach(philo->d->monitor))
				ft_perror(RED"Error: pthread_detach failed\n"NC);
			exit(ft_philosophize(curr_philo));
		}
		else if (curr_philo->pid == -1)
			return (ft_perror(RED"Error: fork failed\n"NC));
		else
			curr_philo = curr_philo->next;
	}
	return (SUCCESS);
}

/// @brief		Philosophers logic
/// @param p	Pointer to a t_philo struct
/// @details	- Get the start time of the simulation (t_0)
/// 			- Start the philo loop
///					- Grab forks
///					- Eat / Sleep / Think
///	@note		Used in ft_children
static int	ft_philosophize(t_philo *p)
{
	ft_gettime_sem(p);
	while (1)
	{
		if (p->d->n_philos < 2)
			continue ;
		sem_wait(p->d->sem_start);
		if ((ft_take_fork(p) == SUCCESS) && (ft_take_fork(p) == SUCCESS))
		{
			sem_post(p->d->sem_start);
			if (ft_meal(p) || ft_sleep(p) || ft_think(p))
				return (ft_end_sem(p), SUCCESS);
		}
		else
			return (ft_end_sem(p), SUCCESS);
	}
	return (SUCCESS);
}

/// @brief		Monitor thread
/// @param arg	Pointer to a t_philo struct passed by reference
/// @var philo	Pointer to a t_philo struct
/// @return		0 for success, 1 if dead
/// @details	- While simulation is not over:
/// 					- Check if the philo has died
///	@note		Used in ft_children
static void	*ft_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
		if (ft_check(philo) != SUCCESS)
			return (NULL);
	return (NULL);
}

/// @brief		Check if a philo has died
/// @param p	Pointer to a t_philo struct passed by reference
/// @return		0 for success alive, 1 on failure
/// @details	- Activate sem_now semaphore
///					- Get the current time
///						- Check if the philo has died
///					- Deactivate sem_now semaphore
///	@note		Used in ft_monitor
static int	ft_check(t_philo *p)
{
	if (sem_wait(p->d->sem_now) == SUCCESS)
	{
		if (ft_gettime_sem(p) == SUCCESS)
		{
			if ((ft_utime(p->t_0) - ft_utime(p->t_curr)) > p->d->t_death)
			{
				ft_log(p, DEAD, p->t_0);
				ft_end_sem(p);
				return (SUCCESS);
			}
		}
		if (sem_post(p->d->sem_now) != SUCCESS)
			return (ft_perror(RED"Error: sem_post failed\n"NC));
	}
	else
		return (ft_perror(RED"Error: sem_wait failed\n"NC));
	return (SUCCESS);
}
