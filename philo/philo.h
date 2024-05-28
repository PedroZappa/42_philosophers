/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:18:08 by passunca          #+#    #+#             */
/*   Updated: 2024/05/22 11:32:31 by passunca         ###   ########.fr       */
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

/// Macros
# define YES 1
# define NO 0
# define FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5
# define DONE 6

/// Typedefs
typedef long long		t_msec;
typedef pthread_mutex_t	t_mutex;

//=============================================================================/
//                               Structures                                    /
//=============================================================================/

typedef struct s_data
{
	int			n_philos;
	int			n_forks;
	int			n_meals;
	int			done;
	t_msec		t_start;
	t_msec		t_death;
	t_msec		t_meal;
	t_msec		t_sleep;
	t_mutex		*mutex_fork;
	t_mutex		mutex_printf;
	t_mutex		mutex_time;
	t_mutex		mutex_end;
	pthread_t	monitor;
}			t_data;

typedef struct s_philo
{
	int			id;
	int			meal_count;
	pthread_t	thread;
	t_mutex		*l_fork;
	t_mutex		*r_fork;
	t_msec		t_meal;
	t_data		*data;
}			t_philo;

//=============================================================================/
//							Function Prototypes                                /
//=============================================================================/

/// ft_error.c
int		ft_perror(char *err);

/// ft_free.c
void	ft_free(t_philo **philo);

/// ft_init.c
int		ft_init(t_philo **philo, int argc, char **argv);

/// ft_parse_args.c
long	ft_parse_arg(char *str);

/// ft_time.c
t_msec	ft_gettime(void);
void	ft_philo_do(t_msec time, t_data *data);

#endif
