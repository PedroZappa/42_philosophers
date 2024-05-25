/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:15:10 by passunca          #+#    #+#             */
/*   Updated: 2024/05/17 21:11:13 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c);
static int	ft_isdigit(char c);

/// @brief		Parse input argument and return it as long
/// @param str	Argument to parse
/// @return		Parsed argument as long on success, -1 on failure
long	ft_parse_arg(char *str)
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

/// @brief		Check if a character is a space
/// @param c	Character to check
/// @return		1 if true, 0 if false
static int	ft_isspace(char c)
{
	return ((c == ' ') || ((c >= 9) && (c <= 13)));
}

/// @brief		Check if a character is a digit
/// @param c	Character to check
/// @return		1 if true, 0 if false
static int	ft_isdigit(char c)
{
	return ((c >= '0') && (c <= '9'));
}
