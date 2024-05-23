/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:12:47 by passunca          #+#    #+#             */
/*   Updated: 2024/05/23 20:26:50 by passunca         ###   ########.fr       */
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

typedef struct s_data
{
	int				n_philos;
	int				meal_counter;
	int				max_meals;
	int				curr_meal;
	sem_t			*forks;
	sem_t			*msg;
	sem_t			*death;
	sem_t			*stop;
	t_msec			t_start;
	t_msec			t_death;
	t_msec			t_meal;
	t_msec			t_sleep;
}				t_data;

typedef struct s_philo
{
	pid_t	pid;
	t_msec	meal_start;
	t_msec	next_meal;
	int		idx;
	int		died;
	int		meal_counter;
	t_data	*data;
}				t_philo;

//=============================================================================/
//							Function Prototypes                                /
//=============================================================================/

/// ft_ctype.c
int		ft_isspace(char c);
int		ft_isdigit(char c);

/// ft_error.c
int		ft_perror(char *err);
int		ft_perror_free(t_data *data, char *err, int ret);

/// ft_free.c
void	ft_free(t_data *data, t_philo *philo);

/// ft_init.c
t_philo	*ft_init_philo(t_data *data);
void	ft_init_semaphores(t_data *data);
void	ft_fork_process(t_data *data, t_philo *philo);

/// ft_ops.c
void	*ft_monitor(void *arg);
void	ft_philo_log(int id, t_philo *philo);
void	ft_grab_fork(t_philo *philo);
void	ft_have_meal(t_philo *philo);
void	ft_sleep(t_philo *philo);

/// ft_time.c
t_msec	ft_gettime(void);

/// ft_parse.c
int		ft_parse(char **argv, t_data *data);


#endif
