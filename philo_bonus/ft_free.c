/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 11:26:15 by passunca          #+#    #+#             */
/*   Updated: 2024/05/26 22:08:42 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int			ft_sem_closer(t_data *to_del);
static int	ft_sem_unlinker(void);

/// @brief			Free allocated memory
/// @param philo	Pointer to a t_philo struct
/// @details		- Kill all child processes
/// 				- Close semaphores
/// 				- Unlink semaphores
/// 				- Free pointer to pid array
/// 				- Free pointer to t_philo struct
void	ft_free(t_philo *philos)
{
	ft_kill_philos(philos);
	ft_sem_closer(philos->data);
	ft_free_philos(philos);
}

/// @brief			Close semaphores
/// @param to_del	Pointer to a t_philo struct
/// @return			0 on success, 1 on failure
int	ft_sem_closer(t_data *to_del)
{
	if (sem_close(to_del->sem_printf) \
		|| sem_close(to_del->sem_forks) \
		|| sem_close(to_del->sem_start) \
		|| sem_close(to_del->sem_death)
		|| sem_close(to_del->sem_end))
	{
		ft_perror(RED"Error: semaphore close error"NC);
		return (1);
	}
	return (ft_sem_unlinker());
}

/// @brief			Unlink semaphores
/// @param			none
/// @return			0 on success, 1 on failure
static int	ft_sem_unlinker(void)
{
	if (sem_unlink("/sem_printf") \
		|| sem_unlink("/sem_forks") \
		|| sem_unlink("/sem_start") \
		|| sem_unlink("/sem_death")
		|| sem_unlink("/sem_end"))
	{
		ft_perror(RED"Error: semaphore unlink error"NC);
		return (1);
	}
	return (0);
}

int	ft_kill_philos(t_philo *philo)
{
	t_philo	*target;
	int	i;

	target = philo;
	i = 0;
	while (i--)
		sem_post(philo->data->sem_end);
	while ((target->next) && (target->next != philo))
	{
		kill(target->pid, SIGKILL);
		target = target->next;
	}
	kill(target->pid, SIGKILL);
	return (0);
}

int	ft_free_data(t_data *data)
{
	// if (data->t_meal != NULL)
	// 	free(data->meal_max);
	free(data);
	return (0);
}
