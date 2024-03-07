/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:48:20 by macassag          #+#    #+#             */
/*   Updated: 2024/03/07 15:16:11 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_lst(t_philo **list)
{
	t_philo	*tmp;

	while (*list != NULL)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
		memset(tmp, 0, sizeof(t_philo));
	}
	*list = NULL;
}

void	error_lst(t_philo **list, char *msg)
{
	free_lst(list);
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	ft_death(t_philo **list)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	printf(DEATH, time.tv_usec, (*list)->index);
	usleep(20000);
	pthread_mutex_unlock(&(*list)->data.mutex);
	pthread_mutex_destroy(&(*list)->data.mutex);
	free_lst(list);
	exit(EXIT_SUCCESS);
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
