/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:17:35 by passunca          #+#    #+#             */
/*   Updated: 2024/05/16 17:35:45 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 1. Parse Input => Error checking && Pre-initialization
//	== Is the input an int?
//	== Is it larger than INT_MAX?
//	== Is timestamps > 60ms?
//	/// atol() and conversion to msec
// 2. Initialize Data => Forks, Philos
// 3. Start Threads => Dinner time!
// 4. Cleanup => When all philos have eaten || a philo has died
int	main(int argc, char **argv)
{
	t_data	dinner;

	(void)argv;
	if ((argc != 5) && (argc != 6))
	{
		ft_perror(RED"Wrong number of arguments\n"NC);
		return (1);
	}
	else
	{
		ft_parse_args(&dinner, argv);
		printf("Input n_philos: %d\n", dinner.n_philos);
		printf("Input t_death: %ld\n", (long)dinner.t_death);
		printf("Input t_meal: %ld\n", (long)dinner.t_meal);
		printf("Input t_sleep: %ld\n", (long)dinner.t_sleep);
		printf("Input n_meals: %d\n", dinner.n_meals);
	}
	return (0);
}
