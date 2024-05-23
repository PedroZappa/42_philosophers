/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:13:44 by passunca          #+#    #+#             */
/*   Updated: 2024/05/23 16:24:24 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_putstr_fd(char *str, int fd);
static int	ft_strlen(char *str);

int	ft_perror_free(t_data *data, char *err, int ret)
{
	if (data)
		if (data->forks)
			free(data->forks);
	ft_perror(err);
	return (ret);
}

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