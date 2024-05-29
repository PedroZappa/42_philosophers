/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:32:30 by passunca          #+#    #+#             */
/*   Updated: 2024/05/29 18:32:52 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	ft_max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
