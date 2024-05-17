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

#include "philo.h"

static int	ft_putstr_fd(char *str, int fd);
static int	ft_strlen(char *str);

/// @brief		Print error message
/// @param err	Error message to print
int	ft_perror(char *err)
{
	ft_putstr_fd(err, 2);
	return (-1);
}

/// @brief		Print a string to a given fd
/// @param str	String to print
/// @param fd	File descriptor
static int	ft_putstr_fd(char *str, int fd)
{
	if (!str || (fd < 0))
		return (0);
	write(fd, str, ft_strlen(str));
	return (0);
}

/// @brief		Count the number of chars in a string
/// @param str	String to count
static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		++len;
	return (len);
}
