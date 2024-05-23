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

t_philo	*ft_parsinit(int argc, char **argv)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		ft_perror("Error: Failed to allocate memory (ft_init)\n");
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

// void	ft_init_semaphores(t_data *data)
// {
// 	sem_unlink("death");
// 	sem_unlink("msg");
// 	sem_unlink("stop");
// 	sem_unlink("forks");
// 	data->sem_death = sem_open("death", O_CREAT, 0600, 1);
// 	data->sem_msg = sem_open("msg", O_CREAT, 0600, 1);
// 	data->sem_wait = sem_open("stop", O_CREAT, 0600, 1);
// 	data->sem_forks = sem_open("forks", O_CREAT, 0600, data->n_philos);
// }
//
// void	ft_fork_process(t_data *data, t_philo *philo)
// {
// 	int	i;
//
// 	i = 0;
// 	while (i < data->n_philos)
// 	{
// 		philo[i].pid = fork();
// 		if (philo[i].pid == 0)
// 		{
// 			ft_start_philo(philo + i);
// 			exit(0);
// 		}
// 		++i;
// 		usleep(100);
// 	}
// }
//
// static void	ft_start_philo(t_philo *philo)
// {
// 	pthread_t	monitor;
//
// 	philo->next_meal = ft_gettime() + philo->data->t_meal;
// 	if (pthread_create(&monitor, NULL, ft_monitor, philo))
// 		ft_perror(RED"Error: pthread_create\n"NC);
// 	if (pthread_detach(monitor))
// 		ft_perror(RED"Error: pthread_detach\n"NC);
// 	while (1)
// 	{
// 		ft_grab_fork(philo);
// 		ft_have_meal(philo);
// 		ft_sleep(philo);
// 		ft_philo_log(THINKING, philo);
// 	}
// }
