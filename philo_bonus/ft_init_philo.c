/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passunca <passunca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:20:24 by passunca          #+#    #+#             */
/*   Updated: 2024/05/26 22:18:43 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_philo	*ft_make_philo(t_data *data, int idx);
static void		ft_add_philo(t_philo **philo, t_philo *new);
void			ft_free_philos(t_philo *philo);

/// @brief		Initialize a doubly linked list of philos
/// @param data	Pointer to a t_data struct
/// @var philo	Pointer to a t_philo struct
/// @var new	Pointer to a t_philo struct
/// @var i		Iterator
/// @return		Pointer to an doubly linked list of t_philo structs
/// @details	Allocate and initialize doubly linked list of t_philo structs
///				- Create first philo
/// 			- Add n_philos to the list
/// @note		Used in main
t_philo	*ft_init_philos(t_data *data)
{
	t_philo	*philo;
	t_philo	*new;
	int		i;

	philo = NULL;
	new = NULL;
	i = 0;
	while (++i <= data->n_philos)
	{
		new = ft_make_philo(data, i);
		if (!new)
		{
			ft_free_philos(philo);
			ft_free_data(data);
			return (NULL);
		}
		ft_add_philo(&philo, new);
	}
	return (philo);
}

/// @brief		Allocate and initialize a doubly linked list of t_philo structs
/// @param data	Pointer to a t_data struct
/// @param idx	Index of the current philo
/// @var new	Pointer to a t_philo struct
/// @return		Pointer to an doubly linked list of t_philo structs
/// @details	- Allocate memory for a t_philo struct
/// 			- Set the memory to 0
/// 			- Initialize the data
/// @note		Used in ft_init_philos
static t_philo	*ft_make_philo(t_data *data, int idx)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	memset(new, '\0', sizeof(t_philo));
	new->idx = idx;
	new->d = data;
	return (new);
}

/// @brief			Add a new philo to the doubly linked list
/// @param philo	Pointer to a pointer to t_philo struct
/// @param new		Pointer to a new t_philo node
/// @var target		Pointer to a t_philo struct used to traverse the list
/// @details		- Traverse the list to find the last node
///					- Add the new node to the list end of the list
/// @note			Used in ft_init_philos
static void	ft_add_philo(t_philo **philo, t_philo *new)
{
	t_philo	*target;

	if (!*philo)
	{
		*philo = new;
		return ;
	}
	target = *philo;
	while (target->idx != (new->idx - 1))
		target = target->next;
	target->next = new;
	new->prev = target;
	new->next = *philo;
	(*philo)->prev = new;
}
