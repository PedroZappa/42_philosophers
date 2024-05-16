/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:17:35 by passunca          #+#    #+#             */
/*   Updated: 2024/05/16 15:41:27 by passunca         ###   ########.fr       */
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
	(void)argc;
	(void)argv;
	return (0);
}
