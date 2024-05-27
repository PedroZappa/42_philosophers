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
void		ft_free_philos(t_philo *philo);
int			ft_kill_philos(t_philo *philo);

/// @brief			Free allocated memory
/// @param philo	Pointer to a t_philo struct
/// @details		- Kill all child processes
/// 				- Close semaphores
/// 				- Unlink semaphores
/// 				- Free pointer to pid array
/// 				- Free pointer to t_philo struct
void	ft_free(t_philo *philos, t_data *data)
{
	ft_kill_philos(philos);
	ft_sem_closer(data);
	ft_free_philos(philos);
	free(data);
}

/// @brief			Close semaphores
/// @param to_del	Pointer to a t_philo struct
/// @return			0 on success, 1 on failure
int	ft_sem_closer(t_data *to_del)
{
	if (sem_close(to_del->sem_printf) \
		|| sem_close(to_del->sem_forks) \
		|| sem_close(to_del->sem_start) \
		|| sem_close(to_del->sem_death) \
		|| sem_close(to_del->sem_time) \
		|| sem_close(to_del->sem_end))
	{
		ft_perror(RED"Error: semaphore close error\n"NC);
		return (1);
	}
	return (ft_sem_unlinker());
}

/// @brief			Unlink semaphores
/// @param			none
/// @return			0 on success, 1 on failure
static int	ft_sem_unlinker(void)
{
	if (sem_unlink("/sem_forks") \
		|| sem_unlink("/sem_printf") \
		|| sem_unlink("/sem_death") \
		|| sem_unlink("/sem_start") \
		|| sem_unlink("/sem_end") \
		|| sem_unlink("/sem_time"))
	{
		ft_perror(RED"Error: semaphore unlink error\n"NC);
		return (1);
	}
	return (0);
}

void	ft_free_philos(t_philo *philo)
{
	t_philo	*tmp;
	t_philo	*next;

	tmp = philo;
	next = tmp;
	if (philo != NULL)
	{
		while ((tmp->next != NULL) && (tmp->next != philo))
		{
			next = tmp->next;
			free(tmp);
			tmp = next;
		}
		free(tmp);
	}
}

int	ft_kill_philos(t_philo *philo)
{
	t_philo	*target;
	int	i;

	target = philo;
	i = philo->data->n_philos;
	while (i--)
		sem_wait(philo->data->sem_end);
	while ((target->next != NULL) && (target->next != philo))
	{
		kill(target->pid, SIGKILL);
		target = target->next;
	}
	kill(target->pid, SIGKILL);
	return (0);
}
