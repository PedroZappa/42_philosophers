/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:52:25 by passunca          #+#    #+#             */
/*   Updated: 2024/05/23 16:30:23 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_getnum(char *str);
static int	ft_init_data(t_data *data, int n, int i);

int	ft_parse(char **argv, t_data *data)
{
	int	n;
	int i;

	i = 1;
	while(argv[i])
	{
		n = ft_getnum(argv[i]);
		if (n == -1)
			return (1);
		if (ft_init_data(data, n, i))
			return (1);
		++i;
	}
	if (i == 5)
	{
		data->meal_counter = 0;
		data->curr_meal = 0;
		data->max_meals = 0;
	}
	return (0);
}

static int	ft_getnum(char *str)
{
	(void)str;
	return (-1);
}

static int	ft_init_data(t_data *data, int n, int i)
{
	(void)data;
	(void)n;
	(void)i;
	return (0);
}
