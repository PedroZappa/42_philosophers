/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:12:47 by passunca          #+#    #+#             */
/*   Updated: 2024/05/26 22:19:26 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

//=============================================================================/
//								Librariy Headers                               /
//=============================================================================/

# include <fcntl.h>			// O_CREAT S_IRWXU S_IRGRP S_IROTH
# include <limits.h>		// INT_MAX
# include <pthread.h>		// pthread_create pthread_detach
# include <semaphore.h>		// sem_open sem_close sem_unlink
# include <signal.h>		// SIGKILL
# include <stdio.h>			// printf
# include <string.h>		// memset
# include <stdlib.h>		// exit, free, malloc
# include <sys/time.h>		// gettimeofday
# include <unistd.h>		// fork usleep

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
# define NC "\e[0m"

/// Boolean
# define NO 0
# define YES 1

/// States
enum {
	FORK = 0,
	EAT = 1,
	SLEEP = 2,
	THINK = 3,
	DEAD = 4
};

/// Typedefs
typedef long long		t_msec;
typedef struct timeval	t_time;

//=============================================================================/
//                               Structures                                    /
//=============================================================================/

typedef struct s_data
{
	int			n_philos;
	t_msec		t_death;
	t_msec		t_meal;
	t_msec		t_sleep;
	t_msec		t_think;
	t_time		t_start;
	int			*meal_max;
	sem_t		*sem_start;
	sem_t		*sem_forks;
	sem_t		*sem_printf;
	sem_t		*sem_time;
	sem_t		*sem_death;
	sem_t		*sem_end;
	pthread_t	monitor;
}				t_data;

typedef struct s_philo
{
	int				idx;
	pid_t			pid;
	t_data			*d;
	t_time			t_curr;
	t_time			t_now;
	int				n_meals;
	struct s_philo	*next;
	struct s_philo	*prev;
}				t_philo;

//=============================================================================/
//							Function Prototypes                                /
//=============================================================================/

/// ft_error.c
int		ft_perror(char *err);

/// ft_fork.c
int		ft_take_fork(t_philo *philo);
int		ft_drop_fork(t_philo *philo);

/// ft_free.c
void	ft_free(t_philo *philos, t_data *data);
int		ft_sem_closer(t_data *to_del);
int		ft_kill_philos(t_philo *philo);
int		ft_free_data(t_data *data);

/// ft_init.c
t_data	*ft_init(int argc, char **argv);
int		ft_init_semaphores(t_data *data);

/// ft_init_philo.c
t_philo	*ft_init_philos(t_data *data);
void	ft_free_philos(t_philo *philo);

/// ft_helper.c
int		ft_min(int a, int b);
int		ft_set_start_time(t_philo *philo);

/// ft_ops.c
int		ft_meal(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		ft_think(t_philo *philo);
int		ft_log(t_philo *philo, int state, t_time t);

/// ft_parse.c
int		ft_parse_arg(char *str);

/// ft_sem.c
int		ft_gettime_sem(t_philo *philo);
void	ft_end_sem(t_philo *philo);

/// ft_time.c
int		ft_gettime(t_time *t);
t_msec	ft_utime(t_time t);
t_msec	ft_dtime(t_time t0, t_time t1);
void	ft_ms2us(void *t);
t_time	ft_now(t_philo *philo);

#endif
