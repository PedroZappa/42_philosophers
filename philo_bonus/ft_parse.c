/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:52:25 by passunca          #+#    #+#             */
/*   Updated: 2024/05/23 20:38:45 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_isspace(char c);
static int	ft_isdigit(char c);

/// @brief		Parse input arguments (digits)
/// @param str	Argument to parse
/// @return		Parsed argument as long on success, -1 on failure
/// @details	- Skip whitespaces
/// 			- Parse sign
///					- Exit -1 if sign is negative
///				- Parse digits
///					- Convert digit by digit
///					- Exit with -1 if number is larger than INT_MAX
///				- Return converted number;
int	ft_parse_arg(char *str)
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
			exit(ft_perror(RED"Error: Negative number\n"NC));
		++i;
	}
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i++] - '0');
		if (num > INT_MAX)
			exit(ft_perror(RED"Error: arg exceeds INT_MAX\n"NC));
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
