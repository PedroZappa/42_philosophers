/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:33:44 by passunca          #+#    #+#             */
/*   Updated: 2024/05/17 17:42:09 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_init_data(t_data **data, int argc, char **argv);

int	ft_init(t_philo **philo, int argc, char **argv)
{
	t_data	*data;
	// t_philo	*tmp;
	// int		i;

	(void)philo;
	(void)argv;
	(void)argc;

	if (ft_init_data(&data, argc, argv) == -1)
		return (-1);
	return (0);
}

static int	ft_init_data(t_data **data, int argc, char **argv)
{
	(void)data;
	(void)argc;
	(void)argv;
	return (0);
}
