/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctype.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:47:07 by passunca          #+#    #+#             */
/*   Updated: 2024/05/23 16:48:15 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


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

