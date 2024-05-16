/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:18:08 by passunca          #+#    #+#             */
/*   Updated: 2024/05/16 17:52:09 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//=============================================================================/
//								Librariy Headers                               /
//=============================================================================/

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

//=============================================================================/
//							Variables & Definitions                            /
//=============================================================================/

// ANSI Escape codes
//Regular text
# define BLK "\e[0;30m"	// RGB(0, 0, 0)
# define RED "\e[0;31m"	// RGB(255, 0, 0)
# define GRN "\e[0;32m"	// RGB(0, 255, 0)
# define YEL "\e[0;33m"	// RGB(255, 255, 0)
# define BLU "\e[0;34m"	// RGB(0, 0, 255)
# define MAG "\e[0;35m"	// RGB(255, 0, 255)
# define CYN "\e[0;36m"	// RGB(0, 255, 255)
# define WHT "\e[0;37m"	// RGB(255, 255, 255)
//Reset
# define NC "\e[0m"

/// Typedefs
typedef long long	t_msec;

//=============================================================================/
//                               Structures                                    /
//=============================================================================/

typedef struct s_data
{
	int				n_philos;
	int				n_forks;
	int				n_meals;
	int				done;
	t_msec			t_start;
	t_msec			t_death;
	t_msec			t_meal;
	t_msec			t_sleep;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_printf;
	pthread_t		check_monitor;
}			t_data;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				id;
	int				dinner_count;
	t_msec			t_meal;
	t_data			*data;
}			t_philo;

//=============================================================================/
//							Function Prototypes                                /
//=============================================================================/

/// ft_error.c
///
int		ft_perror(char *err);

/// ft_parse_args.c
void	ft_parse_args(t_data *dinner, char **argv);

/// ft_security.c
///

/// ft_time.c
///
t_msec	ft_gettime(void);

#endif