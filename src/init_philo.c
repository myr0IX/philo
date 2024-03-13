/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:01:18 by macassag          #+#    #+#             */
/*   Updated: 2024/03/13 16:08:27 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*new_philo(size_t index, t_info info)
{
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_philo));
	new->index = index;
	new->print_lock = &info.mutex;
	new->info = info;
	pthread_mutex_init(&new->fork, NULL);
	return (new);
}

static void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*tmp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
		tmp->fork_next = &new->fork;
	}
}

void	init_philo(t_info info)
{
	t_philo	*philo;
	t_philo	*tmp;
	size_t	i;

	i = 1;
	pthread_mutex_init(&info.mutex, NULL);
	philo = new_philo(i++, info);
	while (i <= info.phi_nbr)
	{
		tmp = new_philo(i++, info);
		if (!tmp)
			error_lst(&philo, "msg");
		ft_lstadd_back(&philo, tmp);
	}
	tmp->next = philo;
	philo->prev = tmp;
	tmp->fork_next = &philo->fork;
	ft_philo(philo);
}
