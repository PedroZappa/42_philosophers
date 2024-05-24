/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:12:47 by passunca          #+#    #+#             */
/*   Updated: 2024/05/23 21:11:30 by passunca         ###   ########.fr       */
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
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
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
# define FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5
# define DONE 6

/// Typedefs
typedef long long		t_msec;

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
	int			meal_max;
	int			meal_counter;
	int			wait;
	int			died;
	int			*pid;
	sem_t		*sem_forks;
	sem_t		*sem_printf;
	t_msec		t_start;
	int			idx;
	int			curr_meal;
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
// int		ft_perror_free(t_data *data, char *err, int ret);

/// ft_free.c
// void	ft_free(t_data *data, t_philo *philo);

/// ft_init.c
t_philo	*ft_parsinit(int argc, char **argv);
t_philo	*ft_init_data(int argc, char **argv);

/// ft_ops.c
void	ft_philo_log(t_philo *philo, char *str);

/// ft_time.c
t_msec	ft_gettime(void);
void	ft_philo_do(t_msec time, t_philo *philo);

/// ft_parse.c
int		ft_parse_arg(char *str);

#endif
