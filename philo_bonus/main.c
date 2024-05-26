/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:39:21 by passunca          #+#    #+#             */
/*   Updated: 2024/05/26 11:27:40 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_philosophize(t_philo *philo);
static void	*ft_monitor(void *arg);

/// @brief		Philosophers main function
/// @param argc	Number of arguments
/// @param argv	Argument vector
/// @details	- Parse input arguments and initialize the data 
///				- Get the current time (simulation start)
///				- Fork n_philos processes
///					- Handle failure to fork on main process
///					- Handle child processes logic
///				- Free allocated memory
int	main(int argc, char **argv)
{
	t_philo	*philos;
	int		i;

	i = -1;
	philos = ft_parsinit(argc, argv);
	philos->t_start = ft_gettime();
	while (++i < philos->n_philos)
	{
		philos->pid[i] = fork();
		if (philos->pid[i] == -1)
			ft_perror(RED"Error: fork failed\n"NC);
		if (philos->pid[i] == 0)
		{
			philos->idx = (i + 1);
			philos->curr_meal = ft_gettime();
			if (pthread_create(&philos->monitor, NULL, &ft_monitor, philos))
				ft_perror(RED"Error: pthread_create failed\n"NC);
			if (pthread_detach(philos->monitor))
				ft_perror(RED"Error: pthread_detach failed\n"NC);
			ft_philosophize(philos);
		}
	}
	ft_free(&philos);
	return (0);
}

/// @brief			Philosophers logic
/// @param philo	Pointer to a t_philo struct
/// @details		- Create monitor thread
/// 				- If idx is odd, wait 1ms
/// 				- While alive:
/// 					- Log "is thinking"
/// 					- Wait for forks
/// 					- Log "has taken a fork" when fork is available
/// 					- Log "is eating" when both forks have been taken
/// 					- Wait for t_meal (eat)
/// 					- Get current meal time
/// 					- Put back forks
/// 					- Count meal
/// 					- Log "is sleeping"
/// 				- Join monitor thread
static void	ft_philosophize(t_philo *philo)
{
	if ((philo->idx % 2) == 1)
		usleep(1000);
	while (1)
	{
		ft_philo_log(philo, "is thinking");
		sem_wait(philo->sem_forks);
		ft_philo_log(philo, "has taken a fork");
		sem_wait(philo->sem_forks);
		ft_philo_log(philo, "has taken a fork");
		ft_philo_log(philo, "is eating");
		ft_philo_do(philo->t_meal, philo);
		philo->curr_meal = ft_gettime();
		sem_post(philo->sem_forks);
		sem_post(philo->sem_forks);
		philo->meal_counter += 1;
		ft_philo_log(philo, "is sleeping");
		ft_philo_do(philo->t_sleep, philo);
	}
	sem_close(philo->sem_printf);
	sem_close(philo->sem_forks);
	free(philo->pid);
	free(philo);
}

/// @brief		Monitor thread
/// @param arg	Pointer to a t_philo struct passed by reference
/// @return		0 if alive, 1 if dead
/// @details	- Typecast arg (void *) to a t_philo *
/// 			- While simulation is not over:
/// 				- Sleep 100ms
/// 				- Check if philo died
///						- Set philo as dead
///						- Print death message protected by semaphore
/// 				- Check if philo has eaten max number of meals
///						- Set philo as dead
///				- If philo has died
///					- Exit wiith 1
///				- Else if philo has eaten max number of meals
///					- Exit with 0
static void	*ft_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->done)
	{
		usleep(100);
		if ((ft_gettime() - philo->curr_meal) > philo->t_death)
		{
			philo->died = YES;
			sem_wait(philo->sem_printf);
			printf("%lld %d %s\n", \
					(ft_gettime() - philo->t_start), philo->idx, "died");
			philo->done = YES;
			break ;
		}
		if ((philo->meal_max != -1) && (philo->meal_counter >= philo->meal_max))
		{
			philo->done = YES;
			break ;
		}
	}
	if (philo->died)
		exit(1);
	else
		exit(0);
}
