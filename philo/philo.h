/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:18:08 by passunca          #+#    #+#             */
/*   Updated: 2024/05/29 20:08:22 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//=============================================================================/
//								Librariy Headers                               /
//=============================================================================/

# include <stdlib.h>	// free, malloc
# include <stdio.h>		// printf
# include <unistd.h>	// usleep
# include <pthread.h>	// pthread_create, pthread_join, pthread_mutex_init, ...
# include <sys/time.h>	// gettimeofday
# include <limits.h>	// INT_MAX

//=============================================================================/
//							Variables & Definitions                            /
//=============================================================================/

/// @brief	ANSI Escape codes
# define BLK "\e[0;30m"	// RGB(0, 0, 0)
# define RED "\e[0;31m"	// RGB(255, 0, 0)
# define GRN "\e[0;32m"	// RGB(0, 255, 0)
# define YEL "\e[0;33m"	// RGB(255, 255, 0)
# define BLU "\e[0;34m"	// RGB(0, 0, 255)
# define MAG "\e[0;35m"	// RGB(255, 0, 255)
# define CYN "\e[0;36m"	// RGB(0, 255, 255)
# define WHT "\e[0;37m"	// RGB(255, 255, 255)
# define NC "\e[0m"

/// Enums
/// @enum	Mutexes
typedef enum e_mutex
{
	MTX_PRINTF,
	MTX_MEALS,
	MTX_DONE,
	MTX_DIED,
	MTX_NUM
}	t_mutexes;

/// @enum	Booleans
typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

/// @enum	Exit status
typedef enum e_exit
{
	SUCCESS,
	FAILURE
}	t_exit;

/// Typedefs
typedef long long		t_msec;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_time;

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
/// @var fork			Array of forks
/// @var data			the access to s_data parameters.
///
typedef struct s_philo
{
	int			id;
	t_msec		last_meal;
	int			meal_count;
	int			l_fork;
	int			r_fork;
	t_mutex		*fork;
	t_data		*data;
}			t_philo;

//=============================================================================/
//							Function Prototypes                                /
//=============================================================================/

/// ft_done.c
int		ft_isdead(t_philo *philo);
void	ft_died(t_data *data);
int		ft_isdone(t_philo *philo);
int		ft_are_done(t_philo *philo, t_data *data);
void	ft_done(t_data *data);
/// ft_eat.c
int		ft_eating(t_philo *philo);
/// ft_error.c
int		ft_perror(char *err);
/// ft_free.c
void	ft_kill_mtx(t_philo *philo);
/// ft_helper.c
int		ft_isspace(char c);
int		ft_isdigit(char c);
int		ft_max(int a, int b);
int		ft_min(int a, int b);
/// ft_init.c
int		ft_init(t_philo **philo, t_data **data, int argc, char **argv);
/// ft_parse.c
long	ft_parse_arg(char *str);
int		ft_check_data(t_data **data);
/// ft_time.c
t_msec	ft_gettime(void);
void	ft_philo_do(t_msec time, t_data *data);
t_msec	ft_dtime(t_msec start);
void	ft_log(t_philo *philo, char *str);
void	ft_msleep(t_msec msec);

#endif
