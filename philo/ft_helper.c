/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:32:30 by passunca          #+#    #+#             */
/*   Updated: 2024/05/29 19:49:36 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/***
* @file			ft_helper.c
* @brief		Helper functions
* @version		1.0
* @date			2024-05-29
* @copyright	© 2024 passunca
***/

/// @brief		Check if a character is a space
/// @param c	Character to check
/// @return		1 if true, 0 if false
int	ft_isspace(char c)
{
	return ((c == ' ') || ((c >= 9) && (c <= 13)));
}

/// @brief		Check if a character is a digit
/// @param c	Character to check
/// @return		1 if true, 0 if false
int	ft_isdigit(char c)
{
	return ((c >= '0') && (c <= '9'));
}

/// @brief		Find the max of two numbers
/// @param a	First number
/// @param b	Second number
/// @return		Max of a and b
int	ft_max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

/// @brief		Find the min of two numbers
/// @param a	First number
/// @param b	Second number
/// @return		Min of a and b
int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
