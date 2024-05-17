/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:15:10 by passunca          #+#    #+#             */
/*   Updated: 2024/05/17 17:38:49 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static long	ft_atol(char *str);
// static int	ft_isspace(char c);
// static int	ft_isdigit(char c);

// void	ft_parse_args(t_philo *philo, char **argv)
// {
// 	philo->n_philos = ft_atol(argv[1]);
// 	philo->t_death = ft_atol(argv[2]);
// 	philo->t_meal = ft_atol(argv[3]);
// 	philo->t_sleep = ft_atol(argv[4]);
// 	if (argv[5])
// 		philo->n_meals = ft_atol(argv[5]);
// 	else
// 		philo->n_meals = -1;
// }

// static long	ft_atol(char *str)
// {
// 	long	num;
// 	int		i;
// 	int		sign;
//
// 	i = 0;
// 	sign = 1;
// 	num = 0;
// 	while (ft_isspace(str[i]))
// 		++i;
// 	if (str[i] == '+' || str[i] == '-')
// 	{
// 		if (str[i] == '-')
// 			return (ft_perror(RED"Negative number\n"NC));
// 		++i;
// 	}
// 	while (ft_isdigit(str[i]))
// 		num = (num * 10) + (str[i++] - '0');
// 	return (num * sign);
// }
//
// static int	ft_isspace(char c)
// {
// 	if ((c == ' ') || ((c >= 9) && (c <= 13)))
// 		return (1);
// 	else
// 		return (0);
// }
//
// static int	ft_isdigit(char c)
// {
// 	if ((c >= '0') && (c <= '9'))
// 		return (1);
// 	else
// 		return (0);
// }
