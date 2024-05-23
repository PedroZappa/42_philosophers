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

static void	ft_philosophize(t_philo *philo);
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
	(void)philo;
}

static void	ft_free(t_philo **philo)
{
	(void)philo;
}
