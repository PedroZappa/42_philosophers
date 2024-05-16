/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:17:35 by passunca          #+#    #+#             */
/*   Updated: 2024/05/16 17:56:43 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_philosophize(t_data *dinner);
// static void	*ft_monitor(void *args);

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

	if ((argc != 5) && (argc != 6))
		return (ft_perror(RED"Wrong number of arguments\n"NC));
	else
	{
		ft_parse_args(&dinner, argv);
		ft_philosophize(&dinner);
		return (0);
	}
}

static void	ft_philosophize(t_data *dinner)
{
	(void)dinner;
}

// static void	*ft_monitor(void *args)
// {
// 	(void)args;
// 	return (NULL);
// }
