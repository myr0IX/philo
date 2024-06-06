/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macassag <macassag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:19:42 by macassag          #+#    #+#             */
/*   Updated: 2024/06/05 13:52:48 by macassag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_mutex	*create_mutex(void)
{
	t_mutex	*mutex;

	mutex = (t_mutex *) malloc(sizeof(t_mutex));
	if (!mutex)
		return (NULL);
	memset(mutex, 0, sizeof(t_mutex));
	if (mutex_init(mutex->mutex) == -1)
		return (NULL);
	return (mutex);
}

int	mutex_init(pthread_mutex_t mutex)
{
	if (pthread_mutex_init(&mutex, NULL))
	{
		write(2, "pthread_mutex_init() error\n", 28);
		return (-1);
	}
	return (0);
}

void	mutex_destroy(pthread_mutex_t *mutex)
{
	if (mutex)
		pthread_mutex_destroy(mutex);
}
