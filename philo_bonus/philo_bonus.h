/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:12:47 by passunca          #+#    #+#             */
/*   Updated: 2024/05/26 20:36:07 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

//=============================================================================/
//								Librariy Headers                               /
//=============================================================================/

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>

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

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEAD 4

/// Typedefs
typedef long long int	t_msec;
typedef struct timeval	t_time;

//=============================================================================/
//                               Structures                                    /
//=============================================================================/

typedef struct s_philo
{
	int			n_philos;
	int			n_forks;
	t_msec		t_death;
	t_msec		t_meal;
	t_msec		t_sleep;
	t_msec		t_think;
	t_msec		curr_meal;
	t_time		t_start;
	t_time		t_now;
	t_time		t_curr;
	int			meal_max;
	int			meal_counter;
	int			done;
	int			died;
	int			idx;
	int			*pid;
	sem_t		*sem_start;
	sem_t		*sem_forks;
	sem_t		*sem_printf;
	sem_t		*sem_time;
	sem_t		*sem_death;
	sem_t		*sem_end;
	pthread_t	monitor;
}				t_philo;

//=============================================================================/
//							Function Prototypes                                /
//=============================================================================/

/// ft_ctype.c
int		ft_isspace(char c);
int		ft_isdigit(char c);

/// ft_error.c
int		ft_perror(char *err);

/// ft_fork.c
int		ft_take_fork(t_philo *philo);
int		ft_drop_fork(t_philo *philo);

/// ft_error.c
void	ft_free(t_philo **philo);

/// ft_init.c
t_philo	*ft_parsinit(int argc, char **argv);

/// ft_math.c
int		ft_min(int a, int b);

/// ft_ops.c
int		ft_meal(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		ft_think(t_philo *philo);
int		ft_log(t_philo *philo, int state, t_time t);
void	ft_philo_log(t_philo *philo, char *str);

/// ft_parse.c
int		ft_parse_arg(char *str);

/// ft_sem.c
int		ft_set_sem_t(t_philo *philo);
void	ft_sem_post_end(t_philo *philo);

/// ft_time.c
int		ft_gettime(t_time *t);
t_msec	ft_utime(t_time t);
t_msec	ft_dtime(t_time t0, t_time t1);
void	ft_ms2us(void *t);
t_time	ft_now(t_philo *philo);
// void	ft_philo_do(t_msec time, t_philo *philo);

#endif
