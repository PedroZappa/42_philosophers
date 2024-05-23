/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:39:21 by passunca          #+#    #+#             */
/*   Updated: 2024/05/23 16:14:41 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int main(int argc, char **argv)
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
		sem_wait(data.stop);
		ft_fork_process(&data, philo);
		sem_wait(data.stop);
		ft_free(&data, philo);
	}
	else
		ft_perror(RED"Wrong number of arguments\n"NC);
	return (0);
}
