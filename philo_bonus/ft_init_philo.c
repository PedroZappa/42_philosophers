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

static t_philo	*ft_make_philo(t_data *data, int idx)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_philo));
	new->idx = idx;
	new->data = data;
	return (new);
}

static void	ft_add_philo(t_philo **philo, t_philo *new)
{
	t_philo	*tmp;

	if (!*philo)
	{
		*philo = new;
		return ;
	}
	tmp = *philo;
	while (tmp->idx != (new->idx - 1))
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	new->next = *philo;
	(*philo)->prev = new;
}
