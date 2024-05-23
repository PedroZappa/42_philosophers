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

/// @brief		Philosophers main function
/// @param argc	Number of arguments
/// @param argv	Argument vector
/// @details	- Parse the arguments and 
///				- Initialize the data
///				- Get the start time of the simulation
///				- Initialize the semaphores
///				-
int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if ((argc == 5) || (argc == 6))
	{
		if (ft_parse(argv, &data))
			return (1);
		philo = ft_init_philo(&data);
		data.t_start = ft_gettime();
		ft_init_semaphores(&data);
		sem_wait(data.sem_wait);
		ft_fork_process(&data, philo);
		sem_wait(data.sem_wait);
		ft_free(&data, philo);
	}
	else
		ft_perror(RED"Wrong number of arguments\n"NC);
	return (0);
}
