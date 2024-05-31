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
int			ft_free_data(t_data *data);

/// @brief			Close semaphores
/// @param to_del	Pointer to a t_philo struct
/// @return			0 on success, 1 on failure
/// @note			Used in main
int	ft_sem_closer(t_data *to_del)
{
	if (sem_close(to_del->sem_printf) \
		|| sem_close(to_del->sem_forks) \
		|| sem_close(to_del->sem_start) \
		|| sem_close(to_del->sem_death) \
		|| sem_close(to_del->sem_time) \
		|| sem_close(to_del->sem_end))
		return (ft_perror(RED"Error: semaphore close error\n"NC));
	return (ft_sem_unlinker());
}

/// @brief			Unlink semaphores
/// @param			none
/// @return			0 on success, 1 on failure
/// @note			Used in ft_sem_closer
static int	ft_sem_unlinker(void)
{
	if (sem_unlink("/sem_forks") \
		|| sem_unlink("/sem_printf") \
		|| sem_unlink("/sem_death") \
		|| sem_unlink("/sem_start") \
		|| sem_unlink("/sem_end") \
		|| sem_unlink("/sem_time"))
		return (ft_perror(RED"Error: semaphore unlink error\n"NC));
	return (SUCCESS);
}

/// @brief			Free philo linked list
/// @param philo	Pointer to a t_philo struct
/// @var tmp		Pointer to a t_philo struct
/// @var next		Pointer to a t_philo struct
/// @details		- Save reference to philo in tmp & next
/// 				- Free data
/// 				- While the next node exists and the next node !philo
///						- Move tmp to next (in next)
///						- Free the current node (tmp)
///						- Save reference to next in tmp
///					- Free the last node (tmp)
void	ft_free_philos(t_philo *philo)
{
	t_philo	*tmp;
	t_philo	*next;

	tmp = philo;
	next = tmp;
	ft_free_data(philo->d);
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

/// @brief			Kill all philos by sending SIGKILL
/// @param philo	Pointer to a t_philo struct
/// @var target		Pointer to a t_philo struct
/// @var i			Philo's indexer
/// @return			0 on success, 1 on failure
/// @details		- Save reference to philo in target
///					- Initialize i to number of philos
///					- Send `i` sem_waits to sem_end
///					- While the next node exists and the next node !philo
int	ft_kill_philos(t_philo *philo)
{
	t_philo	*target;
	int		i;

	target = philo;
	i = philo->d->n_philos;
	usleep(5000);
	while (i--)
		sem_wait(philo->d->sem_end);
	while ((target->next != NULL) && (target->next != philo))
	{
		kill(target->pid, SIGKILL);
		target = target->next;
	}
	kill(target->pid, SIGKILL);
	return (SUCCESS);
}

/// @brief			Free data
/// @param data		Pointer to a t_data struct
/// @return			0 on success, 1 on failure
/// @details		- Free pointer to meal_max if it exists
/// 				- Free data
/// @note			Used in ft_init_philos & ft_free_philos
int	ft_free_data(t_data *data)
{
	if (data->meal_max != NULL)
		free(data->meal_max);
	free(data);
	return (SUCCESS);
}
