/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:55:42 by macassag          #+#    #+#             */
/*   Updated: 2024/03/07 09:54:34 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	waiting_ticket(t_philo **data)
{
	t_philo			*philo;
	static size_t	waiting_ticket;
	size_t			tmp;

	philo = *data;
	pthread_mutex_lock(&philo->data.mutex_2);
	philo->waiting_ticket = ++waiting_ticket;
	pthread_mutex_lock(&philo->data.mutex_2);
}

void	wait_list(t_philo **data)
{
	t_philo			*philo;

	waiting_ticket(data);
	philo = *data;
	while (philo->waiting_ticket != 0)
		continue ;
	pthread_mutex_lock(&philo->data.mutex);
}