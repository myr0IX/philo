/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:01:18 by macassag          #+#    #+#             */
/*   Updated: 2024/03/18 09:36:51 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*new_philo(size_t index, t_info info)
{
	t_philo			*new;
	pthread_mutex_t	*fork;

	new = (t_philo *)malloc(sizeof(t_philo));
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!new || !fork)
		return (NULL);
	memset(new, 0, sizeof(t_philo));
	new->index = index;
	new->info = info;
	pthread_mutex_init(fork, NULL);
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

t_data	*init_data(t_data *data)
{
	data = (t_data *)malloc(sizeof(t_data));
	memset(data, 0, sizeof(t_data));
	data->lock_print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->lock_start = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	data->lock_eat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->lock_print, NULL);
	pthread_mutex_init(data->lock_start, NULL);
	pthread_mutex_init(data->lock_eat, NULL);
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
	data = init_data(data);
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
