/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:15:10 by passunca          #+#    #+#             */
/*   Updated: 2024/05/29 19:53:02 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/***
* @file			ft_parse.c
* @brief		Parse input arguments functionality
* @version		1.0
* @date			2024-05-16
* @copyright	© 2024 passunca
***/

#include "philo.h"

/// @brief		Parse input argument and return it as long
/// @param str	Argument to parse
/// @var num	To store the converted long
/// @var sign	To store the sign of the argument
/// @var i		To iterate through the string
/// @details	- Skip whitespaces
/// 			- Handle sign
/// 			- Check if the argument is a number
///					- Convert character to number
/// @return		Parsed argument as long on success, -1 on failure
/// @note		Used in ft_init_data
long	ft_parse_arg(char *str)
{
	long	num;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	num = 0;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (FAILURE);
		++i;
	}
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i++] - '0');
		if (num > INT_MAX)
			return (FAILURE);
	}
	return (num * sign);
}

/// @brief		Check if the parsed data is valid
/// @param data	Pointer to a t_data struct
/// @return		0 on success, 1 on failure
/// @note		Used in ft_init_data
int	ft_check_data(t_data **data)
{
	if (((*data)->n_philos < 1) || ((*data)->n_philos > 200) \
		|| ((*data)->t_death == -1) || ((*data)->t_meal == -1) \
		|| ((*data)->t_sleep == -1) || ((*data)->t_death < 60) \
		|| ((*data)->t_meal < 60) || ((*data)->t_sleep < 60))
		return (FAILURE);
	return (SUCCESS);
}
