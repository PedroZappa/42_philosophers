/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:10:33 by passunca          #+#    #+#             */
/*   Updated: 2024/05/29 19:48:00 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* @file			ft_eat.c
* @brief		Eating functions
* @version		1.0
* @date			2024-05-28
* @author		passunca
* @copyright	© 2024 passunca
***/

#include "philo.h"

static int	ft_getforks(t_philo *p);
static int	ft_dropforks(t_philo *p);

/// @brief		Eating logic
/// @param p	Pointer to a t_philo struct
/// @return		SUCCESS if eating, FAILURE if not
/// @details	- Lock fork mutexes
///				- Lock meal mutex
///				- Get meal time, set last_meal
///				- Count meal
///				- Unlock meal mutex
///				- Check if the simulation is done
///					- Don't eat if done (unlock fork mutexes)
///				- Eat
///				- Unlock fork mutexes
/// @note		Used in ft_start_philo
int	ft_eating(t_philo *p)
{
	if (ft_getforks(p) != SUCCESS)
		return (FAILURE);
	pthread_mutex_lock(&p->data->mutex[MTX_MEALS]);
	p->last_meal = ft_gettime();
	p->meal_count++;
	pthread_mutex_unlock(&p->data->mutex[MTX_MEALS]);
	if (ft_isdone(p))
		return (ft_dropforks(p), FAILURE);
	ft_usleep(p->data->t_meal);
	ft_dropforks(p);
	return (SUCCESS);
}

/// @brief			Grabbing forks and eating
/// @param p		Pointer to a t_philo struct
/// @return			SUCCESS (0) if eating, FAILURE (1) if not
/// @details		- Lock fork mutexes
/// 				- Check if bolding a fork with both hands
///						- If not, unlock both
/// 				- Log
/// @note			Used in ft_eating
static int	ft_getforks(t_philo *p)
{
	pthread_mutex_lock(&p->fork[ft_min(p->l_fork, p->r_fork)]);
	ft_log(p, "has taken a fork");
	if (p->l_fork == p->r_fork)
	{
		pthread_mutex_unlock(&p->fork[ft_min(p->l_fork, p->r_fork)]);
		return (FAILURE);
	}
	pthread_mutex_lock(&p->fork[ft_max(p->l_fork, p->r_fork)]);
	ft_log(p, "has taken a fork");
	ft_log(p, "is eating");
	return (SUCCESS);
}

/// @brief			Release forks and sleep
/// @param p		Pointer to a t_philo struct
/// @return			SUCCESS if eating, FAILURE if not
/// @details		- Log
/// 				- Unlock fork mutexes
/// 				- Sleep
/// @note			Used in ft_eating
static int	ft_dropforks(t_philo *p)
{
	ft_log(p, "is sleeping");
	pthread_mutex_unlock(&p->fork[ft_max(p->l_fork, p->r_fork)]);
	pthread_mutex_unlock(&p->fork[ft_min(p->l_fork, p->r_fork)]);
	ft_usleep(p->data->t_sleep);
	return (SUCCESS);
}
