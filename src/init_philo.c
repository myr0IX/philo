/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:01:18 by macassag          #+#    #+#             */
/*   Updated: 2024/03/05 14:07:24 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*new_philo(size_t index, t_info infos)
{
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_philo));
	new->index = index;
	new->ft_print = infos.ft_print;
	new->infos = infos;
	return (new);
}

static void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
}

void	init_philo(t_info infos)
{
	t_philo	*philos;
	t_philo	*tmp;
	size_t	i;

	i = 1;
	philos = new_philo(i++, infos);
	while (i <= infos.phi_nbr)
	{
		tmp = new_philo(i, infos);
		if (!tmp)
			error_lst(&philos, "msg");
		ft_lstadd_back(&philos, tmp);
		i++;
	}
	tmp->next = philos;
	philos->prev = tmp;
	philo(philos);
}
