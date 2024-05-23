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

static void	ft_start_philo(t_philo *philo);

t_philo	*ft_init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo) * data->n_philos);
	data->sem_death = NULL;
	data->sem_wait = NULL;
	data->sem_msg = NULL;
	data->sem_forks = NULL;
	while (++i < data->n_philos)
	{
		philo[i].idx = i;
		philo[i].died = NO;
		philo[i].data = data;
		philo[i].pid = -1;
		if (data->meal_counter == -1)
			philo[i].meal_counter = -1;
		else
			philo[i].meal_counter = data->meal_counter;
	}
	return (philo);
}

void	ft_init_semaphores(t_data *data)
{
	sem_unlink("death");
	sem_unlink("msg");
	sem_unlink("stop");
	sem_unlink("forks");
	data->sem_death = sem_open("death", O_CREAT, 0600, 1);
	data->sem_msg = sem_open("msg", O_CREAT, 0600, 1);
	data->sem_wait = sem_open("stop", O_CREAT, 0600, 1);
	data->sem_forks = sem_open("forks", O_CREAT, 0600, data->n_philos);
}

void	ft_fork_process(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			ft_start_philo(philo + i);
			exit(0);
		}
		++i;
		usleep(100);
	}
}

static void	ft_start_philo(t_philo *philo)
{
	pthread_t	monitor;

	philo->next_meal = ft_gettime() + philo->data->t_meal;
	if (pthread_create(&monitor, NULL, ft_monitor, philo))
		ft_perror(RED"Error: pthread_create\n"NC);
	if (pthread_detach(monitor))
		ft_perror(RED"Error: pthread_detach\n"NC);
	while (1)
	{
		ft_grab_fork(philo);
		ft_have_meal(philo);
		ft_sleep(philo);
		ft_philo_log(THINKING, philo);
	}
}
