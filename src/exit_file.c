/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:48:20 by macassag          #+#    #+#             */
/*   Updated: 2024/03/15 14:31:09 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_lst(t_philo **list)
{
	t_philo	*tmp;

	(*list)->prev->next = NULL;
	free((*list)->data);
	while ((*list)->next != NULL)
	{
		tmp = *list;
		*list = (*list)->next;
		pthread_mutex_destroy(&tmp->fork);
		memset(tmp, 0, (sizeof(t_philo)));
		free(tmp);
	}
	// *list = (*list)->next;
	// pthread_mutex_destroy(&tmp->fork);
	free(*list);
	// *list = NULL;
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
