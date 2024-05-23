/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:52:25 by passunca          #+#    #+#             */
/*   Updated: 2024/05/23 16:53:31 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_parse_arg(char *str);
static int	ft_init_data(t_data *data, int n, int i);
static int	ft_init_rest(t_data *data, int n, int i);

int	ft_parse(char **argv, t_data *data)
{
	int	n;
	int i;

	i = 1;
	while(argv[i])
	{
		n = ft_parse_arg(argv[i]);
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

/// @brief		Parse input argument and return it as long
/// @param str	Argument to parse
/// @return		Parsed argument as long on success, -1 on failure
static int	ft_parse_arg(char *str)
{
	long	num;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	num = 0;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (ft_perror(RED"Error: Negative number\n"NC));
		++i;
	}
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i++] - '0');
		if (num > INT_MAX)
			return (ft_perror(RED"Error: arg exceeds INT_MAX\n"NC));
	}
	return (num * sign);
}

static int	ft_init_data(t_data *data, int n, int arg)
{
	if (arg == 1)
	{
		if (n == 0)
			return (ft_perror_free(NULL, \
					RED"Error: No philos at the table\n"NC, 1));
		data->n_philos = n;
	}
	else if (arg == 2)
	{
		if (n < 60)
			return (ft_perror_free(NULL, \
					RED"Error: time_to_die cannot be less than 60ms\n"NC, 1));
		data->t_death = n;
	}
	else if (arg == 3)
	{
		if (n < 60)
			return (ft_perror_free(NULL, \
					RED"Error: time_to_eat cannot be less than 60ms\n"NC, 1));
		data->t_meal = n;
	}
	else
		ft_init_rest(data, n, arg);
	return (0);
}

int	ft_init_rest(t_data *data, int n, int arg)
{
	if (arg == 4)
	{
		if (n < 60)
			return (ft_perror_free(NULL, \
					RED"Error: time_to_sleep cannot be less than 60ms\n"NC, 1));
		data->t_sleep = n;
	}
	if (arg == 5)
	{
		if (n == 0)
			data->meal_counter = -1;
		else
		{
			data->meal_counter = n;
			data->curr_meal = 0;
			data->max_meals = (n * data->n_philos);
		}
	}
	return (0);
}
