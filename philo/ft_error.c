/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:49:16 by passunca          #+#    #+#             */
/*   Updated: 2024/05/17 19:15:57 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/***
* @file			ft_error.c
* @brief		Error handling functions
* @version		1.0
* @date			2024-05-16
* @copyright	© 2024 passunca
***/

#include "philo.h"

static int	ft_putstr_fd(char *str, int fd);
static int	ft_strlen(char *str);

/// @brief		Print error message
/// @param err	Error message to print
/// @return		Return FAILURE (1)
int	ft_perror(char *err)
{
	return (ft_putstr_fd(err, 2), FAILURE);
}

/// @brief		Print a string to a given fd
/// @param str	String to print
/// @param fd	File descriptor
static int	ft_putstr_fd(char *str, int fd)
{
	if (!str || (fd < 0))
		return (FAILURE);
	return (write(fd, str, ft_strlen(str)));
}

/// @brief		Count the number of chars in a string
/// @param str	String to measure
/// @return		Length of the string
/// @note		Used in ft_putstr_fd
static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		++len;
	return (len);
}
