/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:56 by macassag          #+#    #+#             */
/*   Updated: 2024/03/23 14:46:01 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_death(t_philo **data)
{
	t_philo	*philo;

	philo = *data;
	pthread_mutex_lock(&philo->data->lock_data);
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->lock_data);
		return ;
	}
	printf(DEATH, philo->time, philo->index);
	philo->data->stop = 1;
	pthread_mutex_unlock(&philo->data->lock_data);
	philo->stop = 1;
}

void	print_log(char *msg, t_philo **data)
{
	t_philo 		*philo;

	philo = *data;
	// if (philo->stop == 1)
	// 	return ;
	philo->time = get_time(philo);
	pthread_mutex_lock(&philo->data->lock_print);
	// pthread_mutex_lock(&philo->data->lock_data);
	if (get_bool(&philo->mutex, philo->stop))
		;
	else
		printf(msg, philo->time, philo->index);
	pthread_mutex_unlock(&philo->data->lock_print);
}
