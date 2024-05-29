/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:11:57 by macassag          #+#    #+#             */
/*   Updated: 2024/05/29 11:47:59 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


t_time	run_philo(t_mutex *mutex,t_time start_time)
{
	static t_time	time;
	t_time			ret;

	if (!start_time)
	{
		pthread_mutex_lock(&mutex->mutex);
		ret = time;
		pthread_mutex_unlock(&mutex->mutex);
		return (ret);
	}
	pthread_mutex_lock(&mutex->mutex);
	time = start_time;
	pthread_mutex_unlock(&mutex->mutex);
	return (0);
}

// stop all the philosophers
void	stop_philo(t_philo *phi, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (get_value(phi[i].flag) < STOP)
			set_value(phi[i].flag, STOP);
		i++;
	}
}

// exit all the philosophers
void	exit_child(t_philo *phi, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (get_value(phi[i].flag) != EXIT)
		{
			set_value(phi[i].flag, EXIT);
			pthread_join(phi[i].thread, NULL);
		}
		i++;
	}
}
