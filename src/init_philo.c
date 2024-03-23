/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:01:18 by macassag          #+#    #+#             */
/*   Updated: 2024/03/22 10:57:50 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*new_philo(size_t index, t_info info)
{
	t_philo	*new;
	t_fork	*fork;

	new = (t_philo *)malloc(sizeof(t_philo));
	fork = (t_fork *)malloc(sizeof(t_fork));
	// fork->lock_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!new || !fork)
		return (NULL);
	memset(new, 0, sizeof(t_philo));
	memset(fork, 0, sizeof(t_fork));
	new->index = index;
	new->info = info;
	fork->fork = true;
	if (mutex_init(fork->lock_fork) == -1)
		return (NULL);
	new->r_fork = fork;
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
		new->l_fork = tmp->r_fork;
	}
}

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	memset(data, 0, sizeof(t_data));
	// data->lock_print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	// data->lock_start = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	// data->lock_eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	// data->lock_data = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (mutex_init(data->lock_print) == -1)
		return (del_mutex(data));
	if (mutex_init(data->lock_start) == -1)
		return (del_mutex(data));
	if (mutex_init(data->lock_eat) == -1)
		return (del_mutex(data));
	if (mutex_init(data->lock_data) == -1)
		return (del_mutex(data));
	return (data);
}

void	init_philo(t_info info)
{
	t_philo	*philo;
	t_philo	*tmp;
	t_data	*data;
	size_t	i;

	i = 1;
	philo = NULL;
	data = init_data();
	if (!data)
		return ;
	while (i <= info.phi_nbr)
	{
		tmp = new_philo(i++, info);
		if (!tmp)
			error_lst(&philo, "msg");
		tmp->data = data;
		ft_lstadd_back(&philo, tmp);
	}
	tmp->next = philo;
	philo->prev = tmp;
	philo->l_fork = tmp->r_fork;
	ft_philo(philo);
}
