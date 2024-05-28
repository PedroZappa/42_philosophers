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
	exit(0);
}

static int	ft_children(t_philo *philo)
{
	t_philo	*curr_philo;
	int		i;

	curr_philo = philo;
	i = philo->d->n_philos;
	ft_set_start_time(philo);
	while (i--)
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
	return (0);
}

/// @brief			Philosophers logic
/// @param philo	Pointer to a t_philo struct
/// @details		- Sleep 1000us if philo is even idx'ed
/// @details		- Set semaphores
/// 				- While simulation is not over:
static int	ft_philosophize(t_philo *p)
{
	ft_set_time_sem(p);
	while (1)
	{
		if (p->d->n_philos < 2)
			continue ;
		sem_wait(p->d->sem_start);
		if ((ft_take_fork(p) == 0) && (ft_take_fork(p) == 0))
		{
			sem_post(p->d->sem_start);
			if ((ft_meal(p) == 1) || (ft_sleep(p) == 1) || (ft_think(p) == 1))
				ft_sem_post_end(p);
		}
		else
			ft_sem_post_end(p);
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
		if (ft_check(philo) != 0)
			return (NULL);
	return (0);
}

static int	ft_check(t_philo *philo)
{
	if (sem_wait(philo->d->sem_death) == 0)
	{
		if (ft_set_time_sem(philo) == 0)
		{
			if ((ft_utime(philo->t_now) - ft_utime(philo->t_curr)) \
				> philo->d->t_death)
			{
				ft_log(philo, DEAD, philo->t_now);
				ft_sem_post_end(philo);
				return (0);
			}
		}
		if (sem_post(philo->d->sem_death) != 0)
			return (printf(RED"Error: sem_post failed\n"NC));
	}
	else
		return (printf(RED"Error: sem_wait failed\n"NC));
	return (0);
}
