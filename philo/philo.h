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

typedef enum e_mutex
{
	MTX_PRINTF,
	MTX_MEALS,
	MTX_DIED,
	MTX_NUM
}	t_mutexes;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_exit
{
	SUCCESS,
	FAILURE
}	t_exit;

/// Typedefs
typedef long long		t_msec;
typedef pthread_mutex_t	t_mutex;

//=============================================================================/
//                               Structures                                    /
//=============================================================================/


/// @brief			Simulation data.
///
/// @var n_philos	number of philosophers
/// @var t_death	philo's life time (in ms)
/// @var t_meal		philo's meal length (in ms)
/// @var t_sleep	philo's sleep length (in ms)
/// @var t_think	philo's think length (in ms)
/// @var n_meals	max number of meals
/// @var t_start	Start time of the simulation
/// @var done		True when all philos ate n_meals times
/// @var died		True when a philo dies
/// @var mutex		Array of mutexes
///
typedef struct s_data
{
	int			n_philos;
	t_msec		t_death;
	t_msec		t_meal;
	t_msec		t_sleep;
	t_msec		t_think;
	int			n_meals;
	t_msec		t_start;
	int			done;
	int			died;
	t_mutex		*mutex;
}			t_data;

/// @brief				Philo's data.
///
/// @var id				philo's id				
/// @var last_meal		Time of last meal
/// @var meals_count	Number of meals eaten
/// @var l_fork			Philo's left fork
/// @var r_fork			Philo's right fork
/// @var fork			a mutex that symbolize one fork from philos dining problem.
/// @var data			the access to s_data parameters.
///
typedef struct s_philo
{
	int			id;
	int			last_meal;
	int			meal_count;
	pthread_t	thread;
	int			l_fork;
	int			r_fork;
	t_mutex		*fork;
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
