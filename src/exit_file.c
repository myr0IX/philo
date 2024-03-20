/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:48:20 by macassag          #+#    #+#             */
/*   Updated: 2024/03/20 16:15:20 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	del_mutex(t_data *data)
{
	pthread_mutex_destroy(data->lock_print);
	pthread_mutex_destroy(data->lock_start);
	pthread_mutex_destroy(data->lock_eat);
	pthread_mutex_destroy(data->lock_data);
	free(data->lock_print);
	free(data->lock_start);
	free(data->lock_eat);
	free(data->lock_data);
	free(data);
}

void	free_lst(t_philo **list)
{
	t_philo	*tmp;

	(*list)->prev->next = NULL;
	while ((*list)->next != NULL)
	{
		tmp = *list;
		*list = (*list)->next;
		pthread_mutex_destroy(tmp->r_fork);
		free(tmp);
	}
	pthread_mutex_destroy((*list)->r_fork);
	free(*list);
}

void	error_lst(t_philo **list, char *msg)
{
	free_lst(list);
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	philo_end(t_philo **list)
{
	t_philo	*tmp;

	tmp = *list;
	tmp = tmp->next;
	tmp->prev = (*list)->prev;
	(*list)->prev->next = tmp;
	free(*list);
	memset(*list, 0, sizeof(t_philo));
}
