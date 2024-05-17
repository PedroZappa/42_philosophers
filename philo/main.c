/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:17:35 by passunca          #+#    #+#             */
/*   Updated: 2024/05/17 17:37:54 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_philosophize(t_philo *philos);
// static void	*ft_monitor(void *args);

/// @brief		Main function
/// @param argc	Number of arguments
/// @param argv	Argument vector
int	main(int argc, char **argv)
{
	t_philo	*philos;

	if ((argc != 5) && (argc != 6))
		return (ft_perror(RED"Wrong number of arguments\n"NC));
	if (ft_init(&philos, argc, argv) == -1)
		return (0);
	ft_philosophize(philos);
	return (0);
}

static void	ft_philosophize(t_philo *philos)
{
	(void)philos;
}

// static void	*ft_monitor(void *args)
// {
// 	(void)args;
// 	return (NULL);
// }
