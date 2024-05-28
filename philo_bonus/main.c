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

/// @brief			Handle child processes creation
/// @param philo	Pointer to a t_philo struct
/// @return			0 on success, 1 on failure
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

/// @brief		Philosophers logic
/// @param p	Pointer to a t_philo struct
/// @details	- Get the current time
/// 			- While simulation is not over:
///					- Activate sem_start semaphore
///					- If both forks are taken:
///						- Deactivate sem_start semaphore
///						- Eat or sleep or think
///					- Else 
static int	ft_philosophize(t_philo *p)
{
	ft_gettime_sem(p);
	while (1)
	{
		if (p->d->n_philos < 2)
			continue ;
		sem_wait(p->d->sem_start);
		if ((ft_take_fork(p) == 0) && (ft_take_fork(p) == 0))
		{
			sem_post(p->d->sem_start);
			if (ft_meal(p) || ft_sleep(p) || ft_think(p))
				ft_end_sem(p);
		}
		else
			ft_end_sem(p);
	}
	return (0);
}

/// @brief		Monitor thread
/// @param arg	Pointer to a t_philo struct passed by reference
/// @return		0 for success, 1 if dead
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

/// @brief		Check if a philo has died
/// @param p	Pointer to a t_philo struct passed by reference
/// @return		0 for success alive, 1 on failure
/// @details	- Activate sem_death semaphore
///					- Get the current time
///						- Check if the philo has died
///					- Deactivate sem_death semaphore
static int	ft_check(t_philo *p)
{
	if (sem_wait(p->d->sem_death) == 0)
	{
		if (ft_gettime_sem(p) == 0)
		{
			if ((ft_utime(p->t_now) - ft_utime(p->t_curr)) > p->d->t_death)
			{
				ft_log(p, DEAD, p->t_now);
				ft_end_sem(p);
				return (0);
			}
		}
		if (sem_post(p->d->sem_death) != 0)
			return (ft_perror(RED"Error: sem_post failed\n"NC));
	}
	else
		return (ft_perror(RED"Error: sem_wait failed\n"NC));
	return (0);
}
