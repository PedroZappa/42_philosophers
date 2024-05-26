/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 11:26:15 by passunca          #+#    #+#             */
/*   Updated: 2024/05/26 20:22:48 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_sem_closer(t_philo *to_del);
static int	ft_sem_unlinker(void);

/// @brief			Free allocated memory
/// @param philo	Pointer to a t_philo struct
/// @details		- Kill all child processes
/// 				- Close semaphores
/// 				- Unlink semaphores
/// 				- Free pointer to pid array
/// 				- Free pointer to t_philo struct
void	ft_free(t_philo **philo)
{
	t_philo	*to_del;
	int		i;
	int		pid_status;

	to_del = *philo;
	i = 0;
	while (i < to_del->n_philos)
	{
		waitpid(-1, &pid_status, 0);
		if (pid_status != 0)
		{
			i = -1;
			while (++i < to_del->n_philos)
				kill(to_del->pid[i], SIGKILL);
			break ;
		}
		++i;
	}
	ft_sem_closer(to_del);
	free(to_del->pid);
	free(to_del);
}

/// @brief			Close semaphores
/// @param to_del	Pointer to a t_philo struct
/// @return			0 on success, 1 on failure
static int	ft_sem_closer(t_philo *to_del)
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