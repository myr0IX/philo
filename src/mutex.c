/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:19:42 by macassag          #+#    #+#             */
/*   Updated: 2024/03/20 13:26:54 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_lock(pthread_mutex_t *mutex, t_philo **data)
{
	t_philo	*philo;

	philo = *data;
	if (pthread_mutex_lock(mutex) == -1)
	{
		pthread_mutex_lock(philo->data->lock_data);
		philo->data->error = 1;
		write(2, "pthread_mutex_lock() error\n", 28);
		pthread_mutex_lock(philo->data->lock_data);
	}
}

void	mutex_unlock(pthread_mutex_t *mutex, t_philo **data)
{
	t_philo	*philo;

	philo = *data;
	if (pthread_mutex_unlock(mutex) == -1)
	{
		pthread_mutex_lock(philo->data->lock_data);
		philo->data->error = 1;
		write(2, "pthread_mutex_lock() error\n", 28);
		pthread_mutex_lock(philo->data->lock_data);
	}
}
