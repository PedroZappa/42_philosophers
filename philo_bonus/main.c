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
	t_philo	*philo;
	int		i;

	i = -1;
	philo = ft_parsinit(argc, argv);
	philo->t_start = ft_gettime();
	while (++i < philo->n_philos)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] == -1)
			ft_perror("Error: fork failed\n");
		if (philo->pid[i] == 0)
		{
			philo->idx = (i + 1);
			philo->t_meal = ft_gettime();
			ft_philosophize(philo);
		}
	}
	ft_free(&philo);
	return (0);
}

static void	ft_philosophize(t_philo *philo)
{
	if (pthread_create(&philo->monitor, NULL, &ft_monitor, philo))
		ft_perror("Error: pthread_create failed\n");
	if (philo->idx % 2 == 1)
		usleep(1000);
	while (1)
	{
		ft_philo_log(philo, "is thinking");
		sem_wait(philo->sem_forks);
		ft_philo_log(philo, "has taken a fork");
		sem_wait(philo->sem_forks);
		ft_philo_log(philo, "is eating");
		ft_philo_do(philo->t_meal, philo);
		philo->t_meal = ft_gettime();
		sem_post(philo->sem_forks);
		sem_post(philo->sem_forks);
		philo->curr_meal++;
		ft_philo_log(philo, "is sleeping");
		ft_philo_do(philo->t_sleep, philo);
	}
	if (pthread_join(philo->monitor, NULL))
		ft_perror("Error: pthread_join failed\n");

}

static void	*ft_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->wait)
	{
		usleep(100);
		if ((ft_gettime() - philo->t_meal) >= philo->t_death)
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
	if (philo->died == YES)
		exit(1);
	else
		exit(0);
}

static void	ft_free(t_philo **philo)
{
	(void)philo;
}
