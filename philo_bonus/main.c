/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:39:21 by passunca          #+#    #+#             */
/*   Updated: 2024/05/23 21:11:40 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>

static void	ft_philosophize(t_philo *philo);
static void	*ft_monitor(void *arg);
static void	ft_free(t_philo **philo);

/// @brief		Philosophers main function
/// @param argc	Number of arguments
/// @param argv	Argument vector
/// @details	- Parse the arguments and 
///				- Initialize the data
///				-
int	main(int argc, char **argv)
{
	t_philo	*philos;
	int		i;

	philos = ft_parsinit(argc, argv);
	i = -1;
	philos->t_start = ft_gettime();
	while (++i < philos->n_philos)
	{
		philos->pid[i] = fork();
		if (philos->pid[i] == -1)
			ft_perror(RED"Error: fork failed\n"NC);
		if (philos->pid[i] == 0)
		{
			philos->idx = (i + 1);
			philos->curr_meal = ft_gettime();
			ft_philosophize(philos);
		}
	}
	ft_free(&philos);
	return (0);
}

static void	ft_philosophize(t_philo *philo)
{
	if (pthread_create(&philo->monitor, NULL, &ft_monitor, philo))
		ft_perror(RED"Error: pthread_create failed\n"NC);
	if ((philo->idx % 2) == 1)
		usleep(1000);
	while (1)
	{
		ft_philo_log(philo, "is thinking");
		sem_wait(philo->sem_forks);
		ft_philo_log(philo, "has taken a fork");
		sem_wait(philo->sem_forks);
		ft_philo_log(philo, "has taken a fork");
		ft_philo_log(philo, "is eating");
		ft_philo_do(philo->t_meal, philo);
		philo->curr_meal = ft_gettime();
		sem_post(philo->sem_forks);
		sem_post(philo->sem_forks);
		++philo->meal_counter;
		ft_philo_log(philo, "is sleeping");
		ft_philo_do(philo->t_sleep, philo);
	}
	if (pthread_join(philo->monitor, NULL))
		ft_perror(RED"Error: pthread_join failed\n"NC);
}

static void	*ft_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->wait)
	{
		usleep(100);
		if ((ft_gettime() - philo->curr_meal) >= philo->t_death)
		{
			philo->died = YES;
			sem_wait(philo->sem_printf);
			printf("%lld %d %s\n", \
					(ft_gettime() - philo->t_start), philo->idx, "died");
			philo->wait = YES;
			break ;
		}
		if ((philo->meal_max != -1) && (philo->meal_counter >= philo->meal_max))
		{
			philo->wait = YES;
			break ;
		}
	}
	if (philo->died)
		exit(1);
	else
		exit(0);
}

static void	ft_free(t_philo **philo)
{
	t_philo	*to_del;
	int		i;
	int		pid_status;

	to_del = *philo;
	i = 0;
	while (i < to_del->n_philos)
	{
		waitpid(-1, &pid_status, 0);
		if (pid_status != 0)
		{
			i = -1;
			while (++i < to_del->n_philos)
				kill(to_del->pid[i], SIGKILL);
			break ;
		}
		++i;
	}
	sem_close(to_del->sem_printf);
	sem_close(to_del->sem_forks);
	sem_unlink("/sem_printf");
	sem_unlink("/sem_forks");
	free(to_del->pid);
	free(to_del);
}
